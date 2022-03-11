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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
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