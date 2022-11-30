//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_13_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_13_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_13.hpp
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
*/