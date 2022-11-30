//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_19_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_19_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_19.hpp
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
*/