//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SQRT1PM1
#define BOOST_MATH_SQRT1PM1

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/special_functions/expm1.hpp>

//
// This algorithm computes sqrt(1+x)-1 for small x:
//

namespace boost{ namespace math{

template <class T, class Policy>
inline typename tools::promote_args<T>::type sqrt1pm1(const T& val, const Policy& pol)
{
   typedef typename tools::promote_args<T>::type result_type;
   BOOST_MATH_STD_USING

   if(fabs(result_type(val)) > 0.75)
      return sqrt(1 + result_type(val)) - 1;
   return boost::math::expm1(boost::math::log1p(val, pol) / 2, pol);
}

template <class T>
inline typename tools::promote_args<T>::type sqrt1pm1(const T& val)
{
   return sqrt1pm1(val, policies::policy<>());
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_SQRT1PM1






/* sqrt1pm1.hpp
P0zvg18R/+UvgES1D3hJZkAD2P1HEVTH189NnajnU/74qgbsA02ic3Oqy4f3C+8PEX81vpJ0XjRZ1fHOZQ0Yn+Clhf/kr5+Z/HEL8ob8zMHzmHOZBqfsGdQQLb/KAiGTTwQvSX/9Zc8n1l86VkzyjtGUeQeXUZ1FHSfPmzhris6MVCQoo33HyM9NDLoVxTuZPxlISb5J/UH/qymU+iN+Owzzr+pckHoPIEO0dxZ7QkMA3gCeTkRKGhhRUBP4hRJ24v0lKIOC+Sd9dMt2vM5sjjvTmbPCC6szsravFcZ1HOuCHR3jkYF9CzdT6do450nznPtP9nASfLZwi2i0uF6jxVQow64tFn3+7mv+cMGPt8xi81wbz2Cx6tV7XBaeNzdC4cQfOJ+fzIaH5XFhZ4PL1XpifT4XDuaKi0vusbzc7jPfsdWAUQ5PtVFUMlD5c93jvbK6i7qKzf1NqHkx1EdifzVbXnwd1vbB4jKKH4pYb2JhUYrbzFIZ19ODbNA/LWVNlE+i45vDvH969B5hyel70VBvmTCJsn47SJdsfdJGYuVOtas5N9RiaPoh0z3hwaz0dTkVXE60L+o67C8OXLceT9jdaHo1e6q+cu3xoJvnXPJQo6V3Gecmi++j/LhbpoxXP2ayfC0PT73aZU4q
*/