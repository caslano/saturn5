//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_4_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_4_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner3_4.hpp
58+Bn+VQEdXnuiEo6KOX58krhi1hSemFwMxfIpBjlmmvQeRgy/D5jMue8Rf6xckdWCQ2fuJ6Q1D00lc931rvvvNGsATZwO46Thow5+DddBwANTiu/ozXn0kCxelXnHgluePcuMjvAEVS/XHeqjnwTODPRB3FyVcS/qfOkIvGD35EZgjeMy9O8ze7SIOrO3f9H/WXRRAc1VEzctDAtz5Cjypn90Bmn6nacRieIBFA8zi+EqRwxqDLOEXtwK8yW5Xj6FiT0fw8DbIXOIob0R3zp86gfoaaJwsV64UlrfK79AOQPSBFVjUqG1kZ5eb+BZVyNCuSBPJnaLXavh1/699QET4/IOLxmZfaxjfUEOSBAP/KfBOqiZIsfDua76jDrqDBZ2hgBwLo04nqOYmz/Nv5sYBPdhyvfZAdudEiCWLTgSbgVCtC4NxG/Q1NzCw7HlvgI/QsKkLr2A9X3wNigzT3l74N8wq7+iCFsjg7uQKzsYcWjsOC0UjiHYAb3QNilZcgfUNzD/wy4pe0vMC16EEoasIfy4+qxZTB0F5DXQU4hosObj8PSGBGbmG6IDv6AKKtn8ZRCA1kkOecwru5sfVzM/Dz8j2z4xS8MbU6/cLUGthP/T8pw63GhpRv1AvB3uleun/ShuNZw7XG3Wke
*/