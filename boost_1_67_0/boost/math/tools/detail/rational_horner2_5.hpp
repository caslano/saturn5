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
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
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