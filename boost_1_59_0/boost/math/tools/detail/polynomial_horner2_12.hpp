//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_12_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_12_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_12.hpp
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
*/