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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[17] * x2 + a[15];
      t[1] = a[16] * x2 + a[14];
      t[2] = b[17] * x2 + b[15];
      t[3] = b[16] * x2 + b[14];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[13]);
      t[1] += static_cast<V>(a[12]);
      t[2] += static_cast<V>(b[13]);
      t[3] += static_cast<V>(b[12]);
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
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[16]);
      t[1] += static_cast<V>(a[17]);
      t[2] += static_cast<V>(b[16]);
      t[3] += static_cast<V>(b[17]);
      t[0] *= z;
      t[2] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner3_18.hpp
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
*/