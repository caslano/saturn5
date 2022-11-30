
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2013 Nikhar Agrawal
//  Copyright 2013 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2013 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef _BOOST_POLYGAMMA_DETAIL_2013_07_30_HPP_
  #define _BOOST_POLYGAMMA_DETAIL_2013_07_30_HPP_

#include <cmath>
#include <limits>
#include <string>
#include <boost/math/policies/policy.hpp>
#include <boost/math/special_functions/bernoulli.hpp>
#include <boost/math/special_functions/trunc.hpp>
#include <boost/math/special_functions/zeta.hpp>
#include <boost/math/special_functions/digamma.hpp>
#include <boost/math/special_functions/sin_pi.hpp>
#include <boost/math/special_functions/cos_pi.hpp>
#include <boost/math/special_functions/pow.hpp>
#include <boost/math/tools/assert.hpp>
#include <boost/math/tools/config.hpp>

#ifdef BOOST_HAS_THREADS
#include <mutex>
#endif

#ifdef _MSC_VER
#pragma once
#pragma warning(push)
#pragma warning(disable:4702) // Unreachable code (release mode only warning)
#endif

namespace boost { namespace math { namespace detail{

  template<class T, class Policy>
  T polygamma_atinfinityplus(const int n, const T& x, const Policy& pol, const char* function) // for large values of x such as for x> 400
  {
     // See http://functions.wolfram.com/GammaBetaErf/PolyGamma2/06/02/0001/
     BOOST_MATH_STD_USING
     //
     // sum       == current value of accumulated sum.
     // term      == value of current term to be added to sum.
     // part_term == value of current term excluding the Bernoulli number part
     //
     if(n + x == x)
     {
        // x is crazy large, just concentrate on the first part of the expression and use logs:
        if(n == 1) return 1 / x;
        T nlx = n * log(x);
        if((nlx < tools::log_max_value<T>()) && (n < (int)max_factorial<T>::value))
           return ((n & 1) ? 1 : -1) * boost::math::factorial<T>(n - 1, pol) * pow(x, -n);
        else
         return ((n & 1) ? 1 : -1) * exp(boost::math::lgamma(T(n), pol) - n * log(x));
     }
     T term, sum, part_term;
     T x_squared = x * x;
     //
     // Start by setting part_term to:
     //
     // (n-1)! / x^(n+1)
     //
     // which is common to both the first term of the series (with k = 1)
     // and to the leading part.  
     // We can then get to the leading term by:
     //
     // part_term * (n + 2 * x) / 2
     //
     // and to the first term in the series 
     // (excluding the Bernoulli number) by:
     //
     // part_term n * (n + 1) / (2x)
     //
     // If either the factorial would overflow,
     // or the power term underflows, this just gets set to 0 and then we
     // know that we have to use logs for the initial terms:
     //
     part_term = ((n > (int)boost::math::max_factorial<T>::value) && (T(n) * n > tools::log_max_value<T>())) 
        ? T(0) : static_cast<T>(boost::math::factorial<T>(n - 1, pol) * pow(x, -n - 1));
     if(part_term == 0)
     {
        // Either n is very large, or the power term underflows,
        // set the initial values of part_term, term and sum via logs:
        part_term = static_cast<T>(boost::math::lgamma(n, pol) - (n + 1) * log(x));
        sum = exp(part_term + log(n + 2 * x) - boost::math::constants::ln_two<T>());
        part_term += log(T(n) * (n + 1)) - boost::math::constants::ln_two<T>() - log(x);
        part_term = exp(part_term);
     }
     else
     {
        sum = part_term * (n + 2 * x) / 2;
        part_term *= (T(n) * (n + 1)) / 2;
        part_term /= x;
     }
     //
     // If the leading term is 0, so is the result:
     //
     if(sum == 0)
        return sum;

     for(unsigned k = 1;;)
     {
        term = part_term * boost::math::bernoulli_b2n<T>(k, pol);
        sum += term;
        //
        // Normal termination condition:
        //
        if(fabs(term / sum) < tools::epsilon<T>())
           break;
        //
        // Increment our counter, and move part_term on to the next value:
        //
        ++k;
        part_term *= T(n + 2 * k - 2) * (n - 1 + 2 * k);
        part_term /= (2 * k - 1) * 2 * k;
        part_term /= x_squared;
        //
        // Emergency get out termination condition:
        //
        if(k > policies::get_max_series_iterations<Policy>())
        {
           return policies::raise_evaluation_error(function, "Series did not converge, closest value was %1%", sum, pol);
        }
     }
     
     if((n - 1) & 1)
        sum = -sum;

     return sum;
  }

