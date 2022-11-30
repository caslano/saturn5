//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_15_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_15_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner2_15.hpp
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
*/