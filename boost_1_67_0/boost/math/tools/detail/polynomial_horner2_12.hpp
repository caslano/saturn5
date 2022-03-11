//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_12_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_12_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_12.hpp
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
*/