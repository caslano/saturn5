//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_17.hpp
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
*/