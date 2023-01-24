//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
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
   return static_cast<V>((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_6.hpp
fKydeeOu+A2Yro+CqRhgouC23sGCPnqnOofQtIjfpJkWEXZFkVsRiLdG2RXTR+gkSunlJCnwewyDQrUbVn2r2A1kMuiWz3W5Ae5HTho1m0B/vziDeMLjGsQuPP0bykOH6RZazMGrxtG2W01ikEVrzR8+NNfThrSwxI6RYBeaHUMuE3efifd+ZyidHkjoT5EsxdntGHvO5kCHXEI7Hn3ltyLZpfdYUNeFyB5gkN6WrXNKkZMvNQaWyC3GlXmBWQa1O4mydedik5Dzw4pncGdDvN3fHwFRsHDvNwwLJWqMCn5xq76CFYsxvnXLflDJVrchNsqGCxjL0m5ulcXUWoOAvDB3Ci2YioHb098BQ5wtQBmH/VVRggazs26idKKWrmvEK07p8tKnQbtAktKtlEtrlAtP1aXex+kN7rFyPRd6xkJh4B6ny0sl13PKEg2Fonue2BhtxF9H9oh3LkrqnlByUwivz13n8Naaweg/zI3+OjT6D5/N6Jeb32AV9UapVVlBNver8LxVqM3fBe9cW0MF57LlONo1Jrm2AvSWirw4vjKV3xvItN/VyhIcHoSCkgZiewPi9E6DAdxpcIr1rTdudsGXtLHqI7Jp1tC1mhLUKU3KDB3vzuJQ91aUu94qqd+YJtehv2LFJ6J/xlGL72raAOjaxEACuWsdlqFur6HLUAOPk4Hln/F15MYz/4z/Ru1Fc5lYTRZtJ9pc3PqV
*/