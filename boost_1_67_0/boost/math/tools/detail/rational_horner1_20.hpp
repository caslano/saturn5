//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_20_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_20_HPP

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
   if(x <= 1)
     return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((a[0] * z + a[1]) / (b[0] * z + b[1]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((a[0] * z + a[1]) * z + a[2]) / ((b[0] * z + b[1]) * z + b[2]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) / (((b[0] * z + b[1]) * z + b[2]) * z + b[3]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((b[4] * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) / ((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((b[5] * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) / (((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((b[6] * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) / ((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((a[7] * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((b[7] * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) / (((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((a[8] * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((b[8] * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) / ((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((a[9] * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((b[9] * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) / (((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((((a[10] * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((((b[10] * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) / ((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((((a[11] * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((((b[11] * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) / (((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((((((a[12] * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((((((b[12] * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) / ((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((((((a[13] * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((((((b[13] * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) / (((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((((((((a[14] * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((((((((b[14] * x + b[13]) * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) * z + a[14]) / ((((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]) * z + b[14]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((((((((a[15] * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((((((((b[15] * x + b[14]) * x + b[13]) * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) * z + a[14]) * z + a[15]) / (((((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]) * z + b[14]) * z + b[15]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((((((((((a[16] * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((((((((((b[16] * x + b[15]) * x + b[14]) * x + b[13]) * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) * z + a[14]) * z + a[15]) * z + a[16]) / ((((((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]) * z + b[14]) * z + b[15]) * z + b[16]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((((((((((a[17] * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((((((((((b[17] * x + b[16]) * x + b[15]) * x + b[14]) * x + b[13]) * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) * z + a[14]) * z + a[15]) * z + a[16]) * z + a[17]) / (((((((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]) * z + b[14]) * z + b[15]) * z + b[16]) * z + b[17]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 19>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((((((((((((a[18] * x + a[17]) * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((((((((((((b[18] * x + b[17]) * x + b[16]) * x + b[15]) * x + b[14]) * x + b[13]) * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) * z + a[14]) * z + a[15]) * z + a[16]) * z + a[17]) * z + a[18]) / ((((((((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]) * z + b[14]) * z + b[15]) * z + b[16]) * z + b[17]) * z + b[18]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 20>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((((((((((((a[19] * x + a[18]) * x + a[17]) * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((((((((((((b[19] * x + b[18]) * x + b[17]) * x + b[16]) * x + b[15]) * x + b[14]) * x + b[13]) * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) * z + a[14]) * z + a[15]) * z + a[16]) * z + a[17]) * z + a[18]) * z + a[19]) / (((((((((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]) * z + b[14]) * z + b[15]) * z + b[16]) * z + b[17]) * z + b[18]) * z + b[19]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_20.hpp
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
*/