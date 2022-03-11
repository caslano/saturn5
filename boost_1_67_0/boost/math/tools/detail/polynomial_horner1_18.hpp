//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_18_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_18_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_18.hpp
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
*/