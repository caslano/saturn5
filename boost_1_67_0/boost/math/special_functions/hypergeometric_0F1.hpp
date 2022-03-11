///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_HYPERGEOMETRIC_0F1_HPP
#define BOOST_MATH_HYPERGEOMETRIC_0F1_HPP

#include <boost/math/policies/policy.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/detail/hypergeometric_series.hpp>
#include <boost/math/special_functions/detail/hypergeometric_0F1_bessel.hpp>

namespace boost { namespace math { namespace detail {


   template <class T>
   struct hypergeometric_0F1_cf
   {
      //
      // We start this continued fraction at b on index -1
      // and treat the -1 and 0 cases as special cases.
      // We do this to avoid adding the continued fraction result
      // to 1 so that we can accurately evaluate for small results
      // as well as large ones.  See http://functions.wolfram.com/07.17.10.0002.01
      //
      T b, z;
      int k;
      hypergeometric_0F1_cf(T b_, T z_) : b(b_), z(z_), k(-2) {}
      typedef std::pair<T, T> result_type;

      result_type operator()()
      {
         ++k;
         if (k <= 0)
            return std::make_pair(z / b, 1);
         return std::make_pair(-z / ((k + 1) * (b + k)), 1 + z / ((k + 1) * (b + k)));
      }
   };

   template <class T, class Policy>
   T hypergeometric_0F1_cf_imp(T b, T z, const Policy& pol, const char* function)
   {
      hypergeometric_0F1_cf<T> evaluator(b, z);
      boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
      T cf = tools::continued_fraction_b(evaluator, policies::get_epsilon<T, Policy>(), max_iter);
      policies::check_series_iterations<T>(function, max_iter, pol);
      return cf;
   }


   template <class T, class Policy>
   inline T hypergeometric_0F1_imp(const T& b, const T& z, const Policy& pol)
   {
      const char* function = "boost::math::hypergeometric_0f1<%1%,%1%>(%1%, %1%)";
      BOOST_MATH_STD_USING

         // some special cases
         if (z == 0)
            return T(1);

      if ((b <= 0) && (b == floor(b)))
         return policies::raise_pole_error<T>(
            function,
            "Evaluation of 0f1 with nonpositive integer b = %1%.", b, pol);

      if (z < -5 && b > -5)
      {
         // Series is alternating and divergent, need to do something else here,
         // Bessel function relation is much more accurate, unless |b| is similarly
         // large to |z|, otherwise the CF formula suffers from cancellation when
         // the result would be very small.
         if (fabs(z / b) > 4)
            return hypergeometric_0F1_bessel(b, z, pol);
         return hypergeometric_0F1_cf_imp(b, z, pol, function);
      }
      // evaluation through Taylor series looks
      // more precisious than Bessel relation:
      // detail::hypergeometric_0f1_bessel(b, z, pol);
      return detail::hypergeometric_0F1_generic_series(b, z, pol);
   }

} // namespace detail

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type hypergeometric_0F1(T1 b, T2 z, const Policy& /* pol */)
{
   BOOST_FPU_EXCEPTION_GUARD
      typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;
   return policies::checked_narrowing_cast<result_type, Policy>(
      detail::hypergeometric_0F1_imp<value_type>(
         static_cast<value_type>(b),
         static_cast<value_type>(z),
         forwarding_policy()),
      "boost::math::hypergeometric_0F1<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type hypergeometric_0F1(T1 b, T2 z)
{
   return hypergeometric_0F1(b, z, policies::policy<>());
}


} } // namespace boost::math

#endif // BOOST_MATH_HYPERGEOMETRIC_HPP

/* hypergeometric_0F1.hpp
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
*/