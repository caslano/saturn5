//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_15_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_15_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner3_15.hpp
fRvR64WUgU9ke263fWv9paBDJ835jdG0IMKCyDMaSi9gYdRn1CVqTEFcBrLIfF8DfCNlCzDzk8GyHKFEofXpSk78HIC/FHGJztViQF5+Em86TPn4hOh4k6N1MR4uzGTW2bFPa7lWuuotPUGkH1omhBGwSvdRu0UkTRBGFaNnjeZhRYyiy2DIpDjB1fz3dCj2CMDTuxAThf4/LWSoo/EW6qCZk/E0CUJXwlwtK/1U9oWKtm6fAkINb1O3xmirv9EGzabtBkxe4+KOSlx6m7HCjiWYyank9lQ7uY1+sYeoTNp6B2Qhl2nsLTgjEWwSE3wfRlJrKQxlZbJwxKI4DcowZItsTpwc9UBzJPLOFUkJruYY2MXI750n3fshAW5m13qfxpgEZISGzulreXUU8OLDWHV9WpeXuiJfozyJVtd8kuUA79x7dGkpOLE4NKE0dcEZqD9aTq3/kCiZ7nuBsQANpFOkOb2bN9JLoToG5GKs49dNH6lrHbRpMvKlU/OZgegX3LG3P36ngHNq02+2FlXWek0Vup6dcIoLAKlQjcWYLCGn/Zt2eyYaveY5uj0TWX78SH77Rc5x5bCV0pceNpZoFqKl+rdU0acWLB+A3OJJiAxG2EiSONLvAF9CCgu2WbjpgXIwPITrIhUiWvihysvYRpN0cJkflmo2mZUtYT4rCmZtZeCMqh3WTiWKtroIxps+5axnuFfBcKTO5t1h2JYViM8D62yTq5dMy0KZAFkTeMr+rMjgIA+bcwg/KpGQkYNMTbXIPKcPeGHHHh1N5q7j9KY6O1nu+0vePa4Xhfw0TJCqs3QSLoCfvi8rkYQzi7sgWGTFs5GbkaBsX1lRwxRZNTfLSGD6r+V85BDgLELNxOCVKjGL2tQVVfz8d1FdFibLSeyqt8wp8917KnMSTTh7cHPn78vfMkfN8s4sxZxuWcnFT3E603SS5Ez96u6l4iVwbnqT7lIesaW3I8UkgGJqjO+LrjL6DtHebnqJm8Nt+W7issupk6yYa2JM2nguZn0XnjBwuGsbSUHiExQY7uR5kEJaTyZZ7LTQxi3wvZ0V/eQtI96p9gc7VLxI/ruSqxd3k9DKw77jKqcPd1QYFicuPzCFLYuGA8IftQtrKNy1/tmXd6bwUrAJMxyIgIs1n2kRGhLv4sNG81X254rLiYjQ9AL0Yk9TReql4BD3zIwRJfZWDioifk6WF2gfrT/Ss48PDo6+E8S9XRQp5eTVFdUCn6skgwW01OF3LfWyRxBQeySZGzrgH3RbLbORqjCPXBSfOLCRCUPcsnKuMRmAMknXX8kARc/ipYI6SyXFd6XPW/2Kfbmr9YaCGdKkrkru46Tynuezr8L6nVQxmiPNpbKiNQAN6ngBO0keY0TFb+dq7jfHzshvr7XPioTA7SQE4WyAmADLSE6NE5xw006rWaCUcWJew/lUlsJrttBcByrqETq7Az+/hPCFKilI9jQev8rHaEwko7jgVGzYo8kUufUo8z4RXPKVlIg+1f/HSF1FYmo7Dwk1MljB+aJ4jc+c/GIIEkca1TnKAwC6NCaxd4B0In3ML4dgFJCR+x/0DZKje4jl97VwjwDy8Pv9Fof+ITqJFXKFqGyCE9HXeXYNgGQ2sSYehOMKEPQzWWdN5TpK9FNBaMZRjB7tL9PLxPBTI0JdwcoeKPeALlmuGUKNyjbbyhY2fOHEx+phVaoP0e+Ah12SMPMd7NkTXH0LZDeUd2H+JU7bCOLtdYCgEoHKLIz5E9E3XTziKJTDvy+wp2RxAY9derKszLW2ns6trMtJvb0OLDi0DR6+hkQ3pV8FSbEacIcmMNIqoQPoSJEMfrQTsxrJBw6ZZFWPc2qQ3W+kAnlY1uKe0IS2VyFok2gqgRMl38rqylTk5Cx7XwXLG2hP2QYdvpiKH9dz7ZNT60RxsWMdvd0hrXbF5yYpHNYW4Vyb+h4kAsCwQHI5DKadceUcLMbYxxwV1E5TMh0OAuy4lx7xEICsZLn5McJ4MmsaEjB3GVAEAiBUfuZ80hHYjcTxCztGsS3QLunEzYBMXonIPg+gXhs0k9NPAXsJkLMJHDYgoXIqcjfMGIduMqkBEai5gGbFxqy+5MMP0no/r8ceZAHJruHhIK5Ysr4BWOZg871YLO7+QYqqz+So8VeiCqwSvCGKyx5fMzdqNohyzVRL+wPDsEMryX3oyZ8Kg1HUW9EPsODzUKUJcmNxHl+SBN1KOe3YmrasvDsnMx1gMEtPsSwezRUFT4Pqz1x5SKM8TL9psPJXwFDAK0XrFDwPd868PG+BGY3NibsNIImKb3I+nKQCAPlJjc1Ch+LcG/8VsC7xE8cA5v8y62i0kOIFBi91Wlh/UaAoxuehVumQlc0wdPJqrWoLnADds5hQCeP2mXuohHY9PM4I3cm/GeKvc+74itjhlMZInwbnIU+Yzy9mqLm2MqkYvEwXq2NYztmv0Md5cl2F8qp5ONg1ML8gV0SsB3P0ynYsdfV9s1tMO2/Dxdjn31MG5hL+4xqScr0XVXKyiwG3S7ClrZdk/3uJJKbXbLKpuNUtlJ+gqbCKw+d0X4oHQB+/L9wVVEAXQW4xRNwjGf+6d+MXcjYodrnLYq7aKmeBOo7HAoyhLQWokMTvlnND18xF7k4SWNu8zZUACCz30/QxtKiWCCx8OHpzZqXVXWM/ZzgfF0mHrhrpH7mvp3zIvywIZzNzbJcEBmuZVZAf0NrP4+CicpatWEjO3FYrtYH9jzVeI82ma3CuFl/NM1mBPIBqiVwbYc0b5ija8bm5ZGnEwwacKcmi1TmhQuijNg5YfXKzrOtjkwwkR1qXaHoRT9P3IIq3KujTAZLuSd3OOphrsXLaqxCuAG+nnyCoeGisOVoCLmumsJNWc+PKu+iRDGJhoaHQuvG1pdG6cT7QJVfuaLk7FibocgF6Nvg/AEJ/XDWDtF0761kTZkQwZ6WcHyn+XWrI/aMQ01p29TaSVgQaMr+Y9z/XyHUaSCcgTwgjypUGDLNf+hdnuS+x+bCoyBbgEJhVZbet2Atnrn3URQUHBsJOhTNB18b8oTMNN3zgcOiFcHGQnWK5ZEsQOWsWvBeXVMThX+vaGAGdFZT8O1VHr/g+RQq3K3CzIwauAnBixWC14g6NwnKsY/nNymb4Qw7AqGq5HvYcFrLDe+dTw7e1qf4f5CfAY2piN9WgmziMOdPsBn1fyHcmrR9urk7dflJ9zwFiueu/AJPbN6P6MQluaK0tN4KpdjVtL21yvZiPbRscXTJIuqhnPD5FI2RI3YD4miUG34MjWB932D7hDTrG494bPUHTZk6bcI8HKJV7ro4fp2/XEYnjlFYcgL+h+Xrh7AG8ZwcHBBC4YIoXJAYcUf1ogFXGjq1LOElqJKFvLaA8hlI4raFFw9pjSp33mHv8fQqc8Q2fBY06ioeIN9cf7K8K32y8EtfjZ/+nlIxOK3bgFMk6a3UraUyNXm8xSvCeyKjnq73X2HtJTylXtp5xrAA8Xfp4bXzgglLuFsIR8O+EvpbA78JeB7TqNBRfjUWJLQHXz0fo5acucLVeraP0e2npS11G7u1DzQcGwzikN1709S4gXS120W7zeSfCgXiaWr/0z/WBbMN4AHD6JWTUN6rAWk0mYGuchB67BIuOpAKzHv0RybOu0mjqtXTXLDlw5gXOrMoXm9Qik/bWEXx192S9LdqDtHxseQxYijJTykY6hENP+mO+wzVGS8OV5lb4YZQhUxGyur40eK6nvnGmUDnxEh0gGeWByEP/OcxnZDYjMysePJSOIhB65dDiBVUqEfTFxgoAN9pGwGOrbU8TQDnev/vHXCDBmQ4DChV9JFhEH5LstLEYufhgU5j7RRHDrAA+BL3mEkQC0/BGKwo/Y3dbEkP2bpGtIyEKGyWT1DJjypRkmY++3paxDPzu5u8tbr7H69ScpEUun/JvZazU+AGno//6IeN1olQqol7ODJGk1O233Bn0cGg05pN8p80fxL9Fl+mm3yUrnSm59wuE7yHFWw3/3RDMOzz4scFhEkBIvyFagVeA3nAoXgIrKF/CPPbOqzrTJOoBBweLvgYUmXepK+XyoJouwH++pzkIkiaUaP62Z4HQpNQaaNyT2HIII/Uvvf2Cs6JakwqccC6S6+0pdAr+CBalfFR+Eqm0I4K+gorGLrH6lbNVH0vPnqvRSbp7gASpLJ/oBqfWjebpkAjruAx1NCla68C7mEj66y86g5H7eHx09KWo97gP/IYSiKKt0osSgMt2r5D+yhiodn2V6u+cLiy81O1rakAi162JNnD6msZ6eAURFan73uT+8lLU2uT7h+LQ0NyLjjLAtBeKAdAnp1/5XKyT5oG8Am0gD+v+tbLrxgR5eD9h9XczsKArSykfXfchGXaa7iqK7RhE7reprZJCnauN8lBgoQraNYnQehHS0ZTp4zFvleUYvz67/n/5F3iaiq9qNbObShHkXGyLb34AKCYtYQv+aEe68gbQJtFINzGQTOORsZz+qJewD708FwgurSmTNjAj+jM8X0YoQxMyh/t4z9lJZPfms4MMzaNd/Dmb1287c9aQyr6pJ5ersMH2lCAOeNGCYfS/Og65bZm1GxfMmMa51KOjPHjWCWmsXZB9BaYjk3QGt7uaUCcpzimBAl71JR7s/ooABE0Prs+tIh6kTwxjmaUSLqFtZZ9M652pJpx8fdJg2su3wstJyCXkJjiPIuUWQmtzEqhvYITFYVKjyY5X8ABArlLE3ykwVjOeKFoUMqGcZ1JuUEeVVb8XqZ3i2bkmRPrJzftzDJQlh0uuyNllFmEOgc71moZlYIyJHMIiHxkD3z96KYP3GS0jqsNH31cBG+mMamKYtI8bf9/xthINw2syv7XvVG3s7wGIBDUlffbWNcb+PRFOOaHz1T30U4JIupJlpOc+JTxotZhsdlWSGp6/GfkWZc6/itr7V3WngxAfsVRccyyMcOR3353uMNSEbJ/g8qjE3MykoJ9hS8TrkOjSsv/pleqU0cYPcHEzo0xDIBkCMIwjDP0ccD3GPGy0xBoKppLi+g8GxoZ6wA/nHXkHTzB6QYwdqaT2WB6v7wiXEjJ5F7pMEpQWiUM+E31OLldkjsmpG24DABsycf6xhn4PZDcUWTUEXNnsV8zD9+RI9VW0I1Eq2xCLQiWWGCKNI9vvdBi74FMaq12QjSnu0cx3S7C4fvFZbp2euQ5dookhDtNAsCLzP6EBAZ95abEMkb3KXiXVoeRxcwWgW5PzitH1B8qmsjDuDE88IMi3ATJy6bqoPGrkBLDmYt25VFtz4pnKDEhb96SpXffi3u+Z5dHG3LgcG3penj2YcLB+QUOr9RRQVEu01HZvOplE74afSZ3yFz8LGpUuZ9EEN2erZXl2y1tFV6Tc7r0Wd4pwQbdqyMbsCQ3S3kT1zN69z/c3ij7qTk/sjX1wGF8rK49DfOGeJFGsFmjg5JFawIonYgeLtj6cC3iwvTdKgnVknBNdsJtxD4bHglQEcezHAUvnZoMiHWFmsRc5lNjyw/Lfa9TmsX74YNaXpTzAMxZwAku+vPaaZm3IvDmV+aMzfPQRZErvq7FtviSTUEeCR+zs61yAHWCR1/Ooa37lioxXKKYs8xkgL7Q4L9G7pPfu+wuKCiD2emqgKAWIFPvQK/tcfpIkKAj8F3SXRYACVtrwzmt++BTrQVK0PdP5a6Izwq8ihtgJnhEPKdOfVMspGKeyezRLtKooYESydYKG31ZJrwgIopRof87/PH8WkjOdv9ZbGCW8qdZi+Jf2iFI4f+aquvcvl9/WbvW3TZEmL/q+I0ShJ2vsQU1h9JypchTNWX0MldAV6x97RLE1S2QeuiiFz7K5bmdW2UA/VvbvAwIWhXPfnSYzRh3w3rfJ7pxOO0Tdp/E1e0W4/T8ypyzxD7cef8tkfHcHCcGFt1RKiFyt3/TfRh/h7PU/xPt9WsvGwSQyhkdPxX0sCxPWdxtyYzTRaDB2T5DuIyU9YRryAUPI4f4XN6eUazkOnhif/Nbf6UUkAtqtYLkjVxXisJznT81X71z7kA3xtScXiiVOitH5Zw6W1TWX2WO8ymoRWOA+gorppLCsGKN33lHvPpFFxwhooMMRmszRQdIxJNypNM2sZJqPy0ly0pQEtdxKPKCXCtGExErtBrT2EeDnnFo2O7kcLsYWoqRziSytbaRKaU2ve4TIMXED7VwoemfejscrlV5yw1J1obYKqCGfEQzyf29ejXl8R259BqxA5mhNTC82SN801zm9fdcypAILlYQ9FDObOn4eRkLWKaHJGQ49m2X4cbORT8ZqU45QANnKxgX8pvTFvInWkCTdAFMg64EF2jyUYBfwUJ9CSFsfHmLk1ZIrzBkrHZOx5Xefti9Rbg0RCSJIuq7HUkkfaeXae0EnwHw8VYADIqQKw2WxMF0GZ4lDw5GQRIQdlOzn0HaVl/icMipJe2Y5IA+SlTPQuVRNWuzvNgJIHeGqVhlpRsPBz/BnDXc810nHkZYKfX5algRXxU23jMfPUxAh7wN8o6IWZpkthJfq4RWrbgX3u9VJHyusZOAi+cwwX3QtsOErHTLY75K/Thhhcqq82GByCbEeEo2oGphgzVGlaAZFHfX627UR88gC3wCa+wb0Z5T59bAbPGz3xAQ5f0CCyyRhxUWNK/Ch43Fi4ZSUnPqre9Btt1kW/cuD5xkq32FMYW8hrnZ6KMQVV/yLzJA1SJTE8G/gQYENoUsO7Y5Y0eXfIiPNGc7kKmQc0Q/tk28xe/BtgqNPveinbsDesKgdldRjnjlkDrUjy5B4rZo9pvRVY7x7QuVFfJ+VoFTn87grL72P9XX8Xr6oyq6AS6GuHFPKGjFObZpZq6rPQq+TfSclIScvHZKmyISHCDQKWWoSfYb5PQEZ8FFLoJbuf+Uwjlb40DmS1/DzKoRpQQpJVkvSFMB7b3R+eqnkm5DNhC4InvF1m+FieliZKdFglqlxckNzAEAJ+Q5Ajgt9AKgIjt2sWRJSyykz5zHe4RCAZm9QB8TkTQrRpatCmzcgIUJh9SAQ4Vc+nlET1HgiiWx4HJcGCA9p8AZtChs2aS92ZXscH7OR+ZgvdDqJKECKClVDG073Xws5nRGJ0g0z2nsd7ue/CZ+1+Vz9fjVbwX/66J3aR26R8sFxeMuHohyAuisJkbRW6ADWFJbmcwyiCvPz0EkxztsK1mowW8IP08wUPOlE4G/0QOJYnp9IqgzQLuO0BOzX8G6K6hEKpkjvVp7uED946QZE2rEe4/7Hqbxg0krWgYIXFViiU8FSzvq3kYqqOfRUCgKK8p1X+vhz+czljPzIkbwiNxoR6eTNCH+XwGF6cRjaI0wYSTU8ehJ2pCY4DxB59VsGzHJ5maaMPsgKEN+s/aKrl34FbOnnN2rAy5pzNq/K8KVyZe/0gux0i6egKwiRecjP71u22YJdjaQ2BSZOnUcgczkDAaribsJEJ+CBYLrztodmqC9ZlC+jsynFHOYjSzVzcEZRY+GOCMN2W0Qu+IBanqwRIhCJQnLkyYWp7lTx36QUX/ELckjS1Vyp4DSJjGBd7wUnSXb4F4Ulla0kK0z5UEBiZqWDS76HMamW0ZsI/Y1ILgHde3x/0YNU0KvNmEaUEPypVzIQYRO0kwkbn/8q0NQj8k3Uz8l9Y8d9nGIMHXEFelb+CMWFZX9Fuiv7c7Jh8GlW0uTEngBhUe0KCUpUSlS2YDLSj2dq2cOuDMGt+xeCXDzrrBF+EfERJNlAgdpwoDv9EXtAjm9c9vrdJsm92w3s0GjrkiPcfArdQxzREkALwCi/tIhOILmr5r6Zb2AACzxfZyLVIQ8Qcp3Ek2zeAeBrntfXS4r3dEmTHcnTgRIFmUNgN7zIAvlVOoyyciqDk4bz6/SqVL849bSsD7u46VPmnJ9/7Mv1bKVrFoNLI4YoIanDs8lQb7zF8e+dqG+PbQDnXcjZR96ZvO6P76IS4mKqCKueu/45opqbV653VEtV71NWffvYCsUIyvYD46CHBaSd+YSA6ubIRlHYUje/hkwLPzXvdVq0CH+177Gfgqh6wNS26KWef4nABLBxB+YiQ1wI1J7VNJmy+EFLrH7DOtZopWth03UP5MyqqChDf0swcuiab3dRACxzmaBLBzeNJQZD6bMxVvVbCTku0H/qkiZKCNRCS+lovQUyJ4DL3zOCQ0J7i3CsdX7xNNns9DmzRrrgzjW7LgAv5YZVJtb43dQXvXWOS63NylXVeLFG2nYgf+lWuDHjXVM5GaGVs21b622KAIRlV3S3xLWvEC0PY+miWI5lORY7X9FOiT1POgbFC1dcFMcbMJWf78Mkdd13Tf+2y5MtA3lGoZ38Pfm4GQgYU9fcOJPVHL86GUX/zwaRF7cWFK/01F8LtD5T+s5uuF90QMAsX9Q7Ct5f64noaczCwWpuK9G86Eobk6cyvuRB8YUk3Sk1rxP2r4V1T7ckdb+Vp3nx5FK1uiJHbxcb9+406z6d2LY4PcYlxwhJmXIi2c/bHYHfcJ+pgwB11CqfYRN6eP0ki3x1p0xJ5NuTUfIOxOwG+9KGGpE0ofglEG0lR1tgPZK85gAcsAt2/VVkVE8AkWgiFK5jiHHiFhTlV5wyBKsQUT9lH3cI8Uu8NV2grQtGWfkP6shqN/pf4GRqFBrefbUMRWtxV8DU6XHTL0ef/YcAfF/F0Y6RKWMAevtHxJYKbJKmpBTGzqFPN4EV91KDD365GXNuh+YCzkTe2rG7Aqo+WwmdupJ9LOyETGVr37l7IgGp6CK73n0zrJO71iUlcr9gLOar6jqCSyfvdpUHqu8PnYJVDmTCsa8WCDjjeTRXpZjyCeI+tblDi5ZAFWTDLNxh0Sap5TWkowSQBu33ttGE4MR6SJEhieGf0ZBBoDdBx2oqINmbfgc9AKM8i4IEmJjOfgWqFnBreuup8FwCh8llAP+9U2gnGwK8k+DRrHotyIJlNUdJQh4KdOxjJTpv2zI98pzj5v+CYGaRiiYp5Tfa79kEKQeJGkydeLtxigvJYDTc6YqdvbzqRF0WoopF6XWXFWq6QNpHRNBRvnQgEjO1uscwzUInDmCVg+ct93YAQKqjIy0QBoGdN3UNw6Goo4QFWmgo+mOtF7Tw2xhoz5wVOyWIUPCtY04DjwmM8aX9IcK8QFuPHjBxjpa+FXFEuviXIHltdCxeIDnaw0eRVzk=
*/