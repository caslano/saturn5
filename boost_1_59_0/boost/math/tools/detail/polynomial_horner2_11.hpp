//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_11_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_11_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_11.hpp
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
*/