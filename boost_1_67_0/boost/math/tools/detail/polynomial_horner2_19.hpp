//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((((a[17] * x2 + a[15]) * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((((a[16] * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 19>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((((a[18] * x2 + a[16]) * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((((a[17] * x2 + a[15]) * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_19.hpp
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
*/