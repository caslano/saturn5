//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_9_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_9_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner3_9.hpp
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
*/