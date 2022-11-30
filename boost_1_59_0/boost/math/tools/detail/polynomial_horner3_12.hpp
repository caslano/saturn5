//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_12_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_12_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_12.hpp
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
*/