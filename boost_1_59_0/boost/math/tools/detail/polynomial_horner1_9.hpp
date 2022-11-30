//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_9_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_9_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((a[8] * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_9.hpp
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
*/