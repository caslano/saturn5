//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_17_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_17_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[16] * x2 + a[14]);
   t[1] = static_cast<V>(a[15] * x2 + a[13]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[12]);
   t[1] += static_cast<V>(a[11]);
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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_17.hpp
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
*/