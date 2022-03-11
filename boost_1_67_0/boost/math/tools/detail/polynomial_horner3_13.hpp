//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_13_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_13_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_13.hpp
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
*/