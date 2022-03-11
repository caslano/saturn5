//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((((a[16] * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_17.hpp
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
*/