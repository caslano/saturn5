//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_9_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_9_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner2_9.hpp
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
*/