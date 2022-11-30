// Copyright 2008 Gautam Sewani
// Copyright 2008 John Maddock
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_DETAIL_HG_PDF_HPP
#define BOOST_MATH_DISTRIBUTIONS_DETAIL_HG_PDF_HPP

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/lanczos.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/pow.hpp>
#include <boost/math/special_functions/prime.hpp>
#include <boost/math/policies/error_handling.hpp>

#ifdef BOOST_MATH_INSTRUMENT
#include <typeinfo>
#endif

namespace boost{ namespace math{ namespace detail{

template <class T, class Func>
void bubble_down_one(T* first, T* last, Func f)
{
   using std::swap;
   T* next = first;
   ++next;
   while((next != last) && (!f(*first, *next)))
   {
      swap(*first, *next);
      ++first;
      ++next;
   }
}

template <class T>
struct sort_functor
{
   sort_functor(const T* exponents) : m_exponents(exponents){}
   bool operator()(int i, int j)
   {
      return m_exponents[i] > m_exponents[j];
   }
private:
   const T* m_exponents;
};

template <class T, class Lanczos, class Policy>
T hypergeometric_pdf_lanczos_imp(T /*dummy*/, unsigned x, unsigned r, unsigned n, unsigned N, const Lanczos&, const Policy&)
{
   BOOST_MATH_STD_USING

   BOOST_MATH_INSTRUMENT_FPU
   BOOST_MATH_INSTRUMENT_VARIABLE(x);
   BOOST_MATH_INSTRUMENT_VARIABLE(r);
   BOOST_MATH_INSTRUMENT_VARIABLE(n);
   BOOST_MATH_INSTRUMENT_VARIABLE(N);
   BOOST_MATH_INSTRUMENT_VARIABLE(typeid(Lanczos).name());

   T bases[9] = {
      T(n) + static_cast<T>(Lanczos::g()) + 0.5f,
      T(r) + static_cast<T>(Lanczos::g()) + 0.5f,
      T(N - n) + static_cast<T>(Lanczos::g()) + 0.5f,
      T(N - r) + static_cast<T>(Lanczos::g()) + 0.5f,
      1 / (T(N) + static_cast<T>(Lanczos::g()) + 0.5f),
      1 / (T(x) + static_cast<T>(Lanczos::g()) + 0.5f),
      1 / (T(n - x) + static_cast<T>(Lanczos::g()) + 0.5f),
      1 / (T(r - x) + static_cast<T>(Lanczos::g()) + 0.5f),
      1 / (T(N - n - r + x) + static_cast<T>(Lanczos::g()) + 0.5f)
   };
   T exponents[9] = {
      n + T(0.5f),
      r + T(0.5f),
      N - n + T(0.5f),
      N - r + T(0.5f),
      N + T(0.5f),
      x + T(0.5f),
      n - x + T(0.5f),
      r - x + T(0.5f),
      N - n - r + x + T(0.5f)
   };
   int base_e_factors[9] = {
      -1, -1, -1, -1, 1, 1, 1, 1, 1
   };
   int sorted_indexes[9] = {
      0, 1, 2, 3, 4, 5, 6, 7, 8
   };
#ifdef BOOST_MATH_INSTRUMENT
   BOOST_MATH_INSTRUMENT_FPU
   for(unsigned i = 0; i < 9; ++i)
   {
      BOOST_MATH_INSTRUMENT_VARIABLE(i);
      BOOST_MATH_INSTRUMENT_VARIABLE(bases[i]);
      BOOST_MATH_INSTRUMENT_VARIABLE(exponents[i]);
      BOOST_MATH_INSTRUMENT_VARIABLE(base_e_factors[i]);
      BOOST_MATH_INSTRUMENT_VARIABLE(sorted_indexes[i]);
   }
#endif
   std::sort(sorted_indexes, sorted_indexes + 9, sort_functor<T>(exponents));
#ifdef BOOST_MATH_INSTRUMENT
   BOOST_MATH_INSTRUMENT_FPU
   for(unsigned i = 0; i < 9; ++i)
   {
      BOOST_MATH_INSTRUMENT_VARIABLE(i);
      BOOST_MATH_INSTRUMENT_VARIABLE(bases[i]);
      BOOST_MATH_INSTRUMENT_VARIABLE(exponents[i]);
      BOOST_MATH_INSTRUMENT_VARIABLE(base_e_factors[i]);
      BOOST_MATH_INSTRUMENT_VARIABLE(sorted_indexes[i]);
   }
#endif

   do{
      exponents[sorted_indexes[0]] -= exponents[sorted_indexes[1]];
      bases[sorted_indexes[1]] *= bases[sorted_indexes[0]];
      if((bases[sorted_indexes[1]] < tools::min_value<T>()) && (exponents[sorted_indexes[1]] != 0))
      {
         return 0;
      }
      base_e_factors[sorted_indexes[1]] += base_e_factors[sorted_indexes[0]];
      bubble_down_one(sorted_indexes, sorted_indexes + 9, sort_functor<T>(exponents));

#ifdef BOOST_MATH_INSTRUMENT
      for(unsigned i = 0; i < 9; ++i)
      {
         BOOST_MATH_INSTRUMENT_VARIABLE(i);
         BOOST_MATH_INSTRUMENT_VARIABLE(bases[i]);
         BOOST_MATH_INSTRUMENT_VARIABLE(exponents[i]);
         BOOST_MATH_INSTRUMENT_VARIABLE(base_e_factors[i]);
         BOOST_MATH_INSTRUMENT_VARIABLE(sorted_indexes[i]);
      }
#endif
   }while(exponents[sorted_indexes[1]] > 1);

   //
   // Combine equal powers:
   //
   int j = 8;
   while(exponents[sorted_indexes[j]] == 0) --j;
   while(j)
   {
      while(j && (exponents[sorted_indexes[j-1]] == exponents[sorted_indexes[j]]))
      {
         bases[sorted_indexes[j-1]] *= bases[sorted_indexes[j]];
         exponents[sorted_indexes[j]] = 0;
         base_e_factors[sorted_indexes[j-1]] += base_e_factors[sorted_indexes[j]];
         bubble_down_one(sorted_indexes + j, sorted_indexes + 9, sort_functor<T>(exponents));
         --j;
      }
      --j;

#ifdef BOOST_MATH_INSTRUMENT
      BOOST_MATH_INSTRUMENT_VARIABLE(j);
      for(unsigned i = 0; i < 9; ++i)
      {
         BOOST_MATH_INSTRUMENT_VARIABLE(i);
         BOOST_MATH_INSTRUMENT_VARIABLE(bases[i]);
         BOOST_MATH_INSTRUMENT_VARIABLE(exponents[i]);
         BOOST_MATH_INSTRUMENT_VARIABLE(base_e_factors[i]);
         BOOST_MATH_INSTRUMENT_VARIABLE(sorted_indexes[i]);
      }
#endif
   }

#ifdef BOOST_MATH_INSTRUMENT
   BOOST_MATH_INSTRUMENT_FPU
   for(unsigned i = 0; i < 9; ++i)
   {
      BOOST_MATH_INSTRUMENT_VARIABLE(i);
      BOOST_MATH_INSTRUMENT_VARIABLE(bases[i]);
      BOOST_MATH_INSTRUMENT_VARIABLE(exponents[i]);
      BOOST_MATH_INSTRUMENT_VARIABLE(base_e_factors[i]);
      BOOST_MATH_INSTRUMENT_VARIABLE(sorted_indexes[i]);
   }
#endif

   T result;
   BOOST_MATH_INSTRUMENT_VARIABLE(bases[sorted_indexes[0]] * exp(static_cast<T>(base_e_factors[sorted_indexes[0]])));
   BOOST_MATH_INSTRUMENT_VARIABLE(exponents[sorted_indexes[0]]);
   {
      BOOST_FPU_EXCEPTION_GUARD
      result = pow(bases[sorted_indexes[0]] * exp(static_cast<T>(base_e_factors[sorted_indexes[0]])), exponents[sorted_indexes[0]]);
   }
   BOOST_MATH_INSTRUMENT_VARIABLE(result);
   for(unsigned i = 1; (i < 9) && (exponents[sorted_indexes[i]] > 0); ++i)
   {
      BOOST_FPU_EXCEPTION_GUARD
      if(result < tools::min_value<T>())
         return 0; // short circuit further evaluation
      if(exponents[sorted_indexes[i]] == 1)
         result *= bases[sorted_indexes[i]] * exp(static_cast<T>(base_e_factors[sorted_indexes[i]]));
      else if(exponents[sorted_indexes[i]] == 0.5f)
         result *= sqrt(bases[sorted_indexes[i]] * exp(static_cast<T>(base_e_factors[sorted_indexes[i]])));
      else
         result *= pow(bases[sorted_indexes[i]] * exp(static_cast<T>(base_e_factors[sorted_indexes[i]])), exponents[sorted_indexes[i]]);
   
      BOOST_MATH_INSTRUMENT_VARIABLE(result);
   }

   result *= Lanczos::lanczos_sum_expG_scaled(static_cast<T>(n + 1))
      * Lanczos::lanczos_sum_expG_scaled(static_cast<T>(r + 1))
      * Lanczos::lanczos_sum_expG_scaled(static_cast<T>(N - n + 1))
      * Lanczos::lanczos_sum_expG_scaled(static_cast<T>(N - r + 1))
      / 
      ( Lanczos::lanczos_sum_expG_scaled(static_cast<T>(N + 1))
         * Lanczos::lanczos_sum_expG_scaled(static_cast<T>(x + 1))
         * Lanczos::lanczos_sum_expG_scaled(static_cast<T>(n - x + 1))
         * Lanczos::lanczos_sum_expG_scaled(static_cast<T>(r - x + 1))
         * Lanczos::lanczos_sum_expG_scaled(static_cast<T>(N - n - r + x + 1)));
   
   BOOST_MATH_INSTRUMENT_VARIABLE(result);
   return result;
}

template <class T, class Policy>
T hypergeometric_pdf_lanczos_imp(T /*dummy*/, unsigned x, unsigned r, unsigned n, unsigned N, const boost::math::lanczos::undefined_lanczos&, const Policy& pol)
{
   BOOST_MATH_STD_USING
   return exp(
      boost::math::lgamma(T(n + 1), pol)
      + boost::math::lgamma(T(r + 1), pol)
      + boost::math::lgamma(T(N - n + 1), pol)
      + boost::math::lgamma(T(N - r + 1), pol)
      - boost::math::lgamma(T(N + 1), pol)
      - boost::math::lgamma(T(x + 1), pol)
      - boost::math::lgamma(T(n - x + 1), pol)
      - boost::math::lgamma(T(r - x + 1), pol)
      - boost::math::lgamma(T(N - n - r + x + 1), pol));
}

template <class T>
inline T integer_power(const T& x, int ex)
{
   if(ex < 0)
      return 1 / integer_power(x, -ex);
   switch(ex)
   {
   case 0:
      return 1;
   case 1:
      return x;
   case 2:
      return x * x;
   case 3:
      return x * x * x;
   case 4:
      return boost::math::pow<4>(x);
   case 5:
      return boost::math::pow<5>(x);
   case 6:
      return boost::math::pow<6>(x);
   case 7:
      return boost::math::pow<7>(x);
   case 8:
      return boost::math::pow<8>(x);
   }
   BOOST_MATH_STD_USING
#ifdef __SUNPRO_CC
   return pow(x, T(ex));
#else
   return pow(x, ex);
#endif
}
template <class T>
struct hypergeometric_pdf_prime_loop_result_entry
{
   T value;
   const hypergeometric_pdf_prime_loop_result_entry* next;
};

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4510 4512 4610)
#endif

struct hypergeometric_pdf_prime_loop_data
{
   const unsigned x;
   const unsigned r;
   const unsigned n;
   const unsigned N;
   unsigned prime_index;
   unsigned current_prime;
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif

template <class T>
T hypergeometric_pdf_prime_loop_imp(hypergeometric_pdf_prime_loop_data& data, hypergeometric_pdf_prime_loop_result_entry<T>& result)
{
   while(data.current_prime <= data.N)
   {
      unsigned base = data.current_prime;
      int prime_powers = 0;
      while(base <= data.N)
      {
         prime_powers += data.n / base;
         prime_powers += data.r / base;
         prime_powers += (data.N - data.n) / base;
         prime_powers += (data.N - data.r) / base;
         prime_powers -= data.N / base;
         prime_powers -= data.x / base;
         prime_powers -= (data.n - data.x) / base;
         prime_powers -= (data.r - data.x) / base;
         prime_powers -= (data.N - data.n - data.r + data.x) / base;
         base *= data.current_prime;
      }
      if(prime_powers)
      {
         T p = integer_power<T>(static_cast<T>(data.current_prime), prime_powers);
         if((p > 1) && (tools::max_value<T>() / p < result.value))
         {
            //
            // The next calculation would overflow, use recursion
            // to sidestep the issue:
            //
            hypergeometric_pdf_prime_loop_result_entry<T> t = { p, &result };
            data.current_prime = prime(++data.prime_index);
            return hypergeometric_pdf_prime_loop_imp<T>(data, t);
         }
         if((p < 1) && (tools::min_value<T>() / p > result.value))
         {
            //
            // The next calculation would underflow, use recursion
            // to sidestep the issue:
            //
            hypergeometric_pdf_prime_loop_result_entry<T> t = { p, &result };
            data.current_prime = prime(++data.prime_index);
            return hypergeometric_pdf_prime_loop_imp<T>(data, t);
         }
         result.value *= p;
      }
      data.current_prime = prime(++data.prime_index);
   }
   //
   // When we get to here we have run out of prime factors,
   // the overall result is the product of all the partial
   // results we have accumulated on the stack so far, these
   // are in a linked list starting with "data.head" and ending
   // with "result".
   //
   // All that remains is to multiply them together, taking
   // care not to overflow or underflow.
   //
   // Enumerate partial results >= 1 in variable i
   // and partial results < 1 in variable j:
   //
   hypergeometric_pdf_prime_loop_result_entry<T> const *i, *j;
   i = &result;
   while(i && i->value < 1)
      i = i->next;
   j = &result;
   while(j && j->value >= 1)
      j = j->next;

   T prod = 1;

   while(i || j)
   {
      while(i && ((prod <= 1) || (j == 0)))
      {
         prod *= i->value;
         i = i->next;
         while(i && i->value < 1)
            i = i->next;
      }
      while(j && ((prod >= 1) || (i == 0)))
      {
         prod *= j->value;
         j = j->next;
         while(j && j->value >= 1)
            j = j->next;
      }
   }

   return prod;
}

template <class T, class Policy>
inline T hypergeometric_pdf_prime_imp(unsigned x, unsigned r, unsigned n, unsigned N, const Policy&)
{
   hypergeometric_pdf_prime_loop_result_entry<T> result = { 1, 0 };
   hypergeometric_pdf_prime_loop_data data = { x, r, n, N, 0, prime(0) };
   return hypergeometric_pdf_prime_loop_imp<T>(data, result);
}

template <class T, class Policy>
T hypergeometric_pdf_factorial_imp(unsigned x, unsigned r, unsigned n, unsigned N, const Policy&)
{
   BOOST_MATH_STD_USING
   BOOST_MATH_ASSERT(N <= boost::math::max_factorial<T>::value);
   T result = boost::math::unchecked_factorial<T>(n);
   T num[3] = {
      boost::math::unchecked_factorial<T>(r),
      boost::math::unchecked_factorial<T>(N - n),
      boost::math::unchecked_factorial<T>(N - r)
   };
   T denom[5] = {
      boost::math::unchecked_factorial<T>(N),
      boost::math::unchecked_factorial<T>(x),
      boost::math::unchecked_factorial<T>(n - x),
      boost::math::unchecked_factorial<T>(r - x),
      boost::math::unchecked_factorial<T>(N - n - r + x)
   };
   int i = 0;
   int j = 0;
   while((i < 3) || (j < 5))
   {
      while((j < 5) && ((result >= 1) || (i >= 3)))
      {
         result /= denom[j];
         ++j;
      }
      while((i < 3) && ((result <= 1) || (j >= 5)))
      {
         result *= num[i];
         ++i;
      }
   }
   return result;
}


template <class T, class Policy>
inline typename tools::promote_args<T>::type 
   hypergeometric_pdf(unsigned x, unsigned r, unsigned n, unsigned N, const Policy&)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename lanczos::lanczos<value_type, Policy>::type evaluation_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   value_type result;
   if(N <= boost::math::max_factorial<value_type>::value)
   {
      //
      // If N is small enough then we can evaluate the PDF via the factorials
      // directly: table lookup of the factorials gives the best performance
      // of the methods available:
      //
      result = detail::hypergeometric_pdf_factorial_imp<value_type>(x, r, n, N, forwarding_policy());
   }
   else if(N <= boost::math::prime(boost::math::max_prime - 1))
   {
      //
      // If N is no larger than the largest prime number in our lookup table
      // (104729) then we can use prime factorisation to evaluate the PDF,
      // this is slow but accurate:
      //
      result = detail::hypergeometric_pdf_prime_imp<value_type>(x, r, n, N, forwarding_policy());
   }
   else
   {
      //
      // Catch all case - use the lanczos approximation - where available - 
      // to evaluate the ratio of factorials.  This is reasonably fast
      // (almost as quick as using logarithmic evaluation in terms of lgamma)
      // but only a few digits better in accuracy than using lgamma:
      //
      result = detail::hypergeometric_pdf_lanczos_imp(value_type(), x, r, n, N, evaluation_type(), forwarding_policy());
   }

   if(result > 1)
   {
      result = 1;
   }
   if(result < 0)
   {
      result = 0;
   }

   return policies::checked_narrowing_cast<result_type, forwarding_policy>(result, "boost::math::hypergeometric_pdf<%1%>(%1%,%1%,%1%,%1%)");
}

}}} // namespaces

#endif


/* hypergeometric_pdf.hpp
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
*/