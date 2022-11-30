//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_20_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_20_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 19>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[18] * x2 + a[16]);
   t[1] = static_cast<V>(a[17] * x2 + a[15]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[14]);
   t[1] += static_cast<V>(a[13]);
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 20>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[19] * x2 + a[17];
   t[1] = a[18] * x2 + a[16];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[15]);
   t[1] += static_cast<V>(a[14]);
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


/* polynomial_horner3_20.hpp
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
*/