//  Copyright (c) 2007 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_COS_PI_HPP
#define BOOST_MATH_COS_PI_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <cmath>
#include <limits>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/special_functions/trunc.hpp>
#include <boost/math/tools/promotion.hpp>
#include <boost/math/constants/constants.hpp>

namespace boost{ namespace math{ namespace detail{

template <class T, class Policy>
T cos_pi_imp(T x, const Policy&)
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
   if(abs(floor(rem/2)*2 - rem) > std::numeric_limits<T>::epsilon())
   {
      invert = !invert;
   }
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
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
*/