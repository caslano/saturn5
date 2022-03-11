//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_14_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_14_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner3_14.hpp
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
*/