  template<class T, class Policy>
  T polygamma_attransitionplus(const int n, const T& x, const Policy& pol, const char* function)
  {
    // See: http://functions.wolfram.com/GammaBetaErf/PolyGamma2/16/01/01/0017/

    // Use N = (0.4 * digits) + (4 * n) for target value for x:
    BOOST_MATH_STD_USING
    const int d4d  = static_cast<int>(0.4F * policies::digits_base10<T, Policy>());
    const int N = d4d + (4 * n);
    const int m    = n;
    const int iter = N - itrunc(x);

    if(iter > (int)policies::get_max_series_iterations<Policy>())
       return policies::raise_evaluation_error<T>(function, ("Exceeded maximum series evaluations evaluating at n = " + std::to_string(n) + " and x = %1%").c_str(), x, pol);

    const int minus_m_minus_one = -m - 1;

    T z(x);
    T sum0(0);
    T z_plus_k_pow_minus_m_minus_one(0);

    // Forward recursion to larger x, need to check for overflow first though:
    if(log(z + iter) * minus_m_minus_one > -tools::log_max_value<T>())
    {
       for(int k = 1; k <= iter; ++k)
       {
          z_plus_k_pow_minus_m_minus_one = pow(z, minus_m_minus_one);
          sum0 += z_plus_k_pow_minus_m_minus_one;
          z += 1;
       }
       sum0 *= boost::math::factorial<T>(n, pol);
    }
    else
    {
       for(int k = 1; k <= iter; ++k)
       {
          T log_term = log(z) * minus_m_minus_one + boost::math::lgamma(T(n + 1), pol);
          sum0 += exp(log_term);
          z += 1;
       }
    }
    if((n - 1) & 1)
       sum0 = -sum0;

    return sum0 + polygamma_atinfinityplus(n, z, pol, function);
  }

  template <class T, class Policy>
  T polygamma_nearzero(int n, T x, const Policy& pol, const char* function)
  {
     BOOST_MATH_STD_USING
     //
     // If we take this expansion for polygamma: http://functions.wolfram.com/06.15.06.0003.02
     // and substitute in this expression for polygamma(n, 1): http://functions.wolfram.com/06.15.03.0009.01
     // we get an alternating series for polygamma when x is small in terms of zeta functions of
     // integer arguments (which are easy to evaluate, at least when the integer is even).
     //
     // In order to avoid spurious overflow, save the n! term for later, and rescale at the end:
     //
     T scale = boost::math::factorial<T>(n, pol);
     //
     // "factorial_part" contains everything except the zeta function
     // evaluations in each term:
     //
     T factorial_part = 1;
     //
     // "prefix" is what we'll be adding the accumulated sum to, it will
     // be n! / z^(n+1), but since we're scaling by n! it's just 
     // 1 / z^(n+1) for now:
     //
     T prefix = pow(x, n + 1);
     if(prefix == 0)
        return boost::math::policies::raise_overflow_error<T>(function, 0, pol);
     prefix = 1 / prefix;
     //
     // First term in the series is necessarily < zeta(2) < 2, so
     // ignore the sum if it will have no effect on the result anyway:
     //
     if(prefix > 2 / policies::get_epsilon<T, Policy>())
        return ((n & 1) ? 1 : -1) * 
         (tools::max_value<T>() / prefix < scale ? policies::raise_overflow_error<T>(function, 0, pol) : prefix * scale);
     //
     // As this is an alternating series we could accelerate it using 
     // "Convergence Acceleration of Alternating Series",
     // Henri Cohen, Fernando Rodriguez Villegas, and Don Zagier, Experimental Mathematics, 1999.
     // In practice however, it appears not to make any difference to the number of terms
     // required except in some edge cases which are filtered out anyway before we get here.
     //
     T sum = prefix;
     for(unsigned k = 0;;)
     {
        // Get the k'th term:
        T term = factorial_part * boost::math::zeta(T(k + n + 1), pol);
        sum += term;
        // Termination condition:
        if(fabs(term) < fabs(sum * boost::math::policies::get_epsilon<T, Policy>()))
           break;
        //
        // Move on k and factorial_part:
        //
        ++k;
        factorial_part *= (-x * (n + k)) / k;
        //
        // Last chance exit:
        //
        if(k > policies::get_max_series_iterations<Policy>())
           return policies::raise_evaluation_error<T>(function, "Series did not converge, best value is %1%", sum, pol);
     }
     //
     // We need to multiply by the scale, at each stage checking for overflow:
     //
     if(boost::math::tools::max_value<T>() / scale < sum)
        return boost::math::policies::raise_overflow_error<T>(function, 0, pol);
     sum *= scale;
     return n & 1 ? sum : T(-sum);
  }

