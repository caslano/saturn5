//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[10] * x2 + a[8]);
   t[1] = static_cast<V>(a[9] * x2 + a[7]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[6]);
   t[1] += static_cast<V>(a[5]);
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[11] * x2 + a[9];
   t[1] = a[10] * x2 + a[8];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[7]);
   t[1] += static_cast<V>(a[6]);
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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[12] * x2 + a[10]);
   t[1] = static_cast<V>(a[11] * x2 + a[9]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[8]);
   t[1] += static_cast<V>(a[7]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[6]);
   t[1] += static_cast<V>(a[5]);
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


/* polynomial_horner3_13.hpp
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
*/