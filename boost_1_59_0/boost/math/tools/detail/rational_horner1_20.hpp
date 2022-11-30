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
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const std::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const std::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 19>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 20>*) BOOST_MATH_NOEXCEPT(V)
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