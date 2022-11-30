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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
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