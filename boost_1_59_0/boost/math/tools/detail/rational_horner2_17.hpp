//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_17_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_17_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((((((a[16] * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / ((((((((b[16] * x2 + b[14]) * x2 + b[12]) * x2 + b[10]) * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + (((((((b[15] * x2 + b[13]) * x2 + b[11]) * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z2 + a[12]) * z2 + a[14]) * z2 + a[16] + (((((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) * z2 + a[13]) * z2 + a[15]) * z) / ((((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z2 + b[12]) * z2 + b[14]) * z2 + b[16] + (((((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]) * z2 + b[13]) * z2 + b[15]) * z));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_17.hpp
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
*/