//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_14_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_14_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / (((((((b[13] * x2 + b[11]) * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + (((((b[12] * x2 + b[10]) * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z2 + a[12]) * z + (((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) * z2 + a[13]) / (((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z2 + b[12]) * z + (((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]) * z2 + b[13]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_14.hpp
+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
*/