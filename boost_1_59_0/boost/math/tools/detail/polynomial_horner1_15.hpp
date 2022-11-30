//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_15_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_15_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_15.hpp
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
*/