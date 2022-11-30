//  Copyright (c) 2007 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SIN_PI_HPP
#define BOOST_MATH_SIN_PI_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <cmath>
#include <limits>
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
   if(abs(floor(rem/2)*2 - rem) > std::numeric_limits<T>::epsilon())
   {
      invert = !invert;
   }
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