//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_16.hpp
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
*/