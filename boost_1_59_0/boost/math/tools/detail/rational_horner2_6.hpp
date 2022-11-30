//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_6_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_6_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner2_6.hpp
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
*/