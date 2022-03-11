//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_14_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_14_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_14.hpp
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
*/