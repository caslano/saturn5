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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
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