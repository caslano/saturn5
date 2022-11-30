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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
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