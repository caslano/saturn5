//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_11_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_11_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_11.hpp
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
*/