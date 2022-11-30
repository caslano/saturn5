//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_5_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_5_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner3_5.hpp
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
*/