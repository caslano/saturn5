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
fKSWq/dONf8j+XsSHSf3OuF87yG5fW046lR3wloV/8PWyfm8gmyGjO2qnC/vcNIPSXtl/dCQ4yTQ8es6tSy9tzvJYdUOWeYnP1XfX/2QmrbOIbUs+Ygvlq1TnznwkXr8JdKNMz9Vv7sH2eRHDqqymn5Y/a6o6MzfSLf8klnMhoXm50x7YZYrhvSRu5itVYXMcynNw3WW+uGCj6V2eirz4q2ankq9eFN0pr0BXj5phQExYo4gnjGLn5ukeGOkmG0SsxXfePKGqkWStoOfTlPoVyT5B5MDmCNW4z6IVelmFJJhX4ZWI2Q016BR5wLFF36S4gBHR6AzwjUm8Y5ZLBLE6+QVKf0Em//KUb4ayXBjoZa6iY0RbIbBELsavMXs8sU4QaweCc6odLhaPB9Jev/JMPwRzKYPrXQW7AvpTGGbjFk6TUoQrBxPJSnYg+BA8AVdPS4ZGpO8FmplhwC62H0STGql0Ekt40goH2RVEETt9Z1osFz+9B1BNAeYxEsx4hlB/AzK35AOn0fBWvj+kJ8zsNeavaREkgobwIR0CPjXQAbN4jlaqJWvaDXi8cxsSzMhXA9ucXrJMJNeo9tGpV/TgO+u1c86Uge1I4+mx3iBjI8KI0vHGQgRxFkBAuzfdgmGaFKEjB4kpw1Soohwu78Awl2SyeT4PBFu3Rdk4YryxW6CWB+yT0oYrKGZ7S/PKZ4nAtVnzCcChT3qJMOJ
*/