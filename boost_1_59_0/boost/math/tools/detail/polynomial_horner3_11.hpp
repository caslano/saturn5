//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_11_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_11_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_11.hpp
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
*/