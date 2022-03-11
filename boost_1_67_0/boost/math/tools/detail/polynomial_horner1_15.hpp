//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_15_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_15_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_15.hpp
+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
*/