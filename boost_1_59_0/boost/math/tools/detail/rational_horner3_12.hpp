//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_12_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_12_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[11] * x2 + a[9];
      t[1] = a[10] * x2 + a[8];
      t[2] = b[11] * x2 + b[9];
      t[3] = b[10] * x2 + b[8];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[7]);
      t[1] += static_cast<V>(a[6]);
      t[2] += static_cast<V>(b[7]);
      t[3] += static_cast<V>(b[6]);
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
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[10]);
      t[1] += static_cast<V>(a[11]);
      t[2] += static_cast<V>(b[10]);
      t[3] += static_cast<V>(b[11]);
      t[0] *= z;
      t[2] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner3_12.hpp
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
*/