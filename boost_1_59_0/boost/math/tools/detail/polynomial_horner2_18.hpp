//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_18.hpp
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
*/