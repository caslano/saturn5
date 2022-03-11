//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_11_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_11_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[8] * x2 + a[6]);
   t[1] = static_cast<V>(a[7] * x2 + a[5]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[4]);
   t[1] += static_cast<V>(a[3]);
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[9] * x2 + a[7];
   t[1] = a[8] * x2 + a[6];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[5]);
   t[1] += static_cast<V>(a[4]);
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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[10] * x2 + a[8]);
   t[1] = static_cast<V>(a[9] * x2 + a[7]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[6]);
   t[1] += static_cast<V>(a[5]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[4]);
   t[1] += static_cast<V>(a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_11.hpp
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
*/