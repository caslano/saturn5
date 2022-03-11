
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