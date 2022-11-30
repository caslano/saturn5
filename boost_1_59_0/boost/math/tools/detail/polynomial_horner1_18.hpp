//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_18_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_18_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((((((a[17] * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_18.hpp
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
*/