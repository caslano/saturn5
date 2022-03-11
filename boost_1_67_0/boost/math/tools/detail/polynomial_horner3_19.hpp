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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_19.hpp
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
*/