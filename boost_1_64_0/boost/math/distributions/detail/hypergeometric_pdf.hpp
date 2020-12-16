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

#ifdef BOOST_MSVC
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

#ifdef BOOST_MSVC
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
   BOOST_ASSERT(N <= boost::math::max_factorial<T>::value);
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
yXApHAmX6fHncKzRpaLdaXpq49I1PY00H41hDGyi6WgKW8Ik2F+P9RtAqgtEfWt83m8AtdD4Wmp8KTAZttF428IU2Am2he1gD9geng5T4RA9PxR2hDP0+HN4OKxDo3o6W7R+3tPrT9XrT4O14CwYDzP0+rP1upmwN8yGw2AuHAvnwnEwD06C87Xc8+F8uFDLvRCWwiK4Gi6Ga2EJvBGWwtvhCrhd498JV8Pn4WXwJXgBfEWPX4Vz4BtyrO3QVb0B1VHZAtvheDWQ3w8ojo7wWtgLXgf7wnVwHLwe5sIbYAG8ES6FN8FV8Gb4I7gB3gJvhVvgbfBReDt8Bm6Eu+CdcA/cDH8N74Lvwy3wELwX/hZuhX+CD6iNjQdhLNwO28HHYBf4OEyHT8BJ8Gm4AO6CBfB5eAm8Ht4EX4QPwpfhI3APfAL+GP4cvmG+3aPrnPBdSV/kt3s+Vxskf9FHqG9gF5jAjb8b/KvaIvmblqMYBQUBeI7KnQdrwZmwNlwM68CrYAz8IYyFm2AcvA/Wh0/BBvB52BC+pPG9DuPh23r8OWQI0jUkxkut/xRcnNb/SLVdMw72gOPhcDgBzoArYB4829HxAl4KJ2t9c17SNRU+CKfDp+H34Ntwptbv+fBDmKH1PBv+Di6DlInEkwBzYFuYCzur/wA4F06Ey+DZ6j8bLoBz4SK4DBbA61TuepXbDJfAx2Ap3Kn+aitH1yTom1rPXls5e/UbTe/BePg+bAw/gE3hPpgC98NU+CHsCn8Dp8CD8HvwtzAbHobz4AGYr8f6rS2d52aMx23xfWuLvMl4tBwmwRWwox53h6tgX3gJHAhXwnQ51nE8oHOTOke9BY7GpesegyuROxPeCLPgejgX1tf7wU3aDu+D98L74UPwx/Bx+CD8KbwDPgvvhL+Am+Gb8C74a3g3PADvgYfgw/AP8BH4R/gY/Bb+BP5Nr1uPRN8CE+EG2AzeBrvBn8Fp8AVYAnfDy9V/I3wRboYvwXvgy/AR+Ap8Au6BL8JX4T74OjwA34CH4JvwL/CXMCFAe4DN4a9hG/ge7Arfh73hB3A83AenwQ/hbPgRnAMPw1L4O3gR/BheBY/AtfATeB38DbwLHoT3wgPwfvgZfBx+DvfAL+E++Ef4Z/g1/Ab+CTaJYnyC7WCAeuwHo+AgGA2HwDpwCoyB02A9WASD5bgC1uV4NYyDa2B9z33laAe1MWW5r6Sp7Z2+sBUcqO3xdDgGpsPpcBBcDofAy+EoeA0cC9fB8XADnADvhJPgDng2/BmcCZ+BWfBFmKPtbR78DOZpu1oAv4b52q4WwkBw3IB1YAGMg0tgIzgYNtXj5rAQ9oBF8CxYDHNVbqHKXQDPhRfD8+AqOE3bI+f1eUrfWWFXy/NUR7XJ0wnGwM6wPjwVNoBdII5jjS/8Hge7WeLrqfH10vh6a3z9Nb4+8FQ9pp7Fpk+Pj7HZA8fCymz7DMCOzzSc167PbMK8x7mj/B1/VrmNn72fRtr5mXYCWz/HYNzEkM2ftIlVs/uzg7/349pP4jzuCvzmwfWwFPptAdU6ig0ftQn0GkyHR2HYNlDy2RXbByo1NoLwP0p6+Xsrf+/C2ewFxQQftPm7ExyKq8h2UCl+G3Ajh3AO+u0IzTxabkuoEFeG247b67ErdGxy5baFkqcQX9APTsKF7QzNm2JsDTEo4IcL2xxae5TrTIm0PZRybuX2h/Z7bBA1Pq/cDtFMuBK3Ebf1aKRdor3VtE00Db9S3AbcDlxFtoqOTC23V9QeNx6Xj1vrs120cVq5/aLd/H0Q57dj5EwnrbATHIubjXstKAM34PbzdyH9YB3uSdx+XK0jsU4n3FjcbFwpbh1uG2437iA=
*/