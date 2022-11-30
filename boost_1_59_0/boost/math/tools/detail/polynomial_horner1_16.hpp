//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_16_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_16_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((((a[14] * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((((a[15] * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_16.hpp
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
*/