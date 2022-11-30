//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_13_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_13_HPP

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
      return static_cast<V>(((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x) / ((b[4] * x2 + b[2]) * x2 + b[0] + (b[3] * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((a[0] * z2 + a[2]) * z2 + a[4] + (a[1] * z2 + a[3]) * z) / ((b[0] * z2 + b[2]) * z2 + b[4] + (b[1] * z2 + b[3]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]) / (((b[5] * x2 + b[3]) * x2 + b[1]) * x + (b[4] * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z + (a[1] * z2 + a[3]) * z2 + a[5]) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z + (b[1] * z2 + b[3]) * z2 + b[5]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x) / (((b[6] * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + ((b[5] * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6] + ((a[1] * z2 + a[3]) * z2 + a[5]) * z) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6] + ((b[1] * z2 + b[3]) * z2 + b[5]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / ((((b[7] * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + ((b[6] * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z + ((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) / ((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z + ((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / ((((b[8] * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + (((b[7] * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8] + (((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z) / ((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8] + (((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / (((((b[9] * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + (((b[8] * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z + (((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) / (((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z + (((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / (((((b[10] * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + ((((b[9] * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10] + ((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z) / (((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10] + ((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / ((((((b[11] * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + ((((b[10] * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z + ((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) / ((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z + ((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / ((((((b[12] * x2 + b[10]) * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + (((((b[11] * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z2 + a[12] + (((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) * z) / ((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z2 + b[12] + (((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]) * z));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_13.hpp
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
*/