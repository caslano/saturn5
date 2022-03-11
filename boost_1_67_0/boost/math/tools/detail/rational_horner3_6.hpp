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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
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