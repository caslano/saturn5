//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_20_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_20_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 20>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((((((((a[19] * x + a[18]) * x + a[17]) * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_20.hpp
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
*/