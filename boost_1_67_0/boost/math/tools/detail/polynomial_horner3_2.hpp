//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_2_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_2_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_2.hpp
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
*/