//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_6_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_6_HPP

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
   return static_cast<V>((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_6.hpp
kEqS2rHvC1zmgHT7PGlPLt8xSTp517Hur3WPAOVU6IG8g7IKH9g/lI5v4tX4JgoiHqPiij/Upk+lE4v+DQQwGkHvaHtE2ihhg1BvotFhV3n0bSvcGA4InnKYmbMUOBV9a3zzuoSlkwXbIVwOCb4MmhI7pqZdhiBx9YDv5vh8+bj3hKLzjqccoFHvtxez5aoFsxkN4pTvWxS2kDUufMz8HnmmvtJpDgmIdULwIvKob0UxK0jWvn1M5RgoCFI+2v7YVNOG/bL/qMbKYYYpbdv/1uEnuGPKYWv46g8RKcRQfl3hXTFScv11lDl2/W0aFYcB/GYPXXeh9IE0Xltlb9EjkMg2k6hGTgWpP7vLeApMwC1sgzaVPgNCjPEC81EUu0gnl/EQqNzT65dQTMbfo4AYG4pLoPlJ6DVGOmQxki2GHjW7cMVdfVzGoLo3Aa0Xa945ZwEBTeibYJSUulboiNokJwvxDp+CYhWPY/+xzddlJ5loamjwn/v/q0ga7hXuvjeuL5c01O66kCCJ6VVXmolRpsNUihJi8hVImzce3cK3tdZdnItiubVk+3M9fg==
*/