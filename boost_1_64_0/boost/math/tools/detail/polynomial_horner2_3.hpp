//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
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


/* polynomial_horner2_3.hpp
q6VDcE542848NFIQbNUOhL9znUNXVgnZCeScKUMqAsaWUcUowzJ0ob4yQi/7u3aE6a6TZB5/Fjgg2wj0Xq/0h7mcyCOA8/mwNhpabVdvyfNE7cv8ZBnwNjWJ1p4XGXegDfRbNWxnZ6lJaY7X9z6z2dgnhU+annU7KfuMl5wZ2bETIIsqDtia/FPiO1lhUiNBzi+sXdFdhvHjDsvsydperLATIMtIism04uXUAnjLPUE7n1xbS/9seN6433fS1htAqgFteWo9yF/jIp874np6rCu0bs/EZ0YQJoXqH281ktAukIbH2rsxnw0I7IZnK9Vi9N9w3cxIHT9lojWWYxXK71rkwjG+KiKDo9+k/40lEOTDKojFzaBCmaMhEZUjlVII20vlTbpGy1zaf3ipjwGgzgzMC5Nwg1H/D/cOonRxdb4Zcoh24f0deG4Rn06H03Kx7II+6iAvCbil1/1dMm1yhsSQ4MAy0KLOJDpnka3cOqeHggOSeK6kpnVduEEGr0zwXrfOfmXdNJNvf1rfbXP38opCaIyJwW0i7J58OCe+IEnI1CA5wMOprMyrNg==
*/