//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_15.hpp
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
*/