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
inline V evaluate_polynomial_c_imp(const T*, const V&, const std::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const std::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_15.hpp
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
*/