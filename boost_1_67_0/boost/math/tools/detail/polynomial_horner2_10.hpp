//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_10_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_10_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_10.hpp
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
*/