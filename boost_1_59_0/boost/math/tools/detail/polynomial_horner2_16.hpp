//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_16.hpp
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
*/