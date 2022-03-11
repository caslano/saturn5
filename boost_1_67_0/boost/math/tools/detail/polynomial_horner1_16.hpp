//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_16_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_16_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((a[13] * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((((a[14] * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((((a[15] * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_16.hpp
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
*/