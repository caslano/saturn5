//  Copyright (c) 2007 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SIN_PI_HPP
#define BOOST_MATH_SIN_PI_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/config/no_tr1/cmath.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/trunc.hpp>
#include <boost/math/tools/promotion.hpp>
#include <boost/math/constants/constants.hpp>

namespace boost{ namespace math{ namespace detail{

template <class T, class Policy>
inline T sin_pi_imp(T x, const Policy& pol)
{
   BOOST_MATH_STD_USING // ADL of std names
   if(x < 0)
      return -sin_pi_imp(T(-x), pol);
   // sin of pi*x:
   bool invert;
   if(x < 0.5)
      return sin(constants::pi<T>() * x);
   if(x < 1)
   {
      invert = true;
      x = -x;
   }
   else
      invert = false;

   T rem = floor(x);
   if(iconvert(rem, pol) & 1)
      invert = !invert;
   rem = x - rem;
   if(rem > 0.5f)
      rem = 1 - rem;
   if(rem == 0.5f)
      return static_cast<T>(invert ? -1 : 1);
   
   rem = sin(constants::pi<T>() * rem);
   return invert ? T(-rem) : rem;
}

} // namespace detail

template <class T, class Policy>
inline typename tools::promote_args<T>::type sin_pi(T x, const Policy&)
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
   return policies::checked_narrowing_cast<result_type, forwarding_policy>(boost::math::detail::sin_pi_imp<value_type>(x, forwarding_policy()), "sin_pi");
}

template <class T>
inline typename tools::promote_args<T>::type sin_pi(T x)
{
   return boost::math::sin_pi(x, policies::policy<>());
}

} // namespace math
} // namespace boost
#endif


/* sin_pi.hpp
sbOoWaJAUW6LVU8dwd4cdAvaZijsodSu9hkxPRm1Pjk4rZNQ19UZj7mBwcW2Lzgo5ojl+HoacDRm6X/EphpBCyXne9f5399OyFoN1yNmiu/3G3z5ZUIn46yXspWymwIhPWMHmpSY1BPyar76Kr9XGML5OL4q5zZWzI1VNCZr2Nk+MpOtT3VUatY+uwv5JTjnuN4He5Ke2soXc7XynearZgPtluuMyBzNZAoALEeBy5TmETSByncfiSz8+B1nE6n/kNlksNKD3VRS3p4O/qQj3bQhjTkZeCfP15ttGTA0KE1oB8dlSbMwtK6vxgvhvqFI6yFpLOHl7vqVvH0jFw+DIIxgg0i2nAb6WmZlvQUcVk9RGyrVM/nLDdSNHVv4pDZyUhG1y+jTkrF17+d2ylThndqz7kMlpvz65fQToVCfN5UT1ZoYMfgy4nRWehtTdDa1g+1F6gZWERFE3kX15oThvURZ0b0h9aQFL81KXDB50n/o9nd1DmVylXwaMX5Io7G+yw9CwAOCtRIlm1SaTwUx7wx5IVHBQ2Hb+Gafss4hL+RAiP5MF3W4M+zzIRuSyCHHYwth/wejJbTJXmQkEUQ15FKKoMWIGlAXOi4KNK4EgkTGeQUburFI5dasfD8y95NSNFTBDFKiA5QLi6dT
*/