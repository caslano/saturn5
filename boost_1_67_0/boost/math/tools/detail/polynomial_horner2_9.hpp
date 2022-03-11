//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
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
   return static_cast<V>((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_9.hpp
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
*/