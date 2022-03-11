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


}}}} // namespaces

#endif // include guard


/* rational_horner2_18.hpp
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
*/