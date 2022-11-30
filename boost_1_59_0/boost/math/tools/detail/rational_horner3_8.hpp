//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_8_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_8_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner3_8.hpp
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
*/