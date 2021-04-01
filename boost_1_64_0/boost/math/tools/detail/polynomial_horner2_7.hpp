//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_7_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_7_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_7.hpp
64d7vWUSuMY/0WyKR110dnPw/u1/NXsS/UFeNc9dB32obfW++kVI1U9GWZTf34o5Ju9LDLkAqDzN063Op6P713/oJR609+IuHIdNs5l4p1aNh8gBb15q/JDEOWWS82XtyrqWM0ZEPRF8jo7bLQfoDktRuozlMwCUJbhgCmVerZarvjEt0y675p+n/I0fmAVGpIjG3Bhcf5x+OIV3YkCdV0eaHJoaJ4EH2bxcZA2tR74ApO3MgY/GRX1KhZAoyTicrhIBBYDJ4jL+A4fteg/Avb70CADC3f5uLZLzEzNUnTHSqE7KgHveWJJvkPYXPMh68b5YXnKwDnv2/lwMvrdi55JOx5qje66Qu2oKLXdlgJU9DEC3aDk742LaoqCGTh/a3ypN8k0THxHuA8niSSW0NEqtBTeQFJDDTUoEqFswomOjQYkQR844SDAFl02neGINx98DXGz0uMM6Nq7LbpDHBHyw6Cix7TH4oWLbLmU+nlTLh1XJF7XZGEbbPt9FhEwjHudVz94riKWI1/jns8PuxTWTnEmDjLvAFgBBj1zkULDoPDhXNVmFOwM92Q==
*/