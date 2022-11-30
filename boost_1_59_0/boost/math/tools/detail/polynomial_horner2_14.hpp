//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_14_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_14_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_14.hpp
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
*/