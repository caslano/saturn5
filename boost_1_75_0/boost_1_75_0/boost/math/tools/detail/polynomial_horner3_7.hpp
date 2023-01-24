//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_7_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_7_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[4] * x2 + a[2]);
   t[1] = static_cast<V>(a[3] * x2 + a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[5] * x2 + a[3];
   t[1] = a[4] * x2 + a[2];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[6] * x2 + a[4]);
   t[1] = static_cast<V>(a[5] * x2 + a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_7.hpp
SPulH0Ei7r+ICw+An7dpMFgh9rCWd2jLz3TngEFadedqZTQAVKgyfNgbANY8iN4yT6cbJHvNInzyO/OT+fjkGfOTy/SDV6KDl9biTknHJTe7U/AJ4v8ZPOkPTsXTdrfy5Ay25l0gFmPNDD6FV87QzglK8iAEbsNO64dFNboUNJL8ByiqH7Gd92FJzr4gmAkgkMCjI8fCXtaUqQ3J4hc0/odiApPkF000TgLZkoEwKjNif1P5TQjXyUXcIxwqVTyT6Jw7OwpMYS6GvUDvaGXO9yyaJDIo70XJkFWXDK1ss1MllD0CnZ6J3nmT7ufDfT4L7mDKRo83Ih/PpFNq5Q08DzXidyH+Mtz2r7BZeo+NzD5mtlNdGpR2BeTPQuhmTsms4WhdiFGRZf9DMf8RuQ41+SRIf2ktCc9UTMoArObVmudXMLZ8bUAWMebXCibm1+mcAIOJN8C4x32yfwmmt2Lr20dYDXhc9755b4+GxRJ16Sm5JgB2X3xSGEfjp9OIYw0h6dgRiPlRnicUQxGhW/MByUl3cfkQWoVw5mZl6v0YvpSUcqtrG8OX9tC/evSarWjZrKsmbensaSVXrsXVXDTIorl0+9fiRVkUSAgVJYqFFDo2IPstIiRSqA3GfYQi/NHyKxf/ESViJ0gi9rc0vT2amUJs7BmCUagYDb5a/OtJUBLzbyATs5j/uZh/kwZK8dB6hKVsHZau3EvyAVdt
*/