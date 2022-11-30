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


}}}} // namespaces

#endif // include guard


/* rational_horner3_15.hpp
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
*/