//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
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
   V x2 = x * x;
   return static_cast<V>((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((((a[16] * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((((a[17] * x2 + a[15]) * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((((a[16] * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 19>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((((a[18] * x2 + a[16]) * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((((a[17] * x2 + a[15]) * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 20>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((((((a[19] * x2 + a[17]) * x2 + a[15]) * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((((((a[18] * x2 + a[16]) * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_20.hpp
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
*/