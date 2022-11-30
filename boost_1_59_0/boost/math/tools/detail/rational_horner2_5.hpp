//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_5_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_5_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner2_5.hpp
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
*/