//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_3_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_3_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
}


}}}} // namespaces

#endif // include guard


/* rational_horner3_3.hpp
dbVF1pCoX9vWnqYsqAMxsQSMTYmCo3z6cKCAjllQiVJnqV17WtdsahdkS1LniXwVYFO2hsnNUInccjdWlHSjEogREnVtC1+ypOMY6x7d1X0LrKOJX5NbobZdjMfD3C52azbK5EJ46mw8tzYzisW+UDPNIZ4KmRKDib7hRxMSKWR1NcMmOZsCZ+pPSSpcD+iCrGdABl4xxGQyUg3SydSuF+1zo8YWSlRux3DjtZ1wtmkl3AruRXLTpucRUquv9IEp9jxVHUbsyrN5Y0clnThrcsPlUjgAQ8qeNuUWK7OxM6T5ZpPHMFo6COZg1az+DTGsueMdVappsD6pCpA35FSI2B6w16daByNeCJTEcVTtPyC8mYNXVImjbyjJoYN4W0lolCReGfaVodCOYjwgp/LmFW0mFQ/EUy8Ugf43DyzfjNDOYIzJflTs/46GsfPuHvzkqEKyL4SJwpcKRsMW90wcxVkWYORL/YWE9hMQ6bqM4S/cS805ShOQBhBMcg/IxExLaNK2QZJfK7AHpB1HOYjyZ6NMoOM52OeYl4fB/6C2B7dNkH+XdPW5XmegvYePFdwr6oBlAMd8I5JB5ObeK0pQOPOAPCCNf+7DAIXjzfw4+v5IvOCPKDjDvz/e2B//CWu8/+LVtjEfCmiSxitg
*/