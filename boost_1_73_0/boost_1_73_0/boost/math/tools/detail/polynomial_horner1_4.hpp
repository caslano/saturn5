//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
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


/* polynomial_horner1_4.hpp
j8c4V5uNqAvP+q8eR3UUhMEUgwylWnFnmgtdmJ2xFRzz47KShI72S+9/XG8Ij1TpAtBdDujf3GWUe982UonCDoh2K5db1Ssw6w7oRseDSxJmq60p3JE42w7udL4tSVflHp2lKEpDGi1Dx4Zr0eIfohp77VqZHsTPHdZSNFoZlSs5BGecl3uYKwZj1ZoI37jCYGG9D25XdnPbzq2WvL8czdPJ7IHBbZ5TY8Pn/PztJFx/ZjDaNbYjEQ7CMMjt96redtPwviYt0tEcRa3q/UZtWwbJbZq6qf1KO7FpJF3Y3tno4z3rTiGD7HcywgnrjiP6Of61mGRuSk8mxb6K9+/ogTfmx9bw06/lL1BLAwQKAAAACAAtZ0pSRl8M9uUBAACSBAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEwNTZVVAUAAbZIJGDNVFFr2zAQfhf4PxwteSnLZLupWY0IlK60WbslNF5fxh5U+TybOpaRlIT8+51lp2np9rDBYAZLtnz67rvvPlk4tE5Ji1MmqqbQND3hbqtNbqfsJssWfoDrq4wVuq71ttZKuko3bLbYJEzwQ7TgPQA7ZsewRLNBM7ZVjkwYbOsdBeTSyR6VR+8jOA1jmN+C3VpVa4sBuxuwUyida1PO
*/