//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_14.hpp
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
*/