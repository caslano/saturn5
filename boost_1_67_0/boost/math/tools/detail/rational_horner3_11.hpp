//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_11_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_11_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[10] * x2 + a[8];
      t[1] = a[9] * x2 + a[7];
      t[2] = b[10] * x2 + b[8];
      t[3] = b[9] * x2 + b[7];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[5]);
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
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[8]);
      t[1] += static_cast<V>(a[9]);
      t[2] += static_cast<V>(b[8]);
      t[3] += static_cast<V>(b[9]);
      t[0] *= z2;
      t[2] *= z2;
      t[0] += static_cast<V>(a[10]);
      t[2] += static_cast<V>(b[10]);
      t[1] *= z;
      t[3] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner3_11.hpp
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
*/