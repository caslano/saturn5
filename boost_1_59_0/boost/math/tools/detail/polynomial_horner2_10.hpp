//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_10_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_10_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_10.hpp
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
*/