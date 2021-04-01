//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_5_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_5_HPP

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
   return static_cast<V>((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_5.hpp
GUUVdIBo5b3BJL/k4gHCTMC0M+Cl9hrotG+RPQn9PKu5CFx9o+gSOM7srPnyNrd8RnkTi34GnN5CyenT8wTsIx+4KeXTustg2W7nTjvtxtNzjHHVVe6Jql+u2s1RF+ZW4macli2WV+YaGlubAo9U8p1uPyBUGj7p9TM54VAlAEZnFK7z6YihIm1DITIX8FfckEkTrASkeYvCO+LqK2mXNRFg2ooeuJoOTpm7+gb0QRbYpmBSkKVjO/uevH8eSsuSeRhY9ztHVgmmY1sbIfnGgut/uUl2XE450WBVJXTjJNEw4BuMQw8UEwiiAigpt7I1R07tXVJZ+i3o9q7gdhZESjb7H7Luj6IR8WtDqEnLE8bl7h2mylCX/TOYUzkiQ93U7m8ak0gPG0uHjT3eG3ddzKBiNdgT7/5JwezPH5gIolCeqbcq54dl+6MZwBOiZMy/ycmq/5AgEY7UO16XDVzD/qKIG+dZp4PTqkM+ma0YhboeKt2pqgJabMOtKaSFTnkD/m0XSj0o4queUCXUwM8UOP1G/C+kh5AwBmR2TDQLTN1iQjBcUlNh9v2hmw==
*/