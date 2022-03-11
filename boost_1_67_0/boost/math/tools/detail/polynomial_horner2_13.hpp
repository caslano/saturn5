//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_13.hpp
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
*/