//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[7] * x2 + a[5];
   t[1] = a[6] * x2 + a[4];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[3]);
   t[1] += static_cast<V>(a[2]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[8] * x2 + a[6]);
   t[1] = static_cast<V>(a[7] * x2 + a[5]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[4]);
   t[1] += static_cast<V>(a[3]);
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


/* polynomial_horner3_9.hpp
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
*/