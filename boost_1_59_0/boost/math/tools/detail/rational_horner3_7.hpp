//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_7_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_7_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner3_7.hpp
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
*/