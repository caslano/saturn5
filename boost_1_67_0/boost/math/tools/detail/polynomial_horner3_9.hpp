//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_9_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_9_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_9.hpp
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
*/