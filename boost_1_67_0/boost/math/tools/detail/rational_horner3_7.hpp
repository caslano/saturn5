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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
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