  //
  // Helper function which figures out which slot our coefficient is in
  // given an angle multiplier for the cosine term of power:
  //
  template <class Table>
  typename Table::value_type::reference dereference_table(Table& table, unsigned row, unsigned power)
  {
     return table[row][power / 2];
  }



  template <class T, class Policy>
  T poly_cot_pi(int n, T x, T xc, const Policy& pol, const char* function)
  {
     BOOST_MATH_STD_USING
     // Return n'th derivative of cot(pi*x) at x, these are simply
     // tabulated for up to n = 9, beyond that it is possible to
     // calculate coefficients as follows:
     //
     // The general form of each derivative is:
     //
     // pi^n * SUM{k=0, n} C[k,n] * cos^k(pi * x) * csc^(n+1)(pi * x)
     //
     // With constant C[0,1] = -1 and all other C[k,n] = 0;
     // Then for each k < n+1:
     // C[k-1, n+1]  -= k * C[k, n];
     // C[k+1, n+1]  += (k-n-1) * C[k, n];
     //
     // Note that there are many different ways of representing this derivative thanks to
     // the many trigonometric identies available.  In particular, the sum of powers of
     // cosines could be replaced by a sum of cosine multiple angles, and indeed if you
     // plug the derivative into Mathematica this is the form it will give.  The two
     // forms are related via the Chebeshev polynomials of the first kind and
     // T_n(cos(x)) = cos(n x).  The polynomial form has the great advantage that
     // all the cosine terms are zero at half integer arguments - right where this
     // function has it's minimum - thus avoiding cancellation error in this region.
     //
     // And finally, since every other term in the polynomials is zero, we can save
     // space by only storing the non-zero terms.  This greatly complexifies
     // subscripting the tables in the calculation, but halves the storage space
     // (and complexity for that matter).
     //
     T s = fabs(x) < fabs(xc) ? boost::math::sin_pi(x, pol) : boost::math::sin_pi(xc, pol);
     T c = boost::math::cos_pi(x, pol);
     switch(n)
     {
     case 1:
        return -constants::pi<T, Policy>() / (s * s);
     case 2:
     {
        return 2 * constants::pi<T, Policy>() * constants::pi<T, Policy>() * c / boost::math::pow<3>(s, pol);
     }
     case 3:
     {
        constexpr int P[] = { -2, -4 };
        return boost::math::pow<3>(constants::pi<T, Policy>(), pol) * tools::evaluate_even_polynomial(P, c) / boost::math::pow<4>(s, pol);
     }
     case 4:
     {
        constexpr int P[] = { 16, 8 };
        return boost::math::pow<4>(constants::pi<T, Policy>(), pol) * c * tools::evaluate_even_polynomial(P, c) / boost::math::pow<5>(s, pol);
     }
     case 5:
     {
        constexpr int P[] = { -16, -88, -16 };
        return boost::math::pow<5>(constants::pi<T, Policy>(), pol) * tools::evaluate_even_polynomial(P, c) / boost::math::pow<6>(s, pol);
     }
     case 6:
     {
        constexpr int P[] = { 272, 416, 32 };
        return boost::math::pow<6>(constants::pi<T, Policy>(), pol) * c * tools::evaluate_even_polynomial(P, c) / boost::math::pow<7>(s, pol);
     }
     case 7:
     {
        constexpr int P[] = { -272, -2880, -1824, -64 };
        return boost::math::pow<7>(constants::pi<T, Policy>(), pol) * tools::evaluate_even_polynomial(P, c) / boost::math::pow<8>(s, pol);
     }
     case 8:
     {
        constexpr int P[] = { 7936, 24576, 7680, 128 };
        return boost::math::pow<8>(constants::pi<T, Policy>(), pol) * c * tools::evaluate_even_polynomial(P, c) / boost::math::pow<9>(s, pol);
     }
     case 9:
     {
        constexpr int P[] = { -7936, -137216, -185856, -31616, -256 };
        return boost::math::pow<9>(constants::pi<T, Policy>(), pol) * tools::evaluate_even_polynomial(P, c) / boost::math::pow<10>(s, pol);
     }
     case 10:
     {
        constexpr int P[] = { 353792, 1841152, 1304832, 128512, 512 };
        return boost::math::pow<10>(constants::pi<T, Policy>(), pol) * c * tools::evaluate_even_polynomial(P, c) / boost::math::pow<11>(s, pol);
     }
     case 11:
     {
        constexpr int P[] = { -353792, -9061376, -21253376, -8728576, -518656, -1024};
        return boost::math::pow<11>(constants::pi<T, Policy>(), pol) * tools::evaluate_even_polynomial(P, c) / boost::math::pow<12>(s, pol);
     }
     case 12:
     {
        constexpr int P[] = { 22368256, 175627264, 222398464, 56520704, 2084864, 2048 };
        return boost::math::pow<12>(constants::pi<T, Policy>(), pol) * c * tools::evaluate_even_polynomial(P, c) / boost::math::pow<13>(s, pol);
     }
#ifndef BOOST_NO_LONG_LONG
     case 13:
     {
        constexpr long long P[] = { -22368256LL, -795300864LL, -2868264960LL, -2174832640LL, -357888000LL, -8361984LL, -4096 };
        return boost::math::pow<13>(constants::pi<T, Policy>(), pol) * tools::evaluate_even_polynomial(P, c) / boost::math::pow<14>(s, pol);
     }
     case 14:
     {
        constexpr long long P[] = { 1903757312LL, 21016670208LL, 41731645440LL, 20261765120LL, 2230947840LL, 33497088LL, 8192 };
        return boost::math::pow<14>(constants::pi<T, Policy>(), pol) * c * tools::evaluate_even_polynomial(P, c) / boost::math::pow<15>(s, pol);
     }
     case 15:
     {
        constexpr long long P[] = { -1903757312LL, -89702612992LL, -460858269696LL, -559148810240LL, -182172651520LL, -13754155008LL, -134094848LL, -16384 };
        return boost::math::pow<15>(constants::pi<T, Policy>(), pol) * tools::evaluate_even_polynomial(P, c) / boost::math::pow<16>(s, pol);
     }
     case 16:
     {
        constexpr long long P[] = { 209865342976LL, 3099269660672LL, 8885192097792LL, 7048869314560LL, 1594922762240LL, 84134068224LL, 536608768LL, 32768 };
        return boost::math::pow<16>(constants::pi<T, Policy>(), pol) * c * tools::evaluate_even_polynomial(P, c) / boost::math::pow<17>(s, pol);
     }
     case 17:
     {
        constexpr long long P[] = { -209865342976LL, -12655654469632LL, -87815735738368LL, -155964390375424LL, -84842998005760LL, -13684856848384LL, -511780323328LL, -2146926592LL, -65536 };
        return boost::math::pow<17>(constants::pi<T, Policy>(), pol) * tools::evaluate_even_polynomial(P, c) / boost::math::pow<18>(s, pol);
     }
     case 18:
     {
        constexpr long long P[] = { 29088885112832LL, 553753414467584LL, 2165206642589696LL, 2550316668551168LL, 985278548541440LL, 115620218667008LL, 3100738912256LL, 8588754944LL, 131072 };
        return boost::math::pow<18>(constants::pi<T, Policy>(), pol) * c * tools::evaluate_even_polynomial(P, c) / boost::math::pow<19>(s, pol);
     }
     case 19:
     {
        constexpr long long P[] = { -29088885112832LL, -2184860175433728LL, -19686087844429824LL, -48165109676113920LL, -39471306959486976LL, -11124607890751488LL, -965271355195392LL, -18733264797696LL, -34357248000LL, -262144 };
        return boost::math::pow<19>(constants::pi<T, Policy>(), pol) * tools::evaluate_even_polynomial(P, c) / boost::math::pow<20>(s, pol);
     }
     case 20:
     {
        constexpr long long P[] = { 4951498053124096LL, 118071834535526400LL, 603968063567560704LL, 990081991141490688LL, 584901762421358592LL, 122829335169859584LL, 7984436548730880LL, 112949304754176LL, 137433710592LL, 524288 };
        return boost::math::pow<20>(constants::pi<T, Policy>(), pol) * c * tools::evaluate_even_polynomial(P, c) / boost::math::pow<21>(s, pol);
     }
#endif
     }

     //
     // We'll have to compute the coefficients up to n, 
     // complexity is O(n^2) which we don't worry about for now
     // as the values are computed once and then cached.
     // However, if the final evaluation would have too many
     // terms just bail out right away:
     //
     if((unsigned)n / 2u > policies::get_max_series_iterations<Policy>())
        return policies::raise_evaluation_error<T>(function, "The value of n is so large that we're unable to compute the result in reasonable time, best guess is %1%", 0, pol);
#ifdef BOOST_HAS_THREADS
     static std::mutex m;
     std::lock_guard<std::mutex> l(m);
#endif
     static int digits = tools::digits<T>();
     static std::vector<std::vector<T> > table(1, std::vector<T>(1, T(-1)));

     int current_digits = tools::digits<T>();

     if(digits != current_digits)
     {
        // Oh my... our precision has changed!
        table = std::vector<std::vector<T> >(1, std::vector<T>(1, T(-1)));
        digits = current_digits;
     }

     int index = n - 1;

     if(index >= (int)table.size())
     {
        for(int i = (int)table.size() - 1; i < index; ++i)
        {
           int offset = i & 1; // 1 if the first cos power is 0, otherwise 0.
           int sin_order = i + 2;  // order of the sin term
           int max_cos_order = sin_order - 1;  // largest order of the polynomial of cos terms
           int max_columns = (max_cos_order - offset) / 2;  // How many entries there are in the current row.
           int next_offset = offset ? 0 : 1;
           int next_max_columns = (max_cos_order + 1 - next_offset) / 2;  // How many entries there will be in the next row
           table.push_back(std::vector<T>(next_max_columns + 1, T(0)));

           for(int column = 0; column <= max_columns; ++column)
           {
              int cos_order = 2 * column + offset;  // order of the cosine term in entry "column"
              BOOST_MATH_ASSERT(column < (int)table[i].size());
              BOOST_MATH_ASSERT((cos_order + 1) / 2 < (int)table[i + 1].size());
              table[i + 1][(cos_order + 1) / 2] += ((cos_order - sin_order) * table[i][column]) / (sin_order - 1);
              if(cos_order)
                table[i + 1][(cos_order - 1) / 2] += (-cos_order * table[i][column]) / (sin_order - 1);
           }
        }

     }
     T sum = boost::math::tools::evaluate_even_polynomial(&table[index][0], c, table[index].size());
     if(index & 1)
        sum *= c;  // First coefficient is order 1, and really an odd polynomial.
     if(sum == 0)
        return sum;
     //
     // The remaining terms are computed using logs since the powers and factorials
     // get real large real quick:
     //
     T power_terms = n * log(boost::math::constants::pi<T>());
     if(s == 0)
        return sum * boost::math::policies::raise_overflow_error<T>(function, 0, pol);
     power_terms -= log(fabs(s)) * (n + 1);
     power_terms += boost::math::lgamma(T(n), pol);
     power_terms += log(fabs(sum));

     if(power_terms > boost::math::tools::log_max_value<T>())
        return sum * boost::math::policies::raise_overflow_error<T>(function, 0, pol);

     return exp(power_terms) * ((s < 0) && ((n + 1) & 1) ? -1 : 1) * boost::math::sign(sum);
  }

  template <class T, class Policy>
  struct polygamma_initializer
  {
     struct init
     {
        init()
        {
           // Forces initialization of our table of coefficients and mutex:
           boost::math::polygamma(30, T(-2.5f), Policy());
        }
        void force_instantiate()const{}
     };
     static const init initializer;
     static void force_instantiate()
     {
        initializer.force_instantiate();
     }
  };

  template <class T, class Policy>
  const typename polygamma_initializer<T, Policy>::init polygamma_initializer<T, Policy>::initializer;
  
  template<class T, class Policy>
  inline T polygamma_imp(const int n, T x, const Policy &pol)
  {
    BOOST_MATH_STD_USING
    static const char* function = "boost::math::polygamma<%1%>(int, %1%)";
    polygamma_initializer<T, Policy>::initializer.force_instantiate();
    if(n < 0)
       return policies::raise_domain_error<T>(function, "Order must be >= 0, but got %1%", static_cast<T>(n), pol);
    if(x < 0)
    {
       if(floor(x) == x)
       {
          //
          // Result is infinity if x is odd, and a pole error if x is even.
          //
          if(lltrunc(x) & 1)
             return policies::raise_overflow_error<T>(function, 0, pol);
          else
             return policies::raise_pole_error<T>(function, "Evaluation at negative integer %1%", x, pol);
       }
       T z = 1 - x;
       T result = polygamma_imp(n, z, pol) + constants::pi<T, Policy>() * poly_cot_pi(n, z, x, pol, function);
       return n & 1 ? T(-result) : result;
    }
    //
    // Limit for use of small-x-series is chosen
    // so that the series doesn't go too divergent
    // in the first few terms.  Ordinarily this
    // would mean setting the limit to ~ 1 / n,
    // but we can tolerate a small amount of divergence:
    //
    T small_x_limit = (std::min)(T(T(5) / n), T(0.25f));
    if(x < small_x_limit)
    {
      return polygamma_nearzero(n, x, pol, function);
    }
    else if(x > 0.4F * policies::digits_base10<T, Policy>() + 4.0f * n)
    {
      return polygamma_atinfinityplus(n, x, pol, function);
    }
    else if(x == 1)
    {
       return (n & 1 ? 1 : -1) * boost::math::factorial<T>(n, pol) * boost::math::zeta(T(n + 1), pol);
    }
    else if(x == 0.5f)
    {
       T result = (n & 1 ? 1 : -1) * boost::math::factorial<T>(n, pol) * boost::math::zeta(T(n + 1), pol);
       if(fabs(result) >= ldexp(tools::max_value<T>(), -n - 1))
          return boost::math::sign(result) * policies::raise_overflow_error<T>(function, 0, pol);
       result *= ldexp(T(1), n + 1) - 1;
       return result;
    }
    else
    {
      return polygamma_attransitionplus(n, x, pol, function);
    }
  }

} } } // namespace boost::math::detail

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // _BOOST_POLYGAMMA_DETAIL_2013_07_30_HPP_


/* polygamma.hpp
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
*/