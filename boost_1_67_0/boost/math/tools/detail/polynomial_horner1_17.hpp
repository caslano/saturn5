//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_17_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_17_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((((((a[16] * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_17.hpp
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
*/