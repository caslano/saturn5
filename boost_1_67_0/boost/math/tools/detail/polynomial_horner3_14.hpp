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
inline V evaluate_polynomial_c_imp(const T*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
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