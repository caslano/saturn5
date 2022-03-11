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


}}}} // namespaces

#endif // include guard


/* rational_horner3_5.hpp
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
*/