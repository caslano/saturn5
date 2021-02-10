//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_6_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_6_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_6.hpp
1vvTEwaZ4mucHCYMnbQlBLdvgiSB2DdGsgtN3Xwk7efgJII00KBA+YI5pYtDPsiEXq9pyvQzyuFbpZd0W3VrR8mXBJyINI5Pp1Twfp6euurz2cMi9t5oCsO7TU0FUxglSUTVrVQtDkn3PmtWyIqGSsW+Dl8lH07YoiRNokFO90lDDWE5+BO+PesDwg3uOnJx7v7BvUTfVKs+sa6UonSr1mDRViCLN4EKMTfAQ3K6SC4saHUJv3GrIBRzbtZwOttAxZslTdB/NeTmCuiR0K++loJXsLidQ83FCu05GO0CrH89NHLQBUhXWdFOwzpJW/SQjOtDKiqMsCQNJhyiuitJ70oH0bWWFOYX5HEtfGBsSo/tzMBVkiSwgbPZWcpmRzva0Y52tKMd7b83wiaHH44TdzjoQfEJG1n0AeJ4YT2LbNGmJIR4RlQwNKW2BF4vPpZS1I22WuiK+ENhV0lF/NWjIery9BgIbofcAzbVhijuHegN2C9CzOhmSWqIldumik+f7h4e72c/B+xGCKxp+yK+GLB/geB7+r4aj8ZvYZ3XdUU85ag13kRd10XEeeuIaqESOsfc0fkrVKQB7dpzw9r3HB/+oPwBUEsDBAoAAAAIAC1nSlKxiSeVZgMAAKkJAAAfAAkAY3VybC1tYXN0
*/