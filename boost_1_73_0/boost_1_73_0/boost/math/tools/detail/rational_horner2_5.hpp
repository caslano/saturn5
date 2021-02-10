//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_5_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_5_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x) / ((b[4] * x2 + b[2]) * x2 + b[0] + (b[3] * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((a[0] * z2 + a[2]) * z2 + a[4] + (a[1] * z2 + a[3]) * z) / ((b[0] * z2 + b[2]) * z2 + b[4] + (b[1] * z2 + b[3]) * z));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_5.hpp
k/ssWYbrebh+oLmi5ROskiCGy8sphD96T3SbJDC7vDjxrOcw+/QFxt6496RPUQCzCxfDvRM6d+UVZqXMNjfjvTRjny2R+svKrdoAFocGbSksZLitc/XRQovGVK/1Hl5pPVJZqJSbxQ0o6hqtlfn5wBk4A2fgDJyBM3AGzsAZOANn4Ayc/4zDvS63E869RCZxe1dXlNAr58wZFFBIYbekkUm2JkuKP9q9pPVZYVvzV4N2Er6q63/+nbqAK9HIg76HHHfKCfNdZUvSyrrKLPRS32lvU+OuH1QLZQrS4cC9AwF4hk3TRfUZN+Mpid3JBiYTKjwxpp5kqKzGGrpGrj3v7HuYpIvo+qyrHoVx6k2n0xlMGph+pj57XreY9w3QZh6lror9oQtRdFcBt1JpLJDKp1VLBWNToh0z/uZiu5vD7AoqA3ereBm8hFEQ36aL8OElXfwM5uEqZVxqjTrDnAaZXVHBE5u3Gi1mWPvMXQeEQrVvcGtGzN0GaJiv8rdo2lqeU8vk/ZY8wwW9cZjCHb3r+cjdTkbMHQoWI5YsngPohh25e0r/yb1jKe69N8+942HmD1BLAwQKAAAACAAtZ0pSFTpzqkQCAACzBQAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEx
*/