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
wBLKDi1hwzBSIUCCgSS5yWKbAY3GE7/6l4ZJy+cpLvf+tgbSyM6aFL0ljYkpw0lHi4A7cuJ6cxda99ZsbqLlNDDtuF/LK5mlprynhkYbUWOduI3v7mHr6mlLTqqqVXuyW1HkYw3A9uTn6wY3WsJdedLvGL4/5P0G6ManlYI59X2hhUR7/Fj4qCJx52Jdvc5iqxf5sh1qId3DU6AyjlUUftYbYGkXGPq8uaQ3nd/qgwNzaKCKXSiUcB4H60/NOctogiuiFB9wpJRifhgu+qm8l2gizL9oXWx8KotFQbH4UmZm+GPUKSeFLYTnPbihmBdjtPt3sJOoMGE7AZwPuOdqEO2NNJjoS4fR0K7dWh3GI3bZhSvsLtsdqhN4UFaDnDbPNBgGU19RtHnRXipe2Gcca+5KOcyfyX3Baj5Z/PUZYoa8FGudtcs/0bS9A37El2P9oV9xCdD6DvCP1woTam9q3ndRTCz1n8ErBTzNGjXXWAl2K9U97PPLyw3NGv1/aha8WaI5H1pXu7+vVLm8PXOw4XJJ4LzL8Biluoi0acZ2HQC7qzsfreJyX3civ5qKbHer23Fn+5It9rK7VBRzFzj8s2DyE5AIFUKFu2pbm8kBt8C6l/suIp/5oWPctyuqXNM9JpZ9ekptOIogS+BrHiK3eMqgn7j5eY5U7oD8p/oWSvXY+0IUvJpuJ4FZejk3FSrheQVPCS5Swi4zCVJcj9xCH949inARO+Nxx9nhlQZY19bOZsKssoMAQGVnQfz+7JqJeuFUM1kyiDvmgMLwOaMayFzV/YArcqGKSRqbyZT/Q/lD6g3xuAdFsPLDN2S+H2ZuRuFqJbdniqv3DcCwAhOypUutQtJQbMCzWjP8aieltMf2augrVeg46/jIZ03NSk6IFdhAPTu0vqf5KHAdLTI/YwMEVr5QVA6aY2QUjeOAuxdIfpCEK33WWM2VNdY1SdsuCHIv9NnC0RmzfFB9mrahxT0YmGNyqB4Gln6aAWmN7mfbnndg0fEPahfrvWfL6ODp5GGFWGz2Rnw5NkFdPsjF0QTpLBhaCBoxvO0odhu0kYVXqMc29o2Hv/oGWFKQqJQUAf8SRw0NLa2dnWio2d6Sui1W0eciqkP38+4CAqE3dFt3xkpAFLpFL5an4q/7hNqYs7x9EDulooMkksEfcEGqN+az8MpOMIXXXjmsDhSkJilf8ckF3ckk5VHFWG3FjaRHKUj8vD+s1/qC86RQYeae0UeO8aah4hVOD6E34/8soF+4wMZRICdw8D5WbEMlRhiX5v0J/oVKFJIRLNgc+ZEavTspew11ElCxbP4zfxz7Nv7o8wpZhqX1+rELRGP2rtBVQmMl1fRfiYYBRxgmFQBiv0rcAsItsyBXDYSWY6LE51aIAeqnx/3dU7lhYpcfeMVGsJC4Z7M2t13N2B4dzU0roA0vO/0EwaBxsyZSbuoK6+IshisEOHHlYLAKWiKDKGpjLKXrIIh8Xne3CSdW7DaZ25XIjokToxymg9utKQO8B/W1DSqkLBKSWbQs2NHC+HG+kB+nb4W1VoZ6g/P9pOTQc9E1wst9Xd25emocUj/i/RVCcmDXhCEPQr36zVjxJIMrUf1HbYm7ePPQN4UtWf+0T1M6F9jG2a2UBZy8a3d00uI1WlSQH0dQ/HfYreTqIQ4vEVLrlB5ujZJEjsA+SsM9N5Diz6wsgvfcTFvsx17eNsS5Pre0wlpvvZzMWTPLxCJYln1yVMAnkkQ/4g5YPR7YnpjnYPZ7NpOS8w7nNbtnzlXfvXzwOuZkJMkaEwpBfNGnIoHAu4kkJsn3Yq86w9tuOeqs1KyqFfuSahbuAERCoYm8X/W9ytJ3l/hAx7pbtwxo9RRllm+dvlwwCd5SEL1cjJlPcL+MGaZ0Q3P6rLNdYZSkPB0zMfC8JWw76seAl/6eEnlYdzzQaCfE2WlsHXXZkQqDIxLAWXrUuJID3GDiE4TqxzYht1+JBKfmbgNJ8YSIvdBc82wDecWNYsYRkWbhejBr3WjIUmd9NsIO7yeKRI2c+/+Vm0GDs06/NVvCLKPEXRTIWlsn67sAGYzLAAIs/dPXI8AbzC6RSZMl30bmYGKZLYjHImqiPcnm6/drr78V0KrgNeqoGkoyQ7+/N+l184mVW+aOCS8PGq8D8TzJY90ye8Vcf4GUp9HeMkqNv3qyepAdoHH6Zm2tdOMiW7OM8Q/+inx/b70pHmxyS6wI9+KmzqTL+qyE+rxznNWPm1JC3Gghp9cCR9r+cKxAbN/GnVMvNrKI0fMnmdqkExgYrJrs36OEoy0gTx42DdRwiYMqhp5K/prD1QrveedTLQmKcHloqv5z9pEJN0AASSMFr3wgBHaujdHeD0MBFrM1dBiY4Rr8Y7Pirnqz7fCjX37nmRaaUnMcDYLrsNVW6QQqR5IVmu1F4o3iq8Yt1aTZgRcq+Q/HLtOaG06eINA9QphbMlKy1gPnjlPYv9T2lTK+a+bA/CrI4om74s9celUMOBcrFWv9e26o2ykkT8M3CqgY/NQkq1GT18InQgijgcitRy9ONdq/C1gaV3twAe4sDflAR0GOWw/4jcJghjMVMdxh1HT5A+mzTm4Z3/slywtQ54J9OzmdP2WhZbBrTGxk6lMYs7UCONRgBRcjqA3a2B/eE/LDhqLFQvhqgjxw3B6SAV3VQH9HN8A3RdmhKyByY3HIgHuNidfEWaTiW4FyIdTVoPt1k97c+jR24/Rgc9r6bmwhqfU2miHCF1gbSwNQyM8vWKdBe/EUOF/DcGAd4IYDntB6VMzOnj6ou9qUmaJGPJ+oobbz5UPJ6HKailStL/alsOykdFgDUXjXoK5WVzIv3zbXbVWx1C8lvn5ofA02mcgqFD3p5kR3T2gUt6fUuFuwEbNKqHyylK5zgtJx4RfbaPf8+T0eFZ5Gs6Xn8MyFyS3fQKZOCnh99wBinu3WjEsst2FoYOnYfADNyz5C8Oe5qnfu7BgrDw3IOym+cKdLBuiOFww2onyd7UIsb+x/WA9Ha4kpkjH9NHa6w+nsLoGI3hBfntLtP89cCUJGmWy8Zj+K/kVO6emSQOPK8ZvBEnq17gPKo5jXv2RR7lXoC7LKdYC+3qlbFGnrEmv7S2Ize/G1ptzm3KQoIl1zhzxRowSEQw+RYAFlDqQjAdnEjvrg+yJh19LI7PNaW4z23lFdTAS9FgkfiJjzCF0B2lkmpiAQnpR46/ekzNRMvqcYXmn34PylkpnRk2cw++MKrRD67HEWPngOhZirz087ZkK7EC2BfWvQJHQRCB+KHHdpi3fcOMoGIhmtOfD3oy25LX1v2lVQ99oN7vHcR0xDUrdD2W0YRR4BgHeOJKW21llYeFbPyDd1iATzgeJOSx/ySswqvjwBP3VzKho8GD854ma7k8uUgAA2SZN/s8fCHDvUcRUuiwyZ6p8/7W6qrWmp9Ybvp2dbRdJnfNn4uXAS0MoQz7dX/TijEjTUk0opyOd8eanjxBGaxMeKt2yEta5xdnOb8uLcpVcx68tfOjifYhYhFvaExpB3nNMwpsfiADaFVBZUNF2mObc2x7cj1cHpUkM4GefPv2AmLsDMDWCqov2jRmb5zYZy5ikoMxAJBI0+Lz1RJVgb3OinvjgT/mqAx3uEMpeosgtEu0F0HrcE0DkoFZToZvLQB4UE9TweB438fKlg8GFfidyIvD6Hp8ReYiTNgapLaIJrL7GAwM9yTjUd04C53XOP0SMMZZX+N1x640TrTtpQ5uGUfHdnPdR3sMRwbiN2CnH4oSwxurugUVEygfh1aLzAo49wvFJs9Z+IlnWaH++e+m9GRuA4amNAmHyr+0tM2xSWP7VgMLmwcUDFmmjX/Uicg+gX0mFmHBlaVfixTeDgNux2d38f22/ebpeHyvebQD+uIFwVAagtsjlbTWlVXGaVMqUKRZ6863VKnGjf/l6eSwOUrgHFd068zgH0lXZgv4AaCRxb70714ZLEO+PD8l72gl1g7mvJMB53UUK4dE7z8YA9pwk+gqUngjzljUgCn4wUJQi/pcHipFqfHw49f2hq0/2z4kZKiurbAAhajlJC1zO9C0gs+LgHH5bcgpNGemuh7eubovbis/qTuGqR8Kiu9Yz6NFUNceH1UcXaVairOM1sG+LXMgputrC4d5mS07Voyx3avbK/ylN5vCz3E3ZIza9i9v6o0Q0uYDiIsG+8+iA46uUL/WW/yWPnD3v7FNRPGSWekeJTay3OTYLxlhvnMJkAopq5+sQs9eTgOxQ+ASt7DDoulZ/3nb0cuGniamxd7yPlYYDRas9DRInDmEOGwGa6W+Et+9rr3qkbGFaIkgnKE1R+2rywiDscfMJpew/EScI9HoXwUjPkORBUDI6sv9d3+/jA5eOXKfZQLCsx/1SmZ3YmcsKPQQw+Z3eIII3pvwLzAxlLK9fQSwDKTboQAMxPzAxAQzAs/fgNj05PD0wbgAJkMjyfl5evOfY8akd+npvqLzdPOtD4vluWt9McFQdiC0XR//O5OoCNA4kRobTIs7E98wfmDZPJfOcBgE2euanyNlcyEi3qX3LDGa4B1aJYMQ5sFTmQqmT+7vltdSYZs+qx88ui07qjmed0Xa7v8D6+TDCLzEgfiJoEdKek+XUaWMjZRC3ySeQHmBmd/ra9rEZa8qzd1qtOk1vGgDbyD6lvtWRCt6pj69x5vYfIzF4HoYz8qRrTVrEHVBkdJKhqhe5It78FEi423zA7voNpy9DY+rtoGE4EIMOZwqpBglRGnEGPSciLifU5kljT6NZ34L7JWmvYOotEoutBHvb3T01AY0Y/Urqn9+xqJZG7egFYopzFnNyBCQTao0KGuCAs3FbG8KpH/SfaNpmfM6tbOAHEMtezER5yUmrZY9hdXmcK+B8tPe7KzU6zLTvqA8W3DoHh0iOQIio65H872Tz1asl/tJCUN0Zj7sEPwgLgs6uW6S5sxh8xzaCwNIdBg6gItaZjLBp5C8OrwQFeN2V6ocQWPQNDThN2k+Y1v5MFh7K3Qst8Z4tZEXKOy+Km8CmiwyXGZX8wvJGv0JHMuKRN2e0LuedwKuVBUYxO7+hjHKKpolBIXvS+ebM0Klk829I7On/0+QMs+jtM+sHFxu+bkHvPgcsjVxeeVVdU62RvyJIgxduAWzk8uki3I5tQVR+T4eTJuw0+RSJLigKu3xBTwpDjv65ijLqTj7BFaUuvr7H+mof3YegrxVkw9y6aiRMKy56itTG6P3gqaEJETSEC7yveBU8eb+jVLz/QqUlwkVqGZ66T85ipxgn8KED1pqx7UBA9PY3s4jxzJZoI/7O9Gv67S7qkrKjb91eJtYouPMUGVCc091BKk1fhs4KiqxbZoVvwSES7LOP4RLRV4IDmR5rxNQTUdTdYe4Il8XzSetyY82K4phDbE+7ZC55Yn16+WpwF0VQ8vTXWjcCcW8+K/I31lfgew1XWt/cZ0K6uJA0Y7V/KNAj2N/D+cIFYLoZ+RiVNwwy909GRWxctAhybtkvHKytTyRNx6VQXW892iwzTVJOsZJGvi3mA4Wg1N5rleNWp2YFYRd0k4RNU/eOF896WdPdEoBm0BU+CzAROr3NYm89I5W4DB7tdtGF4Q4DNg70t6VHAIoZ9T/ag4/FhAM5KWbIrFzuQD9lRhvQWiie8cuekj6w7r2CYronZZbEUWjTyKPwBN4vBlP5OS4xhnkwSKi2GDJKkuM8yMGIGKtZHJ6Etc+MpFYEfOKl0ZxchQMTJmbH5+3Zf4ttxvTLe7YI61sKnJRShqfpVvxlhDoZX10bl9Rf6Fci0DtYzkoO6G5oYeOOVnh7wzdlLy0Qeb9tGA8jjelYvB6FpHoYDGgTav27E2M/dn8YqH+2IF/3HT/JtRjzOUfTj0WormGP+0zyJ133TlCScCxEOSVRRa5rNkpDusUEBR979XUtdgb+raM1dQKpRokq1M8XgNAPzByMnwEDluthB8eB2iAvXRnjpI3nnBXE3XbH07eZkEwEAp323Igdzc3PeUK8b8Y0pfLsJxyd0/wbJmFGSO3Rj8wPuxm726YSc62BXWoUzdYP3HE+O7GLn5fQKAPpsaw+Di8jx+tnU7uSVc7MNaOqb3EfSDrwYKCxZJmFG/dcjSQV5W5G2Dp+YOPVdeBzPK2DXDtp2eHakTk2+d+bDoQVMh6yG2XUlE1JhFHM++HlH+VkA14ek8eF47yNTpz3aPmNccfy52B6eC0xHqwYdbc22VKxo0C6m02tEWIqsE6adlusb8fGgwAc/YrTbm6pNVDp980xzBl7mSC1le2SLSUSKlciljAEamc2Mih1pLDxGCHMuPKn9J0/HbhQvaKZficcRC1WkZZbG4O3wCq8p/UVGtgVtvadbCqKcuK49UrP/uMxbPZ3aP6BHP+flIfjXmmLPCOJL/y1fQkLi5BYi9CAFEGpRCX7RHR5Oajyud+WN5/CCoG9TCZvoZdMfPQeDnxmBO63mr/P2VnrK95lt6aB0mw0MTdoGAEpvphJc8ppI6DdwENSYUFGAzDdpdV/hd5zQkc5OCZi3796i0+44FYCaX5MbiNnL41u3mbwUC/VjVwopdENYOJ0uZReEHsj8tGhsUhgy7A+6VbDl3aug/8FQONsdkid26fPl8N+dWfAP46dG33yymVIGurIK8nc40QvH8I3ZHyRz2dudzN/GWZur7VcN4OOZ7HJbmg+Bn5dQM741COfH4CbushHtDfHLi6PQp42fpS8Ih5wUFgWkPCq4k/2jTa97Q0SUNV5hxv/Jq8IwHlJwtrefV0cCX5/8V4CdqcO5OjQd3qW8JT6+/WetA3aqDeru7oy0z7Gdh5vojzvjrv2iqKNtZyvDcexuLKtjmNVd4f7Nm6CLTe10Qum5t7mWFUJjCqcqhSt0/5aCms0iuK4O0BslasZXM58qcKawus3qv1lka308Nb50eU7PBld0f/Yhvu84NkfOfD2ci+QVRy2lZhFi2cskpi9Pnm7+THC7D8FTktUVwPO5ThlalSdwCPMj2R0JXMUPeX+ab5rhVPV7P5EPfcg2l2VADq7CzC3q++GzQdIqpaGiNSooyQqR+qpFFJ9Jy0TkPC7eUQOMRIl3FdQ6YSFVw3BU+TtBhfDm9rEiRVY2pisUZWgBj7+IUavcL8z26X3yRxmN5cd90PchAjxgPQzt3m5ep1s9it2+31x8VhfZTUlFGhaFHTkh8dQnMvlBsvr4VX5dwFvDJyu8EBZ1pMrdSezUmoianxQfC3d9kAigjnZhsVh6IIRSnbwwxlytIRQ5JTHvsgfjaYsFecP8ncAB2XvdJX077PSWwDifXTowCdzetYEAOSUW6dTMxTh1HyJIeJmFn77q/gtzXh/wvoVkSX/9aIBJfS16/8SA6jmUhwWJhQ2+aZz0CcaF4U9xKXgKaS/DDxvvpwgbVkPcQ6lGivjHJAIfPAmKI8pBqyU6NoNu1SjfXTrRYy3SHMP9QGv7BF0WXbp++vzE7a9WtmiTybJ2aPa1m+5z3YxGfFrQ/vkTnkQvZWpfz/lmx9IL5DRM7m0pHFOoY/Innd+1JKpEUICUzRvhZ+GvU9SIw/Ah7uKzil+QIGXV9AVXI3A8GoN3rGB4jf7ApkwKwYLDUK4J4mTE/COjYJatMSO/03qniFOUsDDtWFsOA/Peg3ORJZY/uoeh9C7ljG0vm7k9Cq8mKCvBHIiAbFK7KojgjIR6CdVECYmVeItNGXl6BEzTEHT2oqrvPl6j3xxRKBJucJCdXCMUTr5fKOpjb5MG6JPc9dFRqYoGNEQYzqLMsuSap5SbVYRDMMLtkvrfwydQRm/FZPAaBADWwLFndhmCbppZTiTTF1zy/ca6uG6ss/06LONrlNDwgj8TdKpqe1sdE8u9BqAfBgfwRwDmECa408RWcTtXKhr/xNr7SJuPJn+qPOt2PEUtEaWov3mFZ4TsmisE6CzhHswIk3tLQRMmEbIyQ5InAeuwaYNAvvPuw2Ek54NUhEh0vdxJXHDqeckIibQVxMFCK9SxzFxJAk0NPwGjQtNRLG0eFRm2H+oY9M1Bz+hPKV4hMGAptDrdxKnR9CJiSRjBiTbRZH0f2yBl4u3FCNL9xPXlW03lJrKO7l+lPrTmfhhIUWF1pRdoBd2O/uEP1krUaH3hGYb1SsMVrgU9s/+UOOORF87pgd1U0hGdkRikdLTqlEWVFG/mTrDBlMOvvSl69Ge9N4pQjcYZROJ1gJttZlDtxDlVi/KTPVTFBXK7MK3hbP2I2p0SrhI5+ifbYXoP728AZIquSRfUM5AynY7g9oaTOZ2vXP4Lmis+SyUa1W0iP6h68+ZifFAu5r+/RjfFGcOUIDjC2TCEDTK/80gP8Bu0g5qjz4joytzxO9vEN0lH8+pafgEkWWZ9CplCaq0aQf/YG+YdCf7dt9Pyg1/BVkNGjoJzx4ufifMqeNqxwBvZNO+2kgHikL2mxacW/Ulah6W68fT1MlUmgRK7l3ads2z+uEqZP39tiUXfx4tpKf3ttpHNacRV7aEERJ/sUPFE9zUdgCZO9gD7FWUvWoDu9w4as+O0Th5nk1UQ6Mmd110GFbGLTrYAntaQTvrK4imxiCAxjUTDDlXmw/oC9R7NuvnSLNbatKuakef6sGcZAPIPTkTz4zW2tnksrpav/7TNEXTlCdwCYETdAIMFRwhzAmFAE/WHUJlieKkbrpr1C6tC1nS7jjZ4H+dcr1SgzPqvIzm4/w3Bl6Adkf0D8wfNBGGLzrwGsaPSQevZqIZWNkJa5WaqqkBexs21SBLnzbg2n5biYxgOezIQBCvUgk43j9gWm+znn0PUW2qTwS7rvdiazM1eb++uG/LgoikAZboqmModIBQ0Rs7hTYAxmt/qLCGCq+I8rap9EfzfZEV9xZWnkZUG1utb4ucEhNZMA8tNRI1hHunhDw+EcOuhcULDIf7RvLPnUordiuMLrURxjTw/wyFnJFTDRJzIusbmWm7hivBbB6V11GcfNFxtJ0vdJOxMrwz5uyGJBGSjYUVURlQ4ut3IXSEMtKGG8vdx1cllLFi3VEP4xzbBZDeu7LQATrA9cEYQTpPJNhxUfXobYNnQOOVD2FBNSGYCmPeDKDfgb6/mZCF30UHb/rmO3Fxz0EGCWt7pvXscTYiweR7P+GOCTQq7TaRgYY860etTmEoMvMv6fxbEqlenwFeIrJHjsbs=
*/