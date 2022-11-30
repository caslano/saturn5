//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_14_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_14_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[13] * x2 + a[11];
   t[1] = a[12] * x2 + a[10];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[9]);
   t[1] += static_cast<V>(a[8]);
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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_14.hpp
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
*/