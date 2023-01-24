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
/aUR8vvSoJnCk2cK8AN/FmBcROEpNAWYjb6VE4mYUK2636zewxlSBuPOm76WuGTmxIvtUBLL2XjZ/aabP5g/eFz3x5FI5H6GK/kgUbGMXuiQL+nu7jI7EnwGfBPmzBzz+1si0g0/Rij7WZaPkYRbIkhlihK/Q/DLm2oCmjLHZRwfHDeMbdMo5283BZ0q/Tu8TtmtapAORQ0pshkxyvHBGKKm7Kgvh2Vvw4CF5nuXM6l3bRxWEtxx0wW6fdBpdrAwLINX4OMVn+y/a8SAZnpuVm64GZRrMHlz0rVNdWQ4DMwZOkB96MUSBh4+t9g53SWGKL7r3GJ+Kx/bLneJ140utZ+240ZG/WN074fY/Ligb+TelH2slVEA0fp+Kn6Kc0wHWFZD3dI2kk0dIGN9CO/T0yVc9LB5aN/NlpAaG68KmgPjL9Yxv2RA2nLr32sOfq/zfagfwme8lD9Qblfi4gGSqpoZZ36bJVF8VKz5/UuJLqGzxGfptKz8cTHvpmYWeuHOsa00aH7M47STX0t4P3iSWfDJdWLn06EFeZJacSUanb5z7pLrxIG0z4Sw6R2ZTjijh6ijErggYGUWt/5Txh4uC041scou/J7B/qECnlkMw8+efTV98zM5fBULGVjnQ1bJ/bWa2FqcoJPy/VJTr4g499mYiPEFVp1aymeDbLaYs3jGINNUD6jZRBWnvNuzffYR7g6KL+3oHspTalN0
*/