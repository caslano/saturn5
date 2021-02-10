//  Copyright (c) 2007 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_COS_PI_HPP
#define BOOST_MATH_COS_PI_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/special_functions/trunc.hpp>
#include <boost/math/tools/promotion.hpp>
#include <boost/math/constants/constants.hpp>

namespace boost{ namespace math{ namespace detail{

template <class T, class Policy>
T cos_pi_imp(T x, const Policy& pol)
{
   BOOST_MATH_STD_USING // ADL of std names
   // cos of pi*x:
   bool invert = false;
   if(fabs(x) < 0.25)
      return cos(constants::pi<T>() * x);

   if(x < 0)
   {
      x = -x;
   }
   T rem = floor(x);
   if(iconvert(rem, pol) & 1)
      invert = !invert;
   rem = x - rem;
   if(rem > 0.5f)
   {
      rem = 1 - rem;
      invert = !invert;
   }
   if(rem == 0.5f)
      return 0;
   
   if(rem > 0.25f)
   {
      rem = 0.5f - rem;
      rem = sin(constants::pi<T>() * rem);
   }
   else
      rem = cos(constants::pi<T>() * rem);
   return invert ? T(-rem) : rem;
}

} // namespace detail

template <class T, class Policy>
inline typename tools::promote_args<T>::type cos_pi(T x, const Policy&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<>,
      // We want to ignore overflows since the result is in [-1,1] and the 
      // check slows the code down considerably.
      policies::overflow_error<policies::ignore_error> >::type forwarding_policy;
   return policies::checked_narrowing_cast<result_type, forwarding_policy>(boost::math::detail::cos_pi_imp<value_type>(x, forwarding_policy()), "cos_pi");
}

template <class T>
inline typename tools::promote_args<T>::type cos_pi(T x)
{
   return boost::math::cos_pi(x, policies::policy<>());
}

} // namespace math
} // namespace boost
#endif


/* cos_pi.hpp
Jfzs68AF3UoSteGNX3nYRC42TqiINFG+liF5vFtYZlNZ6sLZKie2ObMs1dY74n0yk1n+VFtI8FPVhbGLlQRv6p2QenCXxTrf5tWy4viGvTnWjvus5X5l7Js4v/VAo8ZpC+XXW8T2N8q8Tp+3mbllw0Ldsl1VoeWGnroOVfvtH18KEFxrxfZ3a6lZgGaM2hNXZ1nVio/3Gj/etCwocCv3OJVSJRke7zubmzd898Gt8jdXq/32DtFl1Pr8JP/5Zi9Wn8/cyy4KRKk/Ec1pCNVJDvhoxvv6/8PXGQp1S2fU8F2Q+5pR72+3c8cD/lcmyzYCAFBLAwQKAAAAAAAtZ0pSAAAAAAAAAAAAAAAALwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2NlcnRzL1NlcnZlci1sb2NhbGhvc3Qtc3YuZGhwVVQFAAG2SCRgUEsDBAoAAAAIAC1nSlKK96cfCwUAAI8GAAAvAAkAY3VybC1tYXN0ZXIvdGVzdHMvY2VydHMvU2VydmVyLWxvY2FsaG9zdC1zdi5rZXlVVAUAAbZIJGBtlbcOpGAShHOeYnO0wjMQXPDjvRk8Gd4ObhgYePqb2/g6ban1dUlV9ffvbzhRVq0/Tw/8cZ5qCHzxjy4m/1v8hUxVFRdX5QDQeeCKYKKH
*/