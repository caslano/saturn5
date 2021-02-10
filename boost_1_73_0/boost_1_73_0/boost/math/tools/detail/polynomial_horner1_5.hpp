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
v6VpNIrPzun6no66jclifp/xldY8Cs+SMAzjgH2UDlPIyvU7OI3g07qGOAw/QDRJJ+dpGML15yxgl7ppUPXoQ7qAKPeUPLP4BTUCeE3t73M86nw3JIqHTKpE9fRfCfGPCx8KFnxwgrfIZV1h4waLKP9CIQVKtzZIfqpab7DDgrDeVFPWieKH8RCz/wCikSvslYXer2AwrwyRg8LoFZBrJ+B0NyewrVwJVukWaSfvt4JQerWSTd6nIe1HN/NlNlv0snvVt8ilobuuuSMM61sA4zti8ryZHoeSfLEPaKpiB50YIAuHBlyJ0B0+KKWFR8QGjmyp3RETGx9LEK3RTitdTxmdP/hN2n3rqInauhTe0A3YV9JnfPGD2FB71qbmo4er++Vs/iVgF0phS8sn/KTrmc/z0lS/hk/2+MmfJhD8UJTgz5Xyw2/oJ1BLAwQKAAAACAAtZ0pSJaP41nEBAABGAgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEwNTdVVAUAAbZIJGBtkstOwzAQRfeW8g+joi6LAfUBlYl4BdFVQxKKYOcmE2qR2JVtWsLXM0kjumEV+3qu7xlPhEfnc+kwZELp0tDnE5u9sYUL2WMWsyhOVyyJsoQlUn8gE/x4LvjBwk4g
*/