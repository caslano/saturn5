///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_HYPERGEOMETRIC_2F0_HPP
#define BOOST_MATH_HYPERGEOMETRIC_2F0_HPP

#include <boost/math/policies/policy.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/detail/hypergeometric_series.hpp>
#include <boost/math/special_functions/laguerre.hpp>
#include <boost/math/special_functions/hermite.hpp>
#include <boost/math/tools/fraction.hpp>

namespace boost { namespace math { namespace detail {

   template <class T>
   struct hypergeometric_2F0_cf
   {
      //
      // We start this continued fraction at b on index -1
      // and treat the -1 and 0 cases as special cases.
      // We do this to avoid adding the continued fraction result
      // to 1 so that we can accurately evaluate for small results
      // as well as large ones.  See  http://functions.wolfram.com/07.31.10.0002.01
      //
      T a1, a2, z;
      int k;
      hypergeometric_2F0_cf(T a1_, T a2_, T z_) : a1(a1_), a2(a2_), z(z_), k(-2) {}
      typedef std::pair<T, T> result_type;

      result_type operator()()
      {
         ++k;
         if (k <= 0)
            return std::make_pair(z * a1 * a2, 1);
         return std::make_pair(-z * (a1 + k) * (a2 + k) / (k + 1), 1 + z * (a1 + k) * (a2 + k) / (k + 1));
      }
   };

   template <class T, class Policy>
   T hypergeometric_2F0_cf_imp(T a1, T a2, T z, const Policy& pol, const char* function)
   {
      using namespace boost::math;
      hypergeometric_2F0_cf<T> evaluator(a1, a2, z);
      std::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
      T cf = tools::continued_fraction_b(evaluator, policies::get_epsilon<T, Policy>(), max_iter);
      policies::check_series_iterations<T>(function, max_iter, pol);
      return cf;
   }


   template <class T, class Policy>
   inline T hypergeometric_2F0_imp(T a1, T a2, const T& z, const Policy& pol, bool asymptotic = false)
   {
      //
      // The terms in this series go to infinity unless one of a1 and a2 is a negative integer.
      //
      using std::swap;
      BOOST_MATH_STD_USING

      static const char* const function = "boost::math::hypergeometric_2F0<%1%,%1%,%1%>(%1%,%1%,%1%)";

      if (z == 0)
         return 1;

      bool is_a1_integer = (a1 == floor(a1));
      bool is_a2_integer = (a2 == floor(a2));

      if (!asymptotic && !is_a1_integer && !is_a2_integer)
         return boost::math::policies::raise_overflow_error<T>(function, 0, pol);
      if (!is_a1_integer || (a1 > 0))
      {
         swap(a1, a2);
         swap(is_a1_integer, is_a2_integer);
      }
      //
      // At this point a1 must be a negative integer:
      //
      if(!asymptotic && (!is_a1_integer || (a1 > 0)))
         return boost::math::policies::raise_overflow_error<T>(function, 0, pol);
      //
      // Special cases first:
      //
      if (a1 == 0)
         return 1;
      if ((a1 == a2 - 0.5f) && (z < 0))
      {
         // http://functions.wolfram.com/07.31.03.0083.01
         int n = static_cast<int>(static_cast<std::uintmax_t>(boost::math::lltrunc(-2 * a1)));
         T smz = sqrt(-z);
         return pow(2 / smz, -n) * boost::math::hermite(n, 1 / smz, pol);
      }

      if (is_a1_integer && is_a2_integer)
      {
         if ((a1 < 1) && (a2 <= a1))
         {
            const unsigned int n = static_cast<unsigned int>(static_cast<std::uintmax_t>(boost::math::lltrunc(-a1)));
            const unsigned int m = static_cast<unsigned int>(static_cast<std::uintmax_t>(boost::math::lltrunc(-a2 - n)));

            return (pow(z, T(n)) * boost::math::factorial<T>(n, pol)) *
               boost::math::laguerre(n, m, -(1 / z), pol);
         }
         else if ((a2 < 1) && (a1 <= a2))
         {
            // function is symmetric for a1 and a2
            const unsigned int n = static_cast<unsigned int>(static_cast<std::uintmax_t>(boost::math::lltrunc(-a2)));
            const unsigned int m = static_cast<unsigned int>(static_cast<std::uintmax_t>(boost::math::lltrunc(-a1 - n)));

            return (pow(z, T(n)) * boost::math::factorial<T>(n, pol)) *
               boost::math::laguerre(n, m, -(1 / z), pol);
         }
      }

      if ((a1 * a2 * z < 0) && (a2 < -5) && (fabs(a1 * a2 * z) > 0.5))
      {
         // Series is alternating and maybe divergent at least for the first few terms
         // (until a2 goes positive), try the continued fraction:
         return hypergeometric_2F0_cf_imp(a1, a2, z, pol, function);
      }

      return detail::hypergeometric_2F0_generic_series(a1, a2, z, pol);
   }

} // namespace detail

template <class T1, class T2, class T3, class Policy>
inline typename tools::promote_args<T1, T2, T3>::type hypergeometric_2F0(T1 a1, T2 a2, T3 z, const Policy& /* pol */)
{
   BOOST_FPU_EXCEPTION_GUARD
      typedef typename tools::promote_args<T1, T2, T3>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;
   return policies::checked_narrowing_cast<result_type, Policy>(
      detail::hypergeometric_2F0_imp<value_type>(
         static_cast<value_type>(a1),
         static_cast<value_type>(a2),
         static_cast<value_type>(z),
         forwarding_policy()),
      "boost::math::hypergeometric_2F0<%1%>(%1%,%1%,%1%)");
}

template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type hypergeometric_2F0(T1 a1, T2 a2, T3 z)
{
   return hypergeometric_2F0(a1, a2, z, policies::policy<>());
}


  } } // namespace boost::math

#endif // BOOST_MATH_HYPERGEOMETRIC_HPP

/* hypergeometric_2F0.hpp
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
*/