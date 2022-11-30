//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_10_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_10_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner3_10.hpp
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
*/