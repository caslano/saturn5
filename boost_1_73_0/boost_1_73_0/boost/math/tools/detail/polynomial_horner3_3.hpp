//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_3_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_3_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_3.hpp
3DD233ctp0mg2+jDXjYwtvVxzz3nnis7dWidFBbHLK1UoenxiOtGm9yO2STLpv4GF+cZM5hXBqX7ujQ1K3Rd66bWUrhKKxaGjakchnrpWMp3CCnvQNkbuEOzQhPaKkeWGlzUa1rOhROgtCxRPp701mh7XVYeH8ZwFMWQlZUFugQ0WJlcg8MnB3O0VswQbGNlrS0G7GrDJIEWksfR+ziKRqND9+Q+SK1rS+xOCD9gZ1o5VC68QjVzZQLvhn5OkTIfvwEMmE9tPWvwfFsehTbQlqxSM+Jkq/miRtgl78pCi6S8JbKROPytxmEUwScfhDmUaBCKSu0L+ygcJpAt8S1EI7jWKwqJI4iPk+NRQsEXn7OAdbVNPLOwo8wL8Ygv1R7He9KkVjnc315BrtESRQelWCHp2vraqRi2Rm4sIyfP6qqF7JyUfkAburRjVjq3oO3PQ0iVmGOnmFLs1UqrfQqD/fYagK8WBfMuGlKp53Oh8g4/4bw/ubnLLqdJvwWe3txmvEHeCOW4XhrvP7x6ZxRFQwgbGPS/77P48UUNSMk2M71uxFIRHtBUxdp3G4jCUY+4Er0BVEQL3xAV9GypXY+lK7+XABZGOy11PWZ0oOAl4+e2CNhEW5fAC+oBu6fChqczokGtSiR5/+H89u7y
*/