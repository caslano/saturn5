//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_17_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_17_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]) / (((b[5] * x2 + b[3]) * x2 + b[1]) * x + (b[4] * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z + (a[1] * z2 + a[3]) * z2 + a[5]) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z + (b[1] * z2 + b[3]) * z2 + b[5]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x) / (((b[6] * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + ((b[5] * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6] + ((a[1] * z2 + a[3]) * z2 + a[5]) * z) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6] + ((b[1] * z2 + b[3]) * z2 + b[5]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / ((((b[7] * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + ((b[6] * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z + ((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) / ((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z + ((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / ((((b[8] * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + (((b[7] * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8] + (((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z) / ((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8] + (((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / (((((b[9] * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + (((b[8] * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z + (((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) / (((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z + (((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / (((((b[10] * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + ((((b[9] * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10] + ((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z) / (((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10] + ((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / ((((((b[11] * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + ((((b[10] * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z + ((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) / ((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z + ((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / ((((((b[12] * x2 + b[10]) * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + (((((b[11] * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z2 + a[12] + (((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) * z) / ((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z2 + b[12] + (((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / (((((((b[13] * x2 + b[11]) * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + (((((b[12] * x2 + b[10]) * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z2 + a[12]) * z + (((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) * z2 + a[13]) / (((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z2 + b[12]) * z + (((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]) * z2 + b[13]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / (((((((b[14] * x2 + b[12]) * x2 + b[10]) * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + ((((((b[13] * x2 + b[11]) * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z2 + a[12]) * z2 + a[14] + ((((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) * z2 + a[13]) * z) / (((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z2 + b[12]) * z2 + b[14] + ((((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]) * z2 + b[13]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / ((((((((b[15] * x2 + b[13]) * x2 + b[11]) * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + ((((((b[14] * x2 + b[12]) * x2 + b[10]) * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z2 + a[12]) * z2 + a[14]) * z + ((((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) * z2 + a[13]) * z2 + a[15]) / ((((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z2 + b[12]) * z2 + b[14]) * z + ((((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]) * z2 + b[13]) * z2 + b[15]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((((((a[16] * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / ((((((((b[16] * x2 + b[14]) * x2 + b[12]) * x2 + b[10]) * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + (((((((b[15] * x2 + b[13]) * x2 + b[11]) * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z2 + a[12]) * z2 + a[14]) * z2 + a[16] + (((((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) * z2 + a[13]) * z2 + a[15]) * z) / ((((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z2 + b[12]) * z2 + b[14]) * z2 + b[16] + (((((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]) * z2 + b[13]) * z2 + b[15]) * z));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_17.hpp
OEHCmd40VYyQU9eClyNDKgvRtr3jJs2JExwhBbGRmIoiiUSHx7E6Yc+eKXHkBODp+Dgt9jiJlBwLbqalZEBmGiwXtipvJWX6oGotu9C0GKpwFGgyy71xjwHcafOjNot4GhpOAmeXibPaLI7Gz89EdCNm3Ub0yLMotL75K+TeKeQfkmEtedB7IgyVgeviw6fspPSvWA0As+OFdbVxK9VXarvovpehwV80ISOezq+qMQIswgqUiLzauqbJ51hGOFed5VjuHaepOe2lUp2F9dAMJZwVHLH5/bcjbEEWHTDjh6JSYmaeU6R7NG+pZnnjJbxgDcFkuxGwNOK2iHLcny0xFYrLR/qcJDOPNY5pXLRUZNkk4iSevGyCzNARiVJMPVZIH6x09UZc7W8+m322asGvHSc+4bG76xeH5yMPKUy9CefH81PMGDhIQCpmobti0YvRCl9ROLgBfbj1lpTuc9FlAnesLlls9/gHRh+eeclfOUajsBcuG9Om73BAckY8kGXJOAxaie6tnjRtIzYfJSytTMaEMqHfh8DILfLKWf2sqj6zHWvLcchcRxCwh8hibE/6OtIw/hcFou++6vi9lE2BRDP793vlHSp8ik16eSgkrGP8mrnFmhQMQ/h0dNtYB39yHSl0ZbJvp+rdfwpg0DUwublve6ZwV69gWApeK4dEfaJL1PYh6+8MMX/eHVyRSIo32tqgtu/H3NcQ5GEvaSnvIOTeUVDWWiyhSRgbdJtr9CRDhKHWEk05/DCDzqehdlj//kKPD1wRSN5piJl/knIZSdkl1001NAUNUIpxG3G8MzkCZxyUKZDqwqiJ3EYPuWGk5Cgh71IUAImI2ryyhEnUMlwPF/VFZi7fc6i6nJZSr5laOx1IJIQGGlbuVbhxmApOhrKXrnzetJ2lu4Qh3gxNc/mVReGtQOQ2ogu8W6WGSSWVjN/XJq/GfFd1tx5Op+rVXHhzPQgT8gDACbBxMTQ96GJyBgH+oqKKbo6kDv8V++n/WbljiwGS/+8b+ZFaMYSsQ4VS2nMWleYx12EyMod5w4S1ZMX154pIpsdAIZBw68jRfQcEWVmmCimC3FeYkSXDUxO4lZW4qe3Chvb4vjTE9tnoBiVmsuP5sj+hsTW+GdFudatEg53RCc7A8cJvohxgWXgtKpxZqAposWqekG3o7UPXhV2CbHs3Asbl7cwXY8U6E21nk46JNrbpbtwJAS2f7oICYfoALurtsXlFq24ev3uJypfN3eojwDfOSNzPGLfcQmsdEmdoxGg8YO/sGcBKAysXCPNrdtPLBaGjcRNFM3AyKa7qMQsmr1FpZfYKHNI901lu0RX5lcxkxQAWucp9ygCmejeoBuQEFQKFwEb2DDL0oEAhwgvetzHC8tEVPMQRM+K428rtlD0tB7vrMZF5yAQce7LPY+p2x09xY2NlcK9M4re5tnh2dwxk2LiudJ0mW2GHvP2bat8acuoQnazAx8Hbjh15noLULdc4BAT3AupFoc851KE2hDZ0DQC4L98u7Qx9eAj5vqDByz/BizVVhuohIbt0wKHxltJGjDMF+Po9VMz4GpfIwTh4fuluscPGy/tdPOSumzT0pS4GhXcFpwWkoZjGJxz5GZm5WpuBm4CMgi6XCdIWZwypLt5qbX3uJk9ebJP7z6kadHAkhCm0GuFJw6vckWxZr/cicBuTjBD2LwWC4smxRjjUjmnpz7upr79KZtuaaWV2sZQq6ohr8XP1www7bfiZCZbY+MKJMLzA9qHX4Ly1ZzWEi6lQ9tv1s+GCbJKYfcn6TF4scEM1UCsoM/9pobjMboOExbuqw44TizA+o6Bq17yBq4xa0qjTyV7HOj4QO7nKDr8JN4jhR6EbA3WE2lS2gB12OhwLRcsHzRa70Vwgj3I9sihzBgMC425ioy97VAiYTJiApov51OvDMCIacGt7trKJ9zYi0E9cpnEdSCfHLAYp9vDtd+/ofU7WSs5RulBKcEnAjilBNxv99wnzcbNoPkQ3kzRD02GBc9RDZ9KCE3kitVURURTdZME75ghx0HQ58MeKpk8i7a0oYMt0ACKQ0eq7AYlKfFkZ7gKngqGqwavDh8Yhc4kRO23LfRCTtejuK73dpFF+uplVWe5prEYCeLtd0jAJ3Nu+UMjiqpiKZMNi9FO33eJP74lcwQvNvp4/uZXenEEcZcRXMZWYererlXnrtJ4U5j7U7gSui/HjT0cF6osaKUoCjvlWfr719ZIop5OyAY4IAh/qH4Gw40lk7mi7U+7KECT0afPSy+GUaqZ/63HhhPSWe2Hacu7ypCf+rrTX/LxzcuBCHdEqccTLQTpjGc5dXsR10GDXk1iMHb+Uhc24q08Pou0WY1YS3WfEaBxc2UyBBdyAH2Hxb7zMRKXitjulmaFR2/BGa9MQjnwYM14e3fxCrnIA8OcWWuER9KBeANRImGciaxnTkxI5R8k7Xbjncxv5gZVnovWwWmAuRE+rbEFzII9mgKcOBS8FAIhMNGzapJWRGq3BKzApgrMGnzuqcmvevUcuWhmJy5l1icjISJIvax8LDz/hda6by7Mil7odjeKbRbjxAiIroDwvmwozGAAlNcX2ZvkUEIFE9X18SHxqoFwh2NMCi4ioBHk/xu8yEVsJ/uhpnTP9AmoRPfotajC+3MKLN6vGBoVQt//ulMCyioJwmdtatymrq7QtBdPj4FsfY6o7mfdzq3b3ScMiVXp13QmZVFlkmIRSlMSCLQOR4J3vfGtyBaN+JdB1UhZ3pc4lL6Z2PSQpFi2syFPMRObe6upzqmmGjoiU5l20e4/0yoqsaFvcmvTDpKcN3zzp3DGO8pnyPeqEz7K6JERbUXBjFNBhqEOB3aqAqXNcm72IP3GSEuU41QhrjSVbMxOztZ8T6S59g0STXlbb1tnTMPB2tthH1uSpyx0sgIe/VV5P5+prIcvCIBV1yXMu/jvuSESkrMnoxW4KYm81d4sL85JDpjhtgGVIWBy5VivWTnEZgiWOK9FYEMjnqRNgCKgnrKPBZNUvEVo1qbqiOx6MIa3FhU7EfL3D6ckycx0jXqk7F65v+oJRpRtOi/sy2BSwJKcDd9parLR6Udc5iWKepZqSZrLxMi9UJoeMVAt2priEUryin3QA7w2iQfcYhASyfBWR6tgRnetRz7FkYIM3TRqm7UnT5kJxd1F6Ec04FehTXNFw9DIKL/ukCzNoduVBEKv00xqJwn2la3XqBA1DjU2Mit4Dh81FRtFIJ8ldHRJXSCKo7z68actl10C8P/D1THj56CJUo31Z+3JRTqJm6Y6us/kWKtZmCSKVEJZmZT48oyWcKrmQoeeMRsLsbJzfst+QigOSGLpPeks99WGxobBfjRU8+gsBfvNDYyNNTnPDbiTGsOAyBV/lWLvtzNVw12mN/NhmGcbeMyGeV5TdTdvAmzbn7BcYzOHqYzHEHOCxFJYbaq6IX+k95ciYBe63W6y7io23vL6zrk8waKTO47uHUReNyUAZQT0TBytLs5pvbUHTgrCewIC3wIOPoaOArG+CcCKpNzuvewxwwnNOa+DiQzh4EAmROKJipCkFvTCnXsWb6VS3b30kgdWzGanv4huk++A7u1on8rMzCeOMwJvSHFzMvYPNMdwf9jjSVfZGqnN7plXJc838uIakqVvR0ZfJCHoFzYcZsZp0FeMQJvyoFKDhFPWQ6ixMJxMUZBC4K0PZGbkKUrmwz09EVSbOcW0aV7sacY/RRFPN8DCo1R2RLIkb1ucM2KVtYQ0aw2kUhZs1xT0V9khNegFr2duksh6TsKsJP75at8qIIu1oNTHqejdu6zIuqhguLnqv/JttF3NAfBrrDmcIcjpBCBbtronUMMjv1SNW36VQ3XhXxgd4m+m+JlojTYzfyFTwm/uqo/sSc0n/zXltAIzgrnnt6FiQ2xwsDOm+RGw3MmaVA4c5Pi3fEV0/HfYDc6DIHbEvTbPtdzrVlxKL9wkm7SlWVxq9mqYZwq/WMA1hJA5Hse20NCIPszEtDADGj8QuqWJE3x6BxPxjymh5vXs5HuhWujLQqYY4ofMLjI3Mha6HyUeLrQG6YLyQ2gGwbHbtSwaz/YJUyKQqiGx+7NcsOJzR8ZvwcHhUPEJrIqr9XW9XRrwQDn1PTtENuB3LkJTMHwP6ILdvDDSG4CEu46mx1bFm5devUnn8o6WMDHScwBgNt8UcStg49arOaoGisL0M1f5owCqwQGTNjyxWLqZVJTuAJ1VqlsHiYDWl9PQWYJ7l0+OrzagXkjMaLf37csblGi56Qd/vhmpBFj3r6t2K3Z8rttpz6XrG8ZxYxAJxMUcGQ4SA3wLgYM3Qi1Hmnw+GeMikJ6nozi6djKilrOHkN+FeOPyxRVcIjlocQnVCNalHlBWjYdbf6CTC323Qjtj6Y065ps52W59crNKihpCL15rHYPpo3AKFpyV61xjoggMe+5ad27OdOb7VqPaLzu8b9xmIyytwrVSg4Mkbi+U+kKFNS+/QabMPr6xgV6UzvAntRBBWCghVYkDc0FLkFFFsckGaR0CWW2vNyhU30Z1Bhblxti5T+/jPAmEFdk3nGvRdvV3HYiGppAxnlzTwf0AAuoXmDKAysIlFiKaBKXAeFFN5LGfcIOWSPmq3GaLRKuUUdJzrWMeOAIaby3tqqyw8OeOgb9IiQOOgZnuUeYTiVc32h7hz/ANYJ80c8g0wL1BbhoZJzGG15mFKoxtmGyHYJa/PdD1A3irpqA4L04JlFevxqpgGSujdr6ijACDDO2VljjevGd4RXSxes9BKJiuvwCal/PX4HBDb1qTctvEUdD11+3K1kefpJpwW18wAoyxsPbdsfiFcMXV0i3f+L0MIHoRv+2osIs5fB/pIB+H5xnCCwMa7BA70alUhhqQz6RFIBV4+me+JqKnVpDApioAMOa5hZZV1qqdo10W5Tb/3zkD3ZSFRyjm5Z09bZEjLDP4Qpss/8IB5KCq6s21f9CNcsY8AFSOZOZ43ka1UDTvT7PyhCJmj7rEVNSi7kXzFMEdygyaeSbcLgT1JDP7vd4ntDJfTMi38uF2uxmX+Bqgzq96fkjokaTJe1KzCx/OjsOVGkeOtWDlo9s1q737LGeiNxb/VnV13puOjEIwRbDPoDbjTbxfVBDyiPNjQFzA0FTapAkaiqqzRrt7KPMjOEMZJQzutzETh9XevD8BvJqUm5EeYMA8LzoZ0WqSSZ1OgBLqZXQsUpZzMaz0LMpke6Bpqhp7mTQcnEWMzKr5eSK13oNEw2yN5TmM8RKjeWPHgMClj0PJfj3rju6O+8dVLegdKbrL6HpnW5rqCGCNqSkZlaGKxoEZ8dPvMlBSKApQ3fMwzR+F13VtRgtzL57u12dVlekl15mSh+7qkRkAMz4dch0CBpbjuQWp2L1kXMyrXt4LJ3loGd3pi6IYKXOb7NO4/waFGTv4YvMkBNJ+UGgYeudzH7LSvabVtyg2AocLnh9SjksxBBGk0uTqjtXhaxfA4ntpjJZJl/ce2T1o7Rcyr2wwqNIluuoFkzOUgeSkLEGK7PrtFki6woZw/OaOWPB87OaSCohWc7tbsK1Vuo+N+kJpShOHryz2naZArgIJmRZQ/u6GyYI2/E+olcDRX+q9xoxO8nBjIOqndgagNVeDUZY6BqqAhk+qLA9zjY+id8hVbsNOlA6KgwSHaK2atxKI4ETOi0gbdEU7jj/tgWN/6G3Sh1A9qgR9/seDGg1TcBfJ3kBnK0K5Y+CrZx2feZkXL3jqMQus3DZqtqqk9qdmulWBGKAx5Vny+1q3wxhTUg+RVevAQHmOjoJoCp7SkGb5wj0SwY2RWaztr7DBropPyC8pGeqp29XwS0qhJ1qVrrMk2pvvwt4u52ja0W+V2C5PN7GOxYPau5PRm31vl74y0uWdgF8hdcOGGyVZ+hhMpWBduIXspCXfaA7HPPmg3kbJsKs41DlJwssVcZYbvsgivHN6S0/bvBVoPwMF0EQhDEucqlbsd1j8OVSsvn3haM7swgjvswI9vj8F2VeMtJ4XPKyT9M1Nyl3T7/5GfvT0dWOqybs0htdf1LUeGgolkXsDzQARGaXwtzGtmz17g3TI/NGCwpScna10DcDHqqe1wELPlRrjzVLsHNqBW8po0jkamhNy3181WjYK9d6HtPGwlBNuNlg5WWAm+uC8JOxW6vJPmTArH8IuGM1otPIgomSLaEWb1Bywi4bJLBA+IIuTphns8Q3m1Mm4ABQF3cdrdRhs/aQVfnWU+09sza8DIz4lBI5m6ZchhmfqqaDvkAjGFKUmSOunid21RT6J3ZjTUOYuJq5wTydodDs9Hg22T/kvAaCSipGknvHV8GMICFwQZxuhw1I4HZB2gh5ijlQVultS6mTaoagh0t7Q4lR05Zp5gTo6NzXuT+JoNblqCpHE5MZg9vX4Pd3OWm7p1uRaqaJakvd0ejtcMGm3wsPTVnXuIkDbG4Mw9Xhk7h9ulMzbOzozZ7/TuARHmzeCZMPPWZSLaY1HO8KckpFhtNF8SnTWAuiwNj1hBJroduPyOLtA3gTvzdl/QSA9IdO2Aa7DnRx5lMh88lybV+DVTxtROLYeF2xH/zCwfhdghW67m20VW2o+ItAd4tTO4Os3FvUu5tGxWSwTaomkt7SjmPkWbVB37XH1KoO7B5byEf/9xsx9+qMKdKWlqitCnkklktyfbD7yRwWznehuT9T6yKSVojrnLEi7cq1e2/toNhcZE22gA+7gA4GxuGZhz30WksI4joeDgBKE37+CPJEew3AM48lU+NM71hHsEkRAAEahnaVoUq5wtI+QoC13myIbKM5sxib716EdoescZsCS0p0OdDA/0Wa2I88Ay61Gw5baaI73XBP9BZq3S7KK2SZR3HtHDoM8BUIyXfH6TWVJXrOCsNlD0nYejjYocQUmJrQ/ti1iSCfwOb6sOMqR0hKY9IAvfgL08znF3HI/LsC4eqgt9gjdmssZzaKa0khNo5wF6zPAxinMI9F0wZOeGynVxWipUidfzO+ttMKvgq5SgR51RMNh0EPHEvjtSP63h3br2HFnn9inSEKoYTpujo7gp6Hg0QsH5q/DPmrRb51mULKuJDAbwLvCmxSv5O5FQosiZeIesvr5VQKKUNWY7f3z0xqm7YbE9bEmDrUiHGL4EZabMVR/sdLjQcf6sRLWBSExe8WvjrGuMJQXaCRdHz8X2TEQr8arziPQsz8spC96e+w49VPSiAxyZc1KLTtTTKbKPTjTT232/LTBGNjbRMdIkzZVhBRiEsADkTodbcZQ800COM7RfgWpNAzI9Noc8wfi1gyWIfZDcF2THtqxFPgACgDZWLtmUrBy3yp+/w1IUIaLUCh0UCgGCRdtRjOMqHEbLPfSsr8f3/FMCMlqGB4ZvZ6OReRpF6DsnNtmQlwgxR/iYHd23ks72Uh9nlIqOroxMBNmuBQW1q7x/7hodLCOfc483nFngTOsKcsE2ZlvPwIqrM2wN2t6UyoZLrylteEu2VD2rpq7IbyYLHK6moKbTj1TlxJkBnDMOY1V3M7DWdXhF50JpjUDc+kDiBk3XXPoLbC4vnpgj37t/3PCIe/w6El+mbG+LZsXyQxJMlt2VXZ7MQ+7xRfwk1ZcCMqgrTYdXLUUFMjRsz6jeI4++RuPUFKiX682dlvEQ5fDbOMvFGXusP1liot69h8P6+d70aL4Bq0ywg8rbPK8dNCJvfSDPsWdPrvPuIwa20UzxATzugTUankL0eit/2bHA5DYxhZz8+RzE0Oah0w5YDW9flsFH2ZGYd8CTr9qKIQpeJdpuh+dKXodWml9Xs8n1sAKvAI9DyZhQx4S7DKe7e/LZCqNYJg7nVQFvRx4Hn7p6QP+C4lHfSk6mJwSE0nuTMnJCZQA1A/U340xnIshxBsbaicKEbddxx5fSU5Xcy247iE6ZpAoNIAYkcjtTQTsGgQ7EMGduTS8U0rKcTbpI3BTzYuwAAyz808jClL9U5cPItBPxFjVgYTYXqe+xUKUh2kcd3GVtrxrEMTz4c2HoIwvKk73TrdA8LL6Oe9FeonMuk3x0bBee4huEktGaaRgt98/vvFRB60kEldqCOSqGjpKsi3DU1YmqDDriOFUow89hJyspHNc0XmV8+FixEiW/qta1A30ddMmTpH+fFN2y5D1kIAPWmY40U5hitadGuWlB68rYrmxoT+gaZKCFQZKXujjA7SeKjEFlzbLyI7mGmZW7gb4f7GDShuo7iVcyfJtmiG3U91jMuNHhOTHl492Z1fxCRtvxxaxL669ynnc3pm3gDYqYVWu6FTVPS55sp8/fn3WafKnLHLaJpvqQgPcTk2UX2+sMiJSE3Jx9mOMlHhBZlKpSPZ87HEVn4huodhzOO3BZ4FGBz3XbBYtDtw8ovJUivBChE5ELEaApdjF3hnZQeiLHQpLHGb3zETOhV3oeIjwXy+1tmj6Jv5JEcnfqp+837sHUPMweOPQ1X4I0ARW3EugmQSVLWt5edyBcRNxuKFIr2ZZDm0V8LJo0dtAsviDguxO/D9dk2bzkAtUoEB4SgSWIpMmHW+sBC5uQ48pHu4QO70AHHY/k16PDb81oqIhtpqVbW1EQ3YmKLxzO+5klnWSVeNXpHHDttH5PM5T368duMABrFge27i+szoUhsSWmkqdgd+oMKE/L9w2HUJOtCouQ8CGK5c/WFAB51TAOeY6jmZ0snrcSYhshhFMbhByGg26LVQB7XiGmmTdChjH3JtpXS06D3Ezdm2HsLUbcdqzzNFppledi59ix+0E0r03/ft+y9glG79zvRRKj3bTA9/3DNcqJHG/srRiX8D8x5OI600hGKWOoPjnRclOXgU2Pk3vHEim8T75p5Cdf1zYKiq4noYkBL1CNhAyKAANks+QUuO6fuL/I68+8xZt5uGatwCYGrKoKJodevHe/aCge7DYiB05ssgu8F38yCNL4TevBAswUExP6N3lHBGl6E6UHzB8Qhp3rtR4i8ECVhcJE0ceNyCMdCCjjozlr7SE3nMyR9+7YYgrSlAOOxlySrq0Ce+O3GCcbPoyYx6t3sWA6LFm11UHkpYcH852dZEfRbvNXb+kcc8g/2wGElR9Fu5S8G+fzyMoAjpseMrEgWxBxuMowkmxRCJ57Zb3+wDL8jlPyGhrW/ExiCZpZ5eE9P11n0HG3VQpEzPeHM1g=
*/