//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_13_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_13_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner3_13.hpp
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
*/