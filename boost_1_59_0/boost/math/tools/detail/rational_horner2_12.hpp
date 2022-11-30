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


}}}} // namespaces

#endif // include guard


/* rational_horner2_12.hpp
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
*/