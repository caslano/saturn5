//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_11_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_11_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_11.hpp
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
*/