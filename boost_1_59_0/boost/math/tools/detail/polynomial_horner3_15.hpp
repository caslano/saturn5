//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_15_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_15_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_15.hpp
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
*/