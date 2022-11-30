//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_19_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_19_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 19>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((((((((a[18] * x + a[17]) * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_19.hpp
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
*/