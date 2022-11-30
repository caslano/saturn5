//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_8_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_8_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_8.hpp
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
*/