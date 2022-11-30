//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_6_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_6_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner3_6.hpp
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
*/