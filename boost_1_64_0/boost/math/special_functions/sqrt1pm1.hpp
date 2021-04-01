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
IUL01Y/YlDWN8ZUyW3VUx7FSc7qC2ZS1sbtAUgCIiBeKic74HwQk7lWWd9t1bTc2MiW5+OF+Mf0MpTGzTtPqJ19nl9sXlF+mvCzxkAxCGouUcg+fXjEJsPChu+FvHe5MMKMeT19t0mWMmedgVYVLEhHZ6ASJvEW2j53mCcn9VxIcK5/aYkQDDqyI3Zk1iBOZ4p9TJ/KK6HJKzUu8hu9qTNCi4XiXO6acprBKfpy/Yi9C06QIWprUVbiARiWdPoKgR53EN+36lWf0FpQqdPpDvYQ0Ba90drO/HZOkiLRZX4IwGTWd6003o0Iey6eRKssKvEo0SXAAcJSKePUpFtUsPtCCkQ924LksY1xcb0qNrhdI9JPYbV038jNgfa39m2AwW7IsBoQWCKLvIOGOQYOi9s02I605vi4q37ETwvasCJeKL3kMkQj8QEjq27ka4GWwm5Nw+S/GN6ksYtoe/OesSRMakr9Z6I4BrqZfMmyV0B0WyRGzGrihgKMAW6K0iLdNmRjEm572NuKLV9v+1sTM6/YbBFys0I5E5hlwepKOqeXrTTKkajPDjfplrA==
*/