//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_8_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_8_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_8.hpp
EhsYN3M0kok2i8VsczhdIyTRLuPRgGGXcVJomEoW5USGSfJUkogqr39F5na5UmkTeuGXuX6yE6WPE3LRBJqm3uVGWtavqJ68c3HCT3pfRNIOFsLremJneCp+7QdKGHkdKNQxhCSxsOKviisMberZIm4M4eFPezx5EJ74YrOLJVTZxMrzu8bPQf8vpEnGk0x0fFl0WRlSCp2R/kilkVp+KsqfZaDvKk8UVCpy6IuC0Mc+2X80Ns0XmwjVBH2x8gqA2fNQDTAYlmwgEqWl7RGbt7Q1PAgavCZ5DvytgP9QdrYE/33R2ddYKKTkQYnl/afqTmIYyYk5qicC3fRjEAbsPUk2Fw9B9b0mxLat72bPcauQXhvyY1TEn2Bi6dh4PcBbJ0kcMOIPHtyA4E9hePRAFSboYy4VeKLVwxjUoUSYuGF4uVJ7uWgYhdxDdxKieqYD5xMFXhi4TRE/Lka5yFltCMCJghyEWvjNYwHxg5jknCw0PVr1etsFWH0jmmNjV3GsQ37KgtQTLEjNYfvzD2YZ9NB8GPHC3GCsLCUeOzR/f07RAb+cQGZ7B4aLyEQD+5Jp+ZFz5elok7BbOUVOzItzMLwDpTreh9tueVBelo8RJ271Rr+xRqpCci4GaM+Q/5nsJ0X3Amp8FVDjOQsiJ+WbC6NJa83o4Ox/BeQzUtOxjEC6WnqfM5ITnD3eGZBfl2RXKL1RGfWGHWYNJvR6
*/