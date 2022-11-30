//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_18_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_18_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner2_18.hpp
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
*/