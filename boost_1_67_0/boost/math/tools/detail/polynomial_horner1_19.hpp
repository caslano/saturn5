//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_19_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_19_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_19.hpp
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
*/