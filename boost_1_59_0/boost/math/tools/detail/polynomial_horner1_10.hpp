//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_10_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_10_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((a[9] * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_10.hpp
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
*/