//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_19_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_19_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner2_19.hpp
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
*/