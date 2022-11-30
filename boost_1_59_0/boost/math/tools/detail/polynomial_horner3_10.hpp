//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[9] * x2 + a[7];
   t[1] = a[8] * x2 + a[6];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[5]);
   t[1] += static_cast<V>(a[4]);
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


/* polynomial_horner3_10.hpp
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
*/