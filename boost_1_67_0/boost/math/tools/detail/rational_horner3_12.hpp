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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
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
jCeGH/oPzUt47SRG1b4nNhOMrc6vf4IABCz70xNxNEwnvcGITT/TetwHlZTOE6lTpKDEPDaq3jNSnt3/gr+fveu+CZoWE9WT0OujvpeTlsdX18WWeBv9FKg8iwnSMzDX5dZ1UWthTq44Ddn25dWGiz8Fn4UqMp+KJn55Wqc9LCbaUrGfFqYqapnR0tLKsPOZr6X8Ta+CDWaGlg96PfUerUvo2tYlQZUdyM/hfaa8Unvxodz/68FS8G4/yPRGHxj9iZN87R7D2YM7iXkPvYjzYZ9GNOR/PsNby04r8nU08Elr2m6rPfL9g/1SJrir/EDnoOuPpv8vKAKCC7oWYd3nTY9wRetEAriRJvXf29pEg/ixGQieO/IIkHYL00ilwC5G+H7y8re22RXMGav4sYb/MET4abh+3Isc0VG21YPuAFmky7dV1F+e6wCkvXgN0Ki4xfd3H2VvI+79lYRgiTKlq7fZw86NEnnQ8vPcf8pi1D8HiHs1JFVk+BAQ/0AT5ZkkJOHzIf82sD3DOf88FWEZyz+W9+0G/tA2uNtl56LnLOqyJn2MdMhliX53G0RDRKtrXDCMHNMx8uVy4wyIDuauxdPud9NpPmcA7n6yR5UTJeGoSCJ1zYbuaHDV2iZP3NjA3dZR8m3pbU7GeEwh9iJ5liJStImoA1sEUV//DbyxgWRD4ntZmuivOBIleYVPIVDyJpFCa2Uee4PJ3ok34hin2JDex5TXmQn92QGLoujeZj5B6OfA73FV1+Hg9bzMYbuaiqubPpPl5o/cCsd7Z5YHFYnM3FGYM8AKSUk2gpWPVqp/umcolaWlDhLbsrvlxW2FeAR/DWoH0H/ms98h345O2OkW7qglkN0CEH6HI0jwyVuAwoxNwOeoNOwU+TgHW8jZ2dtU5JPGBIUePf2ZqtyXP9u7rLEqwjRhsSFq18LqOpQR9pVyXGVKHUPP+vvbttnOwCZmN7PWZfgFeHf+ln/ppMlaEjvGeb2eQuMrBhWI8snEs5uHBDM/a6eyPVG4xPBdR/rugTq02HzWwCxj8zrGXyEVMAz2PsPEYOpu/XM/o0hpJmEXeFwvw7rj1MgYc45efVK4r8MvBGBmzCC7c3rCoMS4XMRINPabTtrckDJLeLeJaO3lL7UrsKmnINB5nA+AGZjIE/ZFI06bWpIyCSD/+tsoKonwxmsSPq70FCc0XPKFfdA1lB9+esGpRsv+ubnmC9n8aUd0W7w1ffaSrIkmkbsA1Pj+ay3u2sszJ3VRsxfLt3102RfzWSzSu93wDMfwL3ulY/mb0LRpwi39yt7IlA9HYe6L91OYOHnxZiyWV0n6K+pzJ5TPmJJ47WVUrrv3Kdrn4Dm6jGxHH2++EHJn5+zMAHk9eTi8B3J8KYhDSRbB6GTOPHtntG/NVHx5Jag196uPi5Cry30CgkrqR4iz52dQmWrtNLWfKP0fwcG1YvpYkRESU7aiNf9ZhrB6qaSzrDL5m9k758mun9P7seLz6+kLOTr4q21Qfpu4DaNVTzD34NWNgwjyDV/gHq0tkcBClDXdj00fSODOWR80mdBltKooKVt0ABHlYQy9K+RzrkGtQh3WBa2NWy1ptLLvDxv0Fya5zkgsUGwNityBCIc2j3Dn0nerlaV35x/tr7XV5dzpvms5Ppzg+Ns/sVf/fA/dTiSv7v4wNYyAtKjWzPr+yCFX/QV1Lx9Jokn3GZpHa+6W4L7wUfhBUjHaisXTY7nfWNJFgo0MRHKOjLi7+BdCmrrLKqrbzCN2nPjIOT4j5iE9NnfqJBKadr5MzCtEwCcQ5h25XNczdvtiHclmL+1HS5znS9G38SMvAwv7qkXLxPwwYwfc9XpsGns93YCVNdnC6rsywiPnPCv33Z8eXfj4uNOn/cMVBNSjxmZLLnx5a0VeSTciXOAqTnZ/LXMsIrt9eq4qJ3EMfp1W42+h+10nnqLnKtFF+rP7Cb0OspImoEcVdviJf0gqwCsnW2SKRliEG8xFl3BpNXtRMx9VMkMRROcifGsWXfSDkvbhISrSbCqW1FUwlzd2SuAxI4jAwQVNKEoc1FAE+OEkJrhLEgQkkYU/KPtBSGndGwPHNVMoqSS6GIxlIbt0Hg5yBnE37Ofb7yRJXMwhRA2zrVhgt4/JZ2TBuUqXm5z33YzxBU5xtIF3duMwP6/pdJLB6BhyMevJlX8UvfglHYcp/1xeh17nhxvetU6QS585Xy1dll9eE1wrk/hlxo0iBp+k+cqhJtbim9+qXE3s0rb2F3v/C9f7U7SQ2HUnoH+Fp+Q4ruH8uWy2/VX5VGcwgyeddOqhiKR+Vsd3j7RojkSptXsxc37WAXfsyxTIxDj+gm68W29HR0M3bPoYELIOoBbgt/wYVUgVj64h5bYqnEpL10y81VQ2FOSmTHfuPF1+dnpOGl/gTLWlrSa6S1qk0Bxh8jomNZ0inRtZhkIxuyEC2XTNwNRUhJQFhdvt7CJFt+jY9FODpvyvkRRB2yXlIwTBUyj+ovYO+9zCldAwwq/7W0Dj+mufmKkN6aYBLXMfAAQeyk8FSZCWLfo+dMky5NEBFwrSA4DKAwABWECbbuqDwdvKLSr13NIN5Nb3iEZ7Wsnperw6hhNDAjKSbEjtu7X8LPyk9qv7SpIFMiGFjXjPnlkj/EnIJvcM8r7BVJgdm75a0IKb4Z57lpLrEL945FuYn56zhXg1ymek6W8DCyJODekVqboxzXc4qPHlr7B9VfrSq1zCuOaDt379a420/L7qbd3BS8P3zxt3yyd3pYSvJsWYbVurZU/Iv/Iqsr9j9XkCcWXpec3K/NLSyPrYmPeTXWtKV6vyY9O68862u3mDM0Oz8+eveeBXTVNlTW58eNPzheXZp6Vmt1YHmycee87OyvSf0htNK+KXjW7UZjxTtM8V6evixMcn2dDvq5YR/G+bjR9k6P3PUDYMxnhouWLzlMmX6E5324y98dS0dnAsRyjcQZIIU+Iocomfk6epHexpEwg0iIKjyZgVAs2XoakFTjEfxWOVhoKMzOAsfX8QlIEsGK/myyTC7EeIbJg9nndIFM83IXZkkgf2j7zee/OhLLBTIL3Q2x9V1+FvfcnNnlTm4W9uNz3ntnfbn52vmTeDz33Uq9IJRz+V0x99L32qcOcyCmaKRiYHppZ0G9uXaabPB8Z6xi4HPPe/nft6hk8G+/r7qjfdPV09XZ2nxI7EbSfNLU0tTY21dZV1KvcdLzddKM+5oHiXdAottmtcU5ekE1IJX8SrqwXfxuqrPX/56uD56L56UIJ8H1N7Y3k/+WzhjexNjHR0DvU+SNku3q7rgzzCjcaGEsJIIaTgU9h2tn7EXV5iv7Xtz2xfEqlpOUJVhTr4uNi4Mje+L3foxuoTjL9Gl25GPl5KL7Qmphx6Vh7UVg3017Rktd3kEd29EvQyGoghHtFLDZ3TeUnxJbzOsc/CqvBAr8lsCuhqEl4COJeM9fEZdzdo3P9hvV03Lvyzpbqyv/vuDPtakpXBhEwh0M69hZnZwWKFJHgh01Uxiw7GZlNi3KC7kqmdtd5K8y6U6LKvm/EINwi/3u1p8iD9kGqpbmEPDMwPSMlTfdBUXtZQto97vYFvyj3X9/bK2Kjd043oH0jrjk81NrE2sPxL3HFovr7/syNP36art24ML6zsgx+bYzvzajDGZvgquV8jVH5wXTqtsP51Or53bNh5c2GTpWTExrfyPvyZ2cxVQNvCZxNT0371nYvJzObkq2CR/fGMzrSMprKEg4qj7ca3Yra8vD2ZJLEshSNFmSJILaxO3dKyCet+Nx3Q4aKqogpR5K7a4bXHR/ogVZuiTlOuJ6iJ1CjsJeEJaR4+g5RBSi+lkZJADaIBWZdgQNpPeibpl/z5505tvjoIMfyE1I50UTI/mfEPiOpYJZKaFIHUpORoalmyHxWHkmDJoUu4RPgl0gVSRAIMaYXUp4R4qnDqXKI9rSF5kGx4VgIbiU0qdSI9mYJ2gkz9C77vTyIFGaE0Y7CwPtIPqdjsz8ZPg348K2DzT6UvrJ7cTzn4v5IdXxkLMza4FYSqNicOORyroZAFYTkrWy5CkvV2Bw3PAqqZ2ezB6bKmx9xBl+S+6uzTlxLasx/4sBCfr4fuiz9QrOehlip6AS3AsbSdBN2eVxIDZWedjpYFXi1scHeD1onv655uStG+cuc7y7oP1/ikEclJ/i5aW5/e4s622UdJcMaUE3qJW0qwfzcCqp9VNy7Zxpf3rQawUY2InwNm0sVqyllI93TbX50F+VCMfa9hGtZWbkBPcu+Km+yz35PP6yroYvWeHcHWLVRuuaOINnu8X5TaR0WA1ufIRR/HnlS+BF3wvh4pxzluRjWxk+TqCPUbZEnrM920xVTHprGx1cZR2cpvi5uGEgW8DyAEfbgqpqwaID/UomAKIptHk+lol/9po8mp0fK96bCgugwusuDe+TUKrIfCbaodzan3mbYHR9YuPsqSilRuDRkbFB8KkZSbUuy8h3qPWADjWCl4q2Mq4xT1usCZxbnVCCy8SNqPoAV/ItFg4OMNher1kQqKLSNJHStucW8Vhm7qo++RlWn5Qa/crdj08azBbD1MVkK9xDBUefIOoTC6iLmwbsdWfj47NWwzZBo7IL66fQ/swmC/rU0a1zgPBo7HulZ4VCdCo9FGjbnGvcADIB+A2TxN68lVWtjSef8THrrjHmHRK8rP/Rx94opANMGFA3XhfOfCq0Uli8rnkVg7R6Gnqp8t8qUE2xcJdxuoUjXaJ+2XFVUYH1Y7lfuzPoufNk005uGEircLXIWCXG/xuWl1SnzLiGmJzMiisngUX3N0sjoGWRMuKZEK5AynGDiNEFxTqq59GGs9vufO/LZvM6WA7we4ycrl/3VG9RxLVj1CP2C+0pkbW4k3vtpJn+/MKuyKrDczfWBYyVQV9icYbMU8UR3ZwZmLhMYQR9kHgXgjSLWolu57armJ+llnOnmm8I0oJbK2ET4xoHOXROy49Nr1Nwc+lEhQS7Z3VZF3nzQyCvkOgxWGVkQ2h08jZgr8OYl8kQWnLmDIpvHBVRjPTk+YwE8oM3yIsqjdsIp6ul27gFRd2lcxDbjI+WAfa/oOZNskyW9Uyw9mhV0527tzPuKqcDqvNsczjb5ER4BLTNtG1YFLN02CAXcuGOWzAUSOkHj8s7A5PxVdm2L4JtftHt/D+GcPti/1aV/fE1sY0VKsxibVh1PvWYQrTFWxXj9wYEseNffrYtuhsQTc+cDnT+HnS8tTjPNiPlzlQoeRMmJYoj/djVtgq+LfYc1nf8VWFj593aVzoFvQRIAxHMUj/Kg8bkh9NykTUscMK9Hb91pAAo0QYrB6YbklzvZ9ts46P7tSxe7wlpKJ2b9CSPtvZh8JluVuR3nfDG7+vRwvtHhD0twAvO33fv+M9gUMFLkniaqGO1xKKF4Z9l8WzcMIkpoLFIH8RzCtZWIIDJft+dUDBYanfDVdI0jvfQbJ0rBqYVYHPpaR9LbzARiTM+WixiviufmyVFtgRwbQHoYJNb7l8PQLdNqWX0oTzOWMw1rPGzDk/FtgRbu3AzHKDPKjtcD+gQBajGQax2vPYvq9n+xUtYWyAdugqyPS6+f1CVp+V/HFz/jpWhwA5pOdaD7uwymp77gpQvyjYgdld6I93aJ7qDx/vcjHIRI1q1Q24eSNQyKnweirUHIi0Y1pdaYyceD+4tDDR9mAb1Za6Sy5qE7I4cRBFi0bgoC9LKwScIgLC6siboF7SNCsNNs23EZqa0MP5Z4RUce3I43QEb6TzNO3HI0MKcKcYkwUpNZ1r0RvROzGGxusU7MU0FdI/8YU4wPlPOTN7qV93bQvsjwmUzJFJlzCKSSZEfTGAZzgz9vgr6nAskO7taNoogyO8J5J+VBPn7HzoTUiyj9+6bDpf4YiYs/rXvpA47lD8DDkYfsHkZXogogneIZgkzGFhJYYgX1+a6Lq9NV/rOxjxP2kfXBw9geciFL2lOAkzf31nlnHRw50+UQEcKN2HHVTv9sgsYm761U50Oxd/xr1EuRBOpp8LbzGLlXHWmuaJgmcL/HGNZyd1RYn7YBP7AJGIn2yfU+VTJD4MwztnBxQINxy2KaoJFrhTxXDQyK/1L/rroK97Mw+9gNMOFsjWw9+88h0QxqkaQtmrwHfHSv+am4krn2lxyKOqppsRbqK3nEzxmNxHeG9/djuiic8mAXud6ptlckaWzivoeP8ianHWkMZwfA8gheRHJHBB83OosoceNykZm3Je0WGv/If2Xx3AKUiDvhRm9SvsI6+crXZ8X/S9gq6azKi6UKP3lOgu3blvxABmP3IvHfcCP/q8PhNM70nWcZG2E6YKX4ZAzWB+6juxp5B/2kE97Q8N3RWaLIfSuvyAkvKwv6w/zj6WrsGrLdAQFyJrFsUsZ3E1QP6OUh1dbKdsXxYsPgSGAm8HstWE/A1BuUvV2MeGBp5VO1RGnucz1+rPdl+Zoe4ZGVJzmLR+nN0RcL+8IK92T1cu/2ImYLxgzsOp335oljMT+li2cWWQ5jXV6dfImrhIhLLhIVBi8nhpUArJ0oCOkVz7oGm5ZHn/OO3Dew/bq2lFXFhGFmwn9p1VDb3bMfSc12ohdCte0XyenZBIzdB8DxisvyAxe871tcoK5Q/qaKmAwYukowWT/bQmDGmx32kbmqv4C4zYLbpPr3UIELX/u2HzxfxCOfcEudVxZvaoky5BWOtP1L4OkYCPpBqdsZ/ueGGezVq9N24sZJlcvV5O5R+NhqkQehr5tzOzumQME8ozy0TsA1pjMQIuyoXEzU7m4vP4DSRFXZEV47rjc+ADPeddlR2APfk3jWWV7+vCRr2+QnANkPq1OtIMtnxaGxiRGm6z2T4xbMGZ10horhASV+TjGgAz4ydizJvhjzztM9L6G6lzrjJgl+V7LcNb47VSIJXHdvNLD4SDEL6AOgySQhPPqpBl6g0NBIW+p5e8s/m2Tyvq/HI3b6zKc+Qou/PAqYQ2yllL3GpBaXom0HpDYwc+vFetDHpSHLLcqSbN47Pe4DeET7VmPhehAGmUwLvFnoetCwrCktjtA+0prFue3M/lL7fI2vK/JZ/22eQj/U9486seXnY9hs/LIFBLbinLsN5EPYxvQErdkVDpaZn88AmWYiggTH2h4iZr++oZm0Anlu3MvtL9KakehgADkpPxlyRtN82BII/EQyimGbPyyz7btkqkJ8iEoMleMenl5HjnWORthiocpneAIxeoTOQ/bAJn8Nl9NfqEcB+7KYmIDcg0GaExMoEfhmQ5EnfUefGwp+vMWrVB1X6Lq2VLJuqBsEForgL4QodgpGRSHzBWHf0G1yQCKdoOCitMAP/QikCv5R52Z/SWQ7udo3rPjEHLwQHK5D7OXz2ONEqoItLM4d/ocs4taCGIEFcoJCo43XDdl5LVzdOA2iLSXjqJ8AJEf1Q9t9GJl1bO5Ss5pVZYy4li2gWWj0h71Kyzkac6O1CVlHVsQqCTBHrOtBQBVyLdi5ULfxgFmz44Gg8HOEr5GE+AyjrD3O5m+0i+DMF6oUZwsyFI9DBT2ZTRNmZ6eXsttkaGYJ88cjmwSqDcAVfnK2lbI0M6PcLXUjGuvxQNfmjnHeU3+A1hCJ8QKxDD0avvC78ZcecLUO7hN/+nYSg2AyZ6aBXJQTVMfc9WbwrHVszhCB9Bnpg8Mc5r8cdGK7Q8nO8t1AKo/h02NPPfGPPnHFyLJTlC0PsyZW9aGvmR/dOoKxn6pCTRt9TaPmbrUhWhA3EMS/N2MbOpQ3Tsvrve3vv8tCgEO+fP132jCkuLVozIs9Oa0byBgfgOLsFczXW1NsElibDFsHUi/jVkvCNhyb2ANhNz701yh5e3Q4n1e0yb+7cQni+Ha4EogGTIpF0WK4RsvN3peb5T1vqPmiFZ3SNPEAL3Q3Xc4bZjBmeEPL5K4N2XTz45FRfS8Sb5SQJUW+y3NIx5OQecmf4HWkKGNXWdfcAA/3k4M1/itWqeM/WXsZypd+9IbiCk46KucFqZhRV8QNFCO6gA2640ZCl+lJrVLvNYqNJ0b0Ctz6ne39otc4lxtpGQlZSYmXFHntAaeYIJrkvhcdsJtt+rKVVCBLGch+teQRG8Sc3UY8D4ULd0QOLAqfSzB5zvRhUO0WQeM4j5qrw8eqK5xsMKw6XNFSCYgXrAbumXyoGqZYmTHcQXQKMW1aP29sXSw6KWQofvfJhFfheA4p+ytizBlSX78VSrMgpG5m2sNOJ2O4a2XnE3X/DKPTNOsK5oRYRoB+evsXzkAM/NJPenzWpT120wqQ60BGKKGgBik3Vt2/olW3wR49z2qmuY3jmZSRReCoJhopxBhHQasdX9whlVo/Vfvs/PZKmSx8nsUIYFVt6bPRza/fhjsqxZGsmknyC62tHE/+QhDyL3ABe7y4t3Gke6ajNBJ2IejTkk3wTXCoiE6iklmR1pTeETQFi86uXOTi/3YOPwy5Ubug5RXKvGVqLV7QSUSGF/vpdztgcGcn0UBDMRYRUQyam7BZtvqdAcmEt8xPK0Wp4FSKRZcvkvsVL7nYdjSYSmYO/l4FKHTr9ERTg2TMGqsrM70JuhBJ4Ovee1s9XiQ+Lhb/O0gkqtduEkFmTW6/lJOt9EzNPSf6WRbAiLAvA96vEu1YglNaaBXWe0m70x1h+Yf3RJsYj9Z8fpOXN0GMPU00dv9/v3oADnyhuc5gqZuIUejap9EyfgMvL1ROvpX+AfGnARSwieyR1io9E161XhMO/39y78b0bZnhBX6xN9k6O1NsYCVNiR26uKmYZ8Xxi3TIY//e6TTmspY9qCfd6epuLjdLNZcK2032tM+aHue6Q5qsATZRHmW2qI9GqTZkh/jIfqDq3G8X4GdXheo00GRpF+8aMvexgzGOEVZcj+4bio5+xVzOpGILmn60ahE/cec3H99mMxGaHeVQ3wKCcmjn64M7wz9tHAx7hlJA+z5UwhSq3A/GmYMTnJpFcVHez4wAIFodyiNoKshL9mR9op0joWKfXESnvhcCxQYEXMgCP9DQumaQZ3fIUJr4EEVRPXjjwtHTKYP9JAMBvnEP88JrKTHdhreJnT5uQnU5LXJPDuqOyjyuyrZW7fuWi8OSY1iTWJ5rSafXZ+Ez3ANs7W7hgFiKlIgNU3iEBu2DCVMqUG8/KCi+BipwTBpXv9m+GcKg=
*/