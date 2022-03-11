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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 19>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 20>*) BOOST_MATH_NOEXCEPT(V)
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