//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_16_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_16_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / (((((((b[14] * x2 + b[12]) * x2 + b[10]) * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + ((((((b[13] * x2 + b[11]) * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z2 + a[12]) * z2 + a[14] + ((((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) * z2 + a[13]) * z) / (((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z2 + b[12]) * z2 + b[14] + ((((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]) * z2 + b[13]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / ((((((((b[15] * x2 + b[13]) * x2 + b[11]) * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + ((((((b[14] * x2 + b[12]) * x2 + b[10]) * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z2 + a[12]) * z2 + a[14]) * z + ((((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) * z2 + a[13]) * z2 + a[15]) / ((((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z2 + b[12]) * z2 + b[14]) * z + ((((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]) * z2 + b[13]) * z2 + b[15]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_16.hpp
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
*/