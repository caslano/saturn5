//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_4_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_4_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner2_4.hpp
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
*/