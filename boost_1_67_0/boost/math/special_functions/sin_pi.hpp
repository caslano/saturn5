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
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
*/