//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_18_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_18_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[17] * x2 + a[15];
   t[1] = a[16] * x2 + a[14];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[13]);
   t[1] += static_cast<V>(a[12]);
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


/* polynomial_horner3_18.hpp
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
*/