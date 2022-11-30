//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_7_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_7_HPP

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
   V t[2];
   t[0] = static_cast<V>(a[4] * x2 + a[2]);
   t[1] = static_cast<V>(a[3] * x2 + a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[5] * x2 + a[3];
   t[1] = a[4] * x2 + a[2];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[6] * x2 + a[4]);
   t[1] = static_cast<V>(a[5] * x2 + a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_7.hpp
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
*/