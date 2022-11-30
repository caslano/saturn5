//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_17_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_17_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((((((a[16] * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_17.hpp
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
*/