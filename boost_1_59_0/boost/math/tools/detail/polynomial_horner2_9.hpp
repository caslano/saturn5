//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_9_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_9_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_9.hpp
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
*/