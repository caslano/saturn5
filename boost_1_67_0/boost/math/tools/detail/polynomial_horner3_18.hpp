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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
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