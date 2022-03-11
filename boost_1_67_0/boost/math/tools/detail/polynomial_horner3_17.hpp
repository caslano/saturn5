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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
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