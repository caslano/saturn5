//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_20_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_20_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((((((a[17] * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 19>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((((((((a[18] * x + a[17]) * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 20>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((((((((a[19] * x + a[18]) * x + a[17]) * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_20.hpp
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
*/