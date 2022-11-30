
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_HYPERGEOMETRIC_1F0_HPP
#define BOOST_MATH_HYPERGEOMETRIC_1F0_HPP

#include <boost/math/policies/policy.hpp>
#include <boost/math/policies/error_handling.hpp>


namespace boost { namespace math { namespace detail {

template <class T, class Policy>
inline T hypergeometric_1F0_imp(const T& a, const T& z, const Policy& pol)
{
   static const char* function = "boost::math::hypergeometric_1F0<%1%,%1%>(%1%, %1%)";
   BOOST_MATH_STD_USING // pow

   if (z == 1)
      return policies::raise_pole_error<T>(
         function,
         "Evaluation of 1F0 with z = %1%.",
         z,
         pol);
   if (1 - z < 0)
   {
      if (floor(a) != a)
         return policies::raise_domain_error<T>(function,
            "Result is complex when a is non-integral and z > 1, but got z = %1%", z, pol);
   }
   // more naive and convergent method than series
   return pow(T(1 - z), T(-a));
}

} // namespace detail

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type hypergeometric_1F0(T1 a, T2 z, const Policy&)
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
      detail::hypergeometric_1F0_imp<value_type>(
         static_cast<value_type>(a),
         static_cast<value_type>(z),
         forwarding_policy()),
      "boost::math::hypergeometric_1F0<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type hypergeometric_1F0(T1 a, T2 z)
{
   return hypergeometric_1F0(a, z, policies::policy<>());
}


  } } // namespace boost::math

#endif // BOOST_MATH_HYPERGEOMETRIC_1F0_HPP

/* hypergeometric_1F0.hpp
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
*/