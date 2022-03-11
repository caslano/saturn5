//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_16_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_16_HPP

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
      V t[4];
      t[0] = a[4] * x2 + a[2];
      t[1] = a[3] * x2 + a[1];
      t[2] = b[4] * x2 + b[2];
      t[3] = b[3] * x2 + b[1];
      t[0] *= x2;
      t[2] *= x2;
      t[0] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[0]);
      t[1] *= x;
      t[3] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[2] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[2] += static_cast<V>(b[4]);
      t[1] *= z;
      t[3] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[5] * x2 + a[3];
      t[1] = a[4] * x2 + a[2];
      t[2] = b[5] * x2 + b[3];
      t[3] = b[4] * x2 + b[2];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[1]);
      t[1] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[1]);
      t[3] += static_cast<V>(b[0]);
      t[0] *= x;
      t[2] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= z;
      t[2] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[6] * x2 + a[4];
      t[1] = a[5] * x2 + a[3];
      t[2] = b[6] * x2 + b[4];
      t[3] = b[5] * x2 + b[3];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[2]);
      t[1] += static_cast<V>(a[1]);
      t[2] += static_cast<V>(b[2]);
      t[3] += static_cast<V>(b[1]);
      t[0] *= x2;
      t[2] *= x2;
      t[0] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[0]);
      t[1] *= x;
      t[3] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= z2;
      t[2] *= z2;
      t[0] += static_cast<V>(a[6]);
      t[2] += static_cast<V>(b[6]);
      t[1] *= z;
      t[3] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[7] * x2 + a[5];
      t[1] = a[6] * x2 + a[4];
      t[2] = b[7] * x2 + b[5];
      t[3] = b[6] * x2 + b[4];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[3]);
      t[1] += static_cast<V>(a[2]);
      t[2] += static_cast<V>(b[3]);
      t[3] += static_cast<V>(b[2]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[1]);
      t[1] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[1]);
      t[3] += static_cast<V>(b[0]);
      t[0] *= x;
      t[2] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[7]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[7]);
      t[0] *= z;
      t[2] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[8] * x2 + a[6];
      t[1] = a[7] * x2 + a[5];
      t[2] = b[8] * x2 + b[6];
      t[3] = b[7] * x2 + b[5];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[3]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[3]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[2]);
      t[1] += static_cast<V>(a[1]);
      t[2] += static_cast<V>(b[2]);
      t[3] += static_cast<V>(b[1]);
      t[0] *= x2;
      t[2] *= x2;
      t[0] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[0]);
      t[1] *= x;
      t[3] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[7]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[7]);
      t[0] *= z2;
      t[2] *= z2;
      t[0] += static_cast<V>(a[8]);
      t[2] += static_cast<V>(b[8]);
      t[1] *= z;
      t[3] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[9] * x2 + a[7];
      t[1] = a[8] * x2 + a[6];
      t[2] = b[9] * x2 + b[7];
      t[3] = b[8] * x2 + b[6];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[5]);
      t[1] += static_cast<V>(a[4]);
      t[2] += static_cast<V>(b[5]);
      t[3] += static_cast<V>(b[4]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[3]);
      t[1] += static_cast<V>(a[2]);
      t[2] += static_cast<V>(b[3]);
      t[3] += static_cast<V>(b[2]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[1]);
      t[1] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[1]);
      t[3] += static_cast<V>(b[0]);
      t[0] *= x;
      t[2] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[7]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[7]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[8]);
      t[1] += static_cast<V>(a[9]);
      t[2] += static_cast<V>(b[8]);
      t[3] += static_cast<V>(b[9]);
      t[0] *= z;
      t[2] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[10] * x2 + a[8];
      t[1] = a[9] * x2 + a[7];
      t[2] = b[10] * x2 + b[8];
      t[3] = b[9] * x2 + b[7];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[3]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[3]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[2]);
      t[1] += static_cast<V>(a[1]);
      t[2] += static_cast<V>(b[2]);
      t[3] += static_cast<V>(b[1]);
      t[0] *= x2;
      t[2] *= x2;
      t[0] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[0]);
      t[1] *= x;
      t[3] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[7]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[7]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[8]);
      t[1] += static_cast<V>(a[9]);
      t[2] += static_cast<V>(b[8]);
      t[3] += static_cast<V>(b[9]);
      t[0] *= z2;
      t[2] *= z2;
      t[0] += static_cast<V>(a[10]);
      t[2] += static_cast<V>(b[10]);
      t[1] *= z;
      t[3] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[11] * x2 + a[9];
      t[1] = a[10] * x2 + a[8];
      t[2] = b[11] * x2 + b[9];
      t[3] = b[10] * x2 + b[8];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[7]);
      t[1] += static_cast<V>(a[6]);
      t[2] += static_cast<V>(b[7]);
      t[3] += static_cast<V>(b[6]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[5]);
      t[1] += static_cast<V>(a[4]);
      t[2] += static_cast<V>(b[5]);
      t[3] += static_cast<V>(b[4]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[3]);
      t[1] += static_cast<V>(a[2]);
      t[2] += static_cast<V>(b[3]);
      t[3] += static_cast<V>(b[2]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[1]);
      t[1] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[1]);
      t[3] += static_cast<V>(b[0]);
      t[0] *= x;
      t[2] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[7]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[7]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[8]);
      t[1] += static_cast<V>(a[9]);
      t[2] += static_cast<V>(b[8]);
      t[3] += static_cast<V>(b[9]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[10]);
      t[1] += static_cast<V>(a[11]);
      t[2] += static_cast<V>(b[10]);
      t[3] += static_cast<V>(b[11]);
      t[0] *= z;
      t[2] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[12] * x2 + a[10];
      t[1] = a[11] * x2 + a[9];
      t[2] = b[12] * x2 + b[10];
      t[3] = b[11] * x2 + b[9];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[8]);
      t[1] += static_cast<V>(a[7]);
      t[2] += static_cast<V>(b[8]);
      t[3] += static_cast<V>(b[7]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[3]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[3]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[2]);
      t[1] += static_cast<V>(a[1]);
      t[2] += static_cast<V>(b[2]);
      t[3] += static_cast<V>(b[1]);
      t[0] *= x2;
      t[2] *= x2;
      t[0] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[0]);
      t[1] *= x;
      t[3] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[7]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[7]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[8]);
      t[1] += static_cast<V>(a[9]);
      t[2] += static_cast<V>(b[8]);
      t[3] += static_cast<V>(b[9]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[10]);
      t[1] += static_cast<V>(a[11]);
      t[2] += static_cast<V>(b[10]);
      t[3] += static_cast<V>(b[11]);
      t[0] *= z2;
      t[2] *= z2;
      t[0] += static_cast<V>(a[12]);
      t[2] += static_cast<V>(b[12]);
      t[1] *= z;
      t[3] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[13] * x2 + a[11];
      t[1] = a[12] * x2 + a[10];
      t[2] = b[13] * x2 + b[11];
      t[3] = b[12] * x2 + b[10];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[9]);
      t[1] += static_cast<V>(a[8]);
      t[2] += static_cast<V>(b[9]);
      t[3] += static_cast<V>(b[8]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[7]);
      t[1] += static_cast<V>(a[6]);
      t[2] += static_cast<V>(b[7]);
      t[3] += static_cast<V>(b[6]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[5]);
      t[1] += static_cast<V>(a[4]);
      t[2] += static_cast<V>(b[5]);
      t[3] += static_cast<V>(b[4]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[3]);
      t[1] += static_cast<V>(a[2]);
      t[2] += static_cast<V>(b[3]);
      t[3] += static_cast<V>(b[2]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[1]);
      t[1] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[1]);
      t[3] += static_cast<V>(b[0]);
      t[0] *= x;
      t[2] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[7]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[7]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[8]);
      t[1] += static_cast<V>(a[9]);
      t[2] += static_cast<V>(b[8]);
      t[3] += static_cast<V>(b[9]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[10]);
      t[1] += static_cast<V>(a[11]);
      t[2] += static_cast<V>(b[10]);
      t[3] += static_cast<V>(b[11]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[12]);
      t[1] += static_cast<V>(a[13]);
      t[2] += static_cast<V>(b[12]);
      t[3] += static_cast<V>(b[13]);
      t[0] *= z;
      t[2] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[14] * x2 + a[12];
      t[1] = a[13] * x2 + a[11];
      t[2] = b[14] * x2 + b[12];
      t[3] = b[13] * x2 + b[11];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[10]);
      t[1] += static_cast<V>(a[9]);
      t[2] += static_cast<V>(b[10]);
      t[3] += static_cast<V>(b[9]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[8]);
      t[1] += static_cast<V>(a[7]);
      t[2] += static_cast<V>(b[8]);
      t[3] += static_cast<V>(b[7]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[3]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[3]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[2]);
      t[1] += static_cast<V>(a[1]);
      t[2] += static_cast<V>(b[2]);
      t[3] += static_cast<V>(b[1]);
      t[0] *= x2;
      t[2] *= x2;
      t[0] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[0]);
      t[1] *= x;
      t[3] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[7]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[7]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[8]);
      t[1] += static_cast<V>(a[9]);
      t[2] += static_cast<V>(b[8]);
      t[3] += static_cast<V>(b[9]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[10]);
      t[1] += static_cast<V>(a[11]);
      t[2] += static_cast<V>(b[10]);
      t[3] += static_cast<V>(b[11]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[12]);
      t[1] += static_cast<V>(a[13]);
      t[2] += static_cast<V>(b[12]);
      t[3] += static_cast<V>(b[13]);
      t[0] *= z2;
      t[2] *= z2;
      t[0] += static_cast<V>(a[14]);
      t[2] += static_cast<V>(b[14]);
      t[1] *= z;
      t[3] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[15] * x2 + a[13];
      t[1] = a[14] * x2 + a[12];
      t[2] = b[15] * x2 + b[13];
      t[3] = b[14] * x2 + b[12];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[11]);
      t[1] += static_cast<V>(a[10]);
      t[2] += static_cast<V>(b[11]);
      t[3] += static_cast<V>(b[10]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[9]);
      t[1] += static_cast<V>(a[8]);
      t[2] += static_cast<V>(b[9]);
      t[3] += static_cast<V>(b[8]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[7]);
      t[1] += static_cast<V>(a[6]);
      t[2] += static_cast<V>(b[7]);
      t[3] += static_cast<V>(b[6]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[5]);
      t[1] += static_cast<V>(a[4]);
      t[2] += static_cast<V>(b[5]);
      t[3] += static_cast<V>(b[4]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[3]);
      t[1] += static_cast<V>(a[2]);
      t[2] += static_cast<V>(b[3]);
      t[3] += static_cast<V>(b[2]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[1]);
      t[1] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[1]);
      t[3] += static_cast<V>(b[0]);
      t[0] *= x;
      t[2] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[7]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[7]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[8]);
      t[1] += static_cast<V>(a[9]);
      t[2] += static_cast<V>(b[8]);
      t[3] += static_cast<V>(b[9]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[10]);
      t[1] += static_cast<V>(a[11]);
      t[2] += static_cast<V>(b[10]);
      t[3] += static_cast<V>(b[11]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[12]);
      t[1] += static_cast<V>(a[13]);
      t[2] += static_cast<V>(b[12]);
      t[3] += static_cast<V>(b[13]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[14]);
      t[1] += static_cast<V>(a[15]);
      t[2] += static_cast<V>(b[14]);
      t[3] += static_cast<V>(b[15]);
      t[0] *= z;
      t[2] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner3_16.hpp
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
*/