//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_7_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_7_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_7.hpp
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
*/