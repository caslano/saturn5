//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_4_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_4_HPP

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


/* polynomial_horner2_4.hpp
bsIwDL7nKSwmtFMXmLRJQ1Evu7AT1eh2D61LorUJSixQefo5aQe7JLb8/TlRhJEaHbEUyrrO8/WD48WHNpZiW9dVPqD6qnMh108roeQdouTEEg+wx3DGUETbolABT/2YxnPB8/feoqN53uSGATGzSmGITgz/a5XTA04JgD1TAOiCHyBSax1cLBlwHhrviHWgR3ckw/yJBqrxw6BdO+lupFxud/v6o9osk2K1+6zl4XqV69XrGxQ1FFCktW4klV1KQcZGaDVpaLR7JDggRLZLOScAc+ZFeMFvDLYbJ7zuCAOQQUgPDEZHJqODRTSeFkKdM5YFMAQfGt9y6ucX1vvXK3lDyfs3/QJQSwMECgAAAAgALWdKUnsip2NCAQAALgIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMDdVVAUAAbZIJGCdUsFOwzAMvVvqP1hFO26BE9IUCgiG2Gll7YY4htal1dqmaryx/T1OxzaJI7k4zrOf30uimRxnxlEEumoLK2FDh2/b5y6ClzSGWZysIUkXS9Dqgmh1LIYrfKorannsqpxAZ0MiuKN+R30EBXdSfMpQt6ahgRjjx2SN2662JseiqklAdUS1T9Hv78Lafikv8eb6dsJ7DiPIDRtAWWyHgOiI
*/