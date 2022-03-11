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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_12.hpp
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
*/