
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
  #include <boost/cstdint.hpp>
  #include <boost/math/policies/policy.hpp>
  #include <boost/math/special_functions/bernoulli.hpp>
  #include <boost/math/special_functions/trunc.hpp>
  #include <boost/math/special_functions/zeta.hpp>
  #include <boost/math/special_functions/digamma.hpp>
  #include <boost/math/special_functions/sin_pi.hpp>
  #include <boost/math/special_functions/cos_pi.hpp>
  #include <boost/math/special_functions/pow.hpp>
  #include <boost/mpl/if.hpp>
  #include <boost/mpl/int.hpp>
  #include <boost/static_assert.hpp>
  #include <boost/type_traits/is_convertible.hpp>

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
           return ((n & 1) ? 1 : -1) * boost::math::factorial<T>(n - 1) * pow(x, -n);
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
       return policies::raise_evaluation_error<T>(function, ("Exceeded maximum series evaluations evaluating at n = " + boost::lexical_cast<std::string>(n) + " and x = %1%").c_str(), x, pol);

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
       sum0 *= boost::math::factorial<T>(n);
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
        int P[] = { -2, -4 };
        return boost::math::pow<3>(constants::pi<T, Policy>(), pol) * tools::evaluate_even_polynomial(P, c) / boost::math::pow<4>(s, pol);
     }
     case 4:
     {
        int P[] = { 16, 8 };
        return boost::math::pow<4>(constants::pi<T, Policy>(), pol) * c * tools::evaluate_even_polynomial(P, c) / boost::math::pow<5>(s, pol);
     }
     case 5:
     {
        int P[] = { -16, -88, -16 };
        return boost::math::pow<5>(constants::pi<T, Policy>(), pol) * tools::evaluate_even_polynomial(P, c) / boost::math::pow<6>(s, pol);
     }
     case 6:
     {
        int P[] = { 272, 416, 32 };
        return boost::math::pow<6>(constants::pi<T, Policy>(), pol) * c * tools::evaluate_even_polynomial(P, c) / boost::math::pow<7>(s, pol);
     }
     case 7:
     {
        int P[] = { -272, -2880, -1824, -64 };
        return boost::math::pow<7>(constants::pi<T, Policy>(), pol) * tools::evaluate_even_polynomial(P, c) / boost::math::pow<8>(s, pol);
     }
     case 8:
     {
        int P[] = { 7936, 24576, 7680, 128 };
        return boost::math::pow<8>(constants::pi<T, Policy>(), pol) * c * tools::evaluate_even_polynomial(P, c) / boost::math::pow<9>(s, pol);
     }
     case 9:
     {
        int P[] = { -7936, -137216, -185856, -31616, -256 };
        return boost::math::pow<9>(constants::pi<T, Policy>(), pol) * tools::evaluate_even_polynomial(P, c) / boost::math::pow<10>(s, pol);
     }
     case 10:
     {
        int P[] = { 353792, 1841152, 1304832, 128512, 512 };
        return boost::math::pow<10>(constants::pi<T, Policy>(), pol) * c * tools::evaluate_even_polynomial(P, c) / boost::math::pow<11>(s, pol);
     }
     case 11:
     {
        int P[] = { -353792, -9061376, -21253376, -8728576, -518656, -1024};
        return boost::math::pow<11>(constants::pi<T, Policy>(), pol) * tools::evaluate_even_polynomial(P, c) / boost::math::pow<12>(s, pol);
     }
     case 12:
     {
        int P[] = { 22368256, 175627264, 222398464, 56520704, 2084864, 2048 };
        return boost::math::pow<12>(constants::pi<T, Policy>(), pol) * c * tools::evaluate_even_polynomial(P, c) / boost::math::pow<13>(s, pol);
     }
#ifndef BOOST_NO_LONG_LONG
     case 13:
     {
        long long P[] = { -22368256LL, -795300864LL, -2868264960LL, -2174832640LL, -357888000LL, -8361984LL, -4096 };
        return boost::math::pow<13>(constants::pi<T, Policy>(), pol) * tools::evaluate_even_polynomial(P, c) / boost::math::pow<14>(s, pol);
     }
     case 14:
     {
        long long P[] = { 1903757312LL, 21016670208LL, 41731645440LL, 20261765120LL, 2230947840LL, 33497088LL, 8192 };
        return boost::math::pow<14>(constants::pi<T, Policy>(), pol) * c * tools::evaluate_even_polynomial(P, c) / boost::math::pow<15>(s, pol);
     }
     case 15:
     {
        long long P[] = { -1903757312LL, -89702612992LL, -460858269696LL, -559148810240LL, -182172651520LL, -13754155008LL, -134094848LL, -16384 };
        return boost::math::pow<15>(constants::pi<T, Policy>(), pol) * tools::evaluate_even_polynomial(P, c) / boost::math::pow<16>(s, pol);
     }
     case 16:
     {
        long long P[] = { 209865342976LL, 3099269660672LL, 8885192097792LL, 7048869314560LL, 1594922762240LL, 84134068224LL, 536608768LL, 32768 };
        return boost::math::pow<16>(constants::pi<T, Policy>(), pol) * c * tools::evaluate_even_polynomial(P, c) / boost::math::pow<17>(s, pol);
     }
     case 17:
     {
        long long P[] = { -209865342976LL, -12655654469632LL, -87815735738368LL, -155964390375424LL, -84842998005760LL, -13684856848384LL, -511780323328LL, -2146926592LL, -65536 };
        return boost::math::pow<17>(constants::pi<T, Policy>(), pol) * tools::evaluate_even_polynomial(P, c) / boost::math::pow<18>(s, pol);
     }
     case 18:
     {
        long long P[] = { 29088885112832LL, 553753414467584LL, 2165206642589696LL, 2550316668551168LL, 985278548541440LL, 115620218667008LL, 3100738912256LL, 8588754944LL, 131072 };
        return boost::math::pow<18>(constants::pi<T, Policy>(), pol) * c * tools::evaluate_even_polynomial(P, c) / boost::math::pow<19>(s, pol);
     }
     case 19:
     {
        long long P[] = { -29088885112832LL, -2184860175433728LL, -19686087844429824LL, -48165109676113920LL, -39471306959486976LL, -11124607890751488LL, -965271355195392LL, -18733264797696LL, -34357248000LL, -262144 };
        return boost::math::pow<19>(constants::pi<T, Policy>(), pol) * tools::evaluate_even_polynomial(P, c) / boost::math::pow<20>(s, pol);
     }
     case 20:
     {
        long long P[] = { 4951498053124096LL, 118071834535526400LL, 603968063567560704LL, 990081991141490688LL, 584901762421358592LL, 122829335169859584LL, 7984436548730880LL, 112949304754176LL, 137433710592LL, 524288 };
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
     static boost::detail::lightweight_mutex m;
     boost::detail::lightweight_mutex::scoped_lock l(m);
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
              BOOST_ASSERT(column < (int)table[i].size());
              BOOST_ASSERT((cos_order + 1) / 2 < (int)table[i + 1].size());
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
     power_terms += boost::math::lgamma(T(n));
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