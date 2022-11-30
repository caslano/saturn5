//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_13_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_13_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((a[12] * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_13.hpp
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
*/