//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_12_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_12_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((a[10] * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((a[11] * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_12.hpp
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
*/