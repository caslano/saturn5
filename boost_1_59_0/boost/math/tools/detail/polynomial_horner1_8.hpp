//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_8_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_8_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const std::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const std::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((a[7] * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_8.hpp
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
*/