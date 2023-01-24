//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
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
   V t[2];
   t[0] = static_cast<V>(a[4] * x2 + a[2]);
   t[1] = static_cast<V>(a[3] * x2 + a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[5] * x2 + a[3];
   t[1] = a[4] * x2 + a[2];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_6.hpp
oUPaR1qD8j7lCTHLW2by77MzxV6ZJniOiarTxHOQU1E+x/TFaRUxoIkHUeafwU1BPIUgHWGqar6vcxlZgmERHTaYjY4QBZYsuxlB4KKZZ13fhjPO/+36fsLr++GvxPquu+Ps63stLmN4HB2LxjJjLOOURT39K31RH0hdVPMc/+c1PX3wP6/p34L/xZo23sBr+Y5Ai6/fbNPj2Ds1udH0Htk6bvtGn92g/D45Sy5OY6voyEbp/Ei9L77C2kuakl0HuP/1JP9m54fKejrACeWVsHi8nuXfCsZ8ZXWc3Iry73utjLf6wSA2WswauUOUguPvM1n6DS3dAS2RkOZZScakHScj/VlqNgxekJ9VEsAWQYIUchgw1vdLoZAj2+xBWtzWc0UxEr2h0KaRasWHvdtho/YG7bCXbzHpATft1/WAMyiKrqRH0T3vlymKQGy4VWu41dTw8laqEx/2ogoEfhklSCodw2pkMHldLSUtoKYTvJvuDAPp7sZAlGvjDgr+K1q9CbOa9QEqZA1GrWZVIUDvPrHQGtTWa1Bbr0MtLcL77cZyE+Rp7/2o0qfzZxCOnPSBGvx+GRCWp3Sq3FxotjzFaDdw7vSZDtCq5N+oHwC7pjL4Nk0V1j/KNIZjk291ILbMjCB+/ZUJQXwOCKKTEiUSgminEy02rV55ZSyfuR7CEsNgtT79GaEFRVk6G3X8bm0Gq8iMTRE8QEU7m7F9
*/