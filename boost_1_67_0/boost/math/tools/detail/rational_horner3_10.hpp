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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
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