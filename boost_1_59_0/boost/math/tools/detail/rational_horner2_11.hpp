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


}}}} // namespaces

#endif // include guard


/* rational_horner2_11.hpp
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
*/