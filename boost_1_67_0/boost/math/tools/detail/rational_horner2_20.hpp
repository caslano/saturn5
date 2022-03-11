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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 19>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 20>*) BOOST_MATH_NOEXCEPT(V)
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