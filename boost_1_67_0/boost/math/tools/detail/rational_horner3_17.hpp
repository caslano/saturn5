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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[16] * x2 + a[14];
      t[1] = a[15] * x2 + a[13];
      t[2] = b[16] * x2 + b[14];
      t[3] = b[15] * x2 + b[13];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[12]);
      t[1] += static_cast<V>(a[11]);
      t[2] += static_cast<V>(b[12]);
      t[3] += static_cast<V>(b[11]);
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
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[14]);
      t[1] += static_cast<V>(a[15]);
      t[2] += static_cast<V>(b[14]);
      t[3] += static_cast<V>(b[15]);
      t[0] *= z2;
      t[2] *= z2;
      t[0] += static_cast<V>(a[16]);
      t[2] += static_cast<V>(b[16]);
      t[1] *= z;
      t[3] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner3_17.hpp
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
*/