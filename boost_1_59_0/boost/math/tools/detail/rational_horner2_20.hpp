//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_20_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_20_HPP

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
   return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((((((((a[17] * x2 + a[15]) * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((((a[16] * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / (((((((((b[17] * x2 + b[15]) * x2 + b[13]) * x2 + b[11]) * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + (((((((b[16] * x2 + b[14]) * x2 + b[12]) * x2 + b[10]) * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z2 + a[12]) * z2 + a[14]) * z2 + a[16]) * z + (((((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) * z2 + a[13]) * z2 + a[15]) * z2 + a[17]) / (((((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z2 + b[12]) * z2 + b[14]) * z2 + b[16]) * z + (((((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]) * z2 + b[13]) * z2 + b[15]) * z2 + b[17]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 19>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((((((((a[18] * x2 + a[16]) * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((((a[17] * x2 + a[15]) * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / (((((((((b[18] * x2 + b[16]) * x2 + b[14]) * x2 + b[12]) * x2 + b[10]) * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + ((((((((b[17] * x2 + b[15]) * x2 + b[13]) * x2 + b[11]) * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z2 + a[12]) * z2 + a[14]) * z2 + a[16]) * z2 + a[18] + ((((((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) * z2 + a[13]) * z2 + a[15]) * z2 + a[17]) * z) / (((((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z2 + b[12]) * z2 + b[14]) * z2 + b[16]) * z2 + b[18] + ((((((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]) * z2 + b[13]) * z2 + b[15]) * z2 + b[17]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 20>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((((((((a[19] * x2 + a[17]) * x2 + a[15]) * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((((((a[18] * x2 + a[16]) * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / ((((((((((b[19] * x2 + b[17]) * x2 + b[15]) * x2 + b[13]) * x2 + b[11]) * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + ((((((((b[18] * x2 + b[16]) * x2 + b[14]) * x2 + b[12]) * x2 + b[10]) * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z2 + a[12]) * z2 + a[14]) * z2 + a[16]) * z2 + a[18]) * z + ((((((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) * z2 + a[13]) * z2 + a[15]) * z2 + a[17]) * z2 + a[19]) / ((((((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z2 + b[12]) * z2 + b[14]) * z2 + b[16]) * z2 + b[18]) * z + ((((((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]) * z2 + b[13]) * z2 + b[15]) * z2 + b[17]) * z2 + b[19]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_20.hpp
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
*/