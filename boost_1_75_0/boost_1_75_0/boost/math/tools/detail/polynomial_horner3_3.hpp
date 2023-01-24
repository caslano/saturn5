//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_3_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_3_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_3.hpp
cI2BG24wcFCPeDiqp5UKheZSjwIeH36G+LuGu8W2eP99u2UbApyyZp4B/3MF/N8t4F/8xuDXsBs9K59/0VFcYrH+jcDlb+8nQI+MQCV1RAZ25XmVbHB3jiUz9D31eFw3p8hfegDung+IJ9/O9GArNDkUJRdQ418+sFtMvB+y+WuzjAg/IjdwNfF01Qi0h9+zm3IDV8Pyr2zAfKOWyDIpvr6aZJVrq0iPiFGngXosRtWbd1sbcj9oqIh/8ineD/TjGuXpNBy1qF2G2tlGtwJVRtU9bHQpFNC7NzFWY03wKwtnNW9DLkDZO9uUV9ipWRA39P22XMeZ2nh6GBBr4yrBYp932r+D8bDvJiMscJnWqzHcKz1377KcUGx2bndjxCF9dSudUyTFOI0GOqhV9hed9MufYoyHhaHY4o2B+LSN2KOKTjtpxvjADbj8+/ADvPMXb8Weu+redCAGWmuAhDc+pS9DxPb37NqrkEzrhRCTqUPMz9+zkzVJjbc+l4w6pufVKD9aSYbLkzIdZCzypIXNBTaSLvWvHB4rzmmslL9NYxQxk2xWfkkPg7EXSE0enzgfZ7hGqYeNEYpvYhvmdDRFi3tWPscx3Cia60Xw9c5aqtkaiG2YT8aAN9cE5Kw8w9WBaNF0ByuppTQLkAGorYZXKuauR3vS4vj4YeiCiyGnyNAIhSJGYLgaMRVKaUMGSdWQQK23s/2JQni8TRne
*/