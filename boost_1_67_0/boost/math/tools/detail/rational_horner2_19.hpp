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


}}}} // namespaces

#endif // include guard


/* rational_horner2_19.hpp
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
*/