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
      boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
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
         int n = static_cast<int>(static_cast<boost::uintmax_t>(boost::math::lltrunc(-2 * a1)));
         T smz = sqrt(-z);
         return pow(2 / smz, -n) * boost::math::hermite(n, 1 / smz);
      }

      if (is_a1_integer && is_a2_integer)
      {
         if ((a1 < 1) && (a2 <= a1))
         {
            const unsigned int n = static_cast<unsigned int>(static_cast<boost::uintmax_t>(boost::math::lltrunc(-a1)));
            const unsigned int m = static_cast<unsigned int>(static_cast<boost::uintmax_t>(boost::math::lltrunc(-a2 - n)));

            return (pow(z, T(n)) * boost::math::factorial<T>(n, pol)) *
               boost::math::laguerre(n, m, -(1 / z), pol);
         }
         else if ((a2 < 1) && (a1 <= a2))
         {
            // function is symmetric for a1 and a2
            const unsigned int n = static_cast<unsigned int>(static_cast<boost::uintmax_t>(boost::math::lltrunc(-a2)));
            const unsigned int m = static_cast<unsigned int>(static_cast<boost::uintmax_t>(boost::math::lltrunc(-a1 - n)));

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