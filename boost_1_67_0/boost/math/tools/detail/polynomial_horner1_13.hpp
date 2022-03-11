//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
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
   return static_cast<V>((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((a[7] * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((a[8] * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((a[9] * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((a[10] * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((a[11] * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((a[12] * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_13.hpp
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
*/