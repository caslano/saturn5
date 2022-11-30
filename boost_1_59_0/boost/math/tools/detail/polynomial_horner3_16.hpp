//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_16_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_16_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[14] * x2 + a[12]);
   t[1] = static_cast<V>(a[13] * x2 + a[11]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[10]);
   t[1] += static_cast<V>(a[9]);
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[15] * x2 + a[13];
   t[1] = a[14] * x2 + a[12];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[11]);
   t[1] += static_cast<V>(a[10]);
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


/* polynomial_horner3_16.hpp
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
*/