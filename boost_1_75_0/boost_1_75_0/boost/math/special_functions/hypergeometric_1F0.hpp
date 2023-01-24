
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
VCCAt7hRx47NgtOe8YaZObmtZGZ9UyScM11r7RlNMW95RmEmI73CrZExudMlC+MpqXCUGNofNlAIpXLvCBlRxXlaFq51lhjFRvNTtv7dcfuTRg3Q2BoeUAP/kXwXHrJOuRthXKjzg7QiOdlshD6lm1kRVDI64ni0EnwiacsX+eyJlFpJUvd6FHhD/gshiKBdNEgvzT/iPNJ4MBHHEhYJ8Hh+9jJ5ri6bu3YK0CzXjMd+kIXgTma8HXJsUdLae9CVWwT//nx/n9me4ml2M7Td2ElwWM0lD5DSPzZ95PdHvlbso9wxeGboDlpcORa+K8Fa7ghqyRvlKPAIJF2tMRoW5woy/FOICtZqhhaKTbps6OBVjZw/PIW0FfVGwb3dHDvJtyiso1fnwnjziJcxKa/FuOtOhwMAfba/1MoNHyibKf9C2BCD+q5glLZugOhU4Gl5O50xADDnzrpMYH2qV4nKP+Yp3ZLPoR3w+n6N7cFRmvMnCNc4biuum/KW8w9pQuz6i+LDy977WUWeg/yIAIJO8oeCbrHNxSWC7fc4HtjS2QOYMIsfD5tb3w/y8U+yY4X2PavPV99uUL5wNa9emvB/Egfkz9ejPACBCaDZ229seP60zW6go76XUavdCfqxS8IF1fXc69TEjURKtoF513Afe0QU/ZgE56J3+T7rE6dO9IEfYtiYSAWAcBO+s3ZjWr4bmrdw3bm8vK/+42rR
*/