//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_14_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_14_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((a[13] * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_14.hpp
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
*/