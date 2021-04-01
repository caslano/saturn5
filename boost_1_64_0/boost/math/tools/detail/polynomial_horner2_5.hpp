//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_5_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_5_HPP

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
   return static_cast<V>((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_5.hpp
5Azh31/Rtxy20hdD3hkqojPY2kGfw5t+afNAvNcLZRVCgIBwM/r1NbiSwgRakP3tyM6aQqrSX7fW7upg++qnJbYvpbzaWFzmepFlyqrggH1SSeG3axh/3VfGXOQ62NmMWTynS0WZSJiFwEOfTUTXOehcvahB1cUlxQIu+mWLUQrcfUuhYYOt0d1ZQ2jFROdBDibqioXJ+BWMIfu7tPTfLtI9cWHSXaRgsbRftKqu58kSmRDS+4oYc5exxFhZncCZBawpnKPCZd0mxdYIwWDwoM18CHkAIbzFDbVDtm3Rt175kLQGnkTKYjxo33LajDc2KTSj6JT4yt9Vzv1pOKbWt7mioqecMLonl+R7A9uFro1ugFIipPhp/bhB0+FuokdW7vMvnPdEZJTaqFQ4g4oG7xfrP8ddySFIVkLDlzCMAFNXxwmar3D+ba18Jskxv1ZkczfeOmLyIuz+fEeWZxjzGVX8oSIIUwGkvweCg+MCFZdgtEDhtdJfVVv5Zq80T3SVhi4+ey6yChM9IowRzK0cOSi4BiJt35UT+Hmoe2FGHuLk+k9oR+qOMRfcHg==
*/