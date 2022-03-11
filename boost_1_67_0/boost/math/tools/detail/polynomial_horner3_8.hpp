//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_8_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_8_HPP

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
   V t[2];
   t[0] = static_cast<V>(a[4] * x2 + a[2]);
   t[1] = static_cast<V>(a[3] * x2 + a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[5] * x2 + a[3];
   t[1] = a[4] * x2 + a[2];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[6] * x2 + a[4]);
   t[1] = static_cast<V>(a[5] * x2 + a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[7] * x2 + a[5];
   t[1] = a[6] * x2 + a[4];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[3]);
   t[1] += static_cast<V>(a[2]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_8.hpp
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
*/