//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
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


/* polynomial_horner3_3.hpp
Sh+A+k1nkz8RpEFZhHIWO/nI4+2+NziumvycFVESlp7gj8EFgBXQcTESJfNxWi5lUWWlk6ekG9j+Lb5mynCW+2Hq8yhTMtI9EI3n+yTvaZEnZVJ4ddrgPV5MmBHPz2naUh7FXh7i0OBVZWin7U+mTMG8MAjiMuZMVdPEDNYz9KnHiD61r27HesnU6lVIr0+dFPiBGoeSmBPrz+cgQ+7dOIIDaWkVlf/4PKh1AE99S+RHY5/lX+LnU8OAwpRxRG2wqGYNRmE8QzesuXO9WMn7bJq3tqGJJxOq+xKcz2/iUZ95N5o5q93leq7QvNmRJp62+2ve9k19vG5THm428TBePab8ZrPmSZrwf2WEMzpKcZp85H2a8OzosMzesdXidWUTN9893WZz6sEV3+u7YyMOlU3O7q3stHjqqXDTp+KdFAcuLXY79TUJI4x8D+DQmnQYtVpj+nG+UXOw+Mh5kbsgBjltG9jKPoJBKWjMvxti9Dwe/GFg0JXMe88HEJNbjt1FQ3biXga+vErui1y9N2Cw52R0Nhn5/dXe9X0aOLgthndPGnmwPYacM/dt4sCGOHJGDjVxYKsMOTcJR1LaHTgbiT6z70c5mDXM25X7Uw7NGsb3V8IjWdOcaw+gHEw2cl57uJ9jnylae6DBgTPZj6+j0mEcepCNqyBwjPwa1IfWG6BRKDdjqk3jO2T8H5vqNb4aUeE+OCxPeoF29d2e6xZPHaIqlT3jHJ3v84QHgVut2x+IPd8fNueiY2XkZ0EcuezkJIy2DfP9GOG7PveiihesdkuB9KEOzEs/FX1tD/HBCbnCx+P2G/rXZ3pjRXtV6Ebn5hY1dmUDxc4v4ZmWqyMKo+ff/7QJvusS7Cms5ppzFHC7JhA/sA1wuwYw3jPbNQ6VjvdGd5DvJB+/2kUwyIced/luhTV4vTTPG1DegtzG1/jYXsBLWpBGOZ+4C8GhMPE93bsiRs85gM8GismpB30N303ipMBbJIz47pJDC13jSwckTgsd03cPxOVUg/V1L4rZ+Z49SHAofF2X7D4agyEJ28h94bvq20mZWHcsdh2ycRDHc26f7se7HaU+gYtgeRZE7/2epe+qcScpcy9iZmVB3zL77oQp80ieFkHOK850Pu33thiNIysrl3tehgI6Dtyv52etvcSCx3nEc2ZN7Xba2qbc8coruBfEERNt20za0IpK2xJNGy/jNE95AQK6Tu38vOgsPffshzxzS7VYIcsCfY7gqpUfHsRZFjsFs6Z2Oz8fPkvXLTysYKcQJ/yewKJK25dMPmdJGXhVUVSM9k66/vjeWeovsAqDCJbuTW1A2wjOWraJME44+Krq645oA1ZlcZPIeiKReRklHmd93ZTut45O032wKkycKkt8ZnffWgzL8MA0KUMe8jgM0oJhz7T8XE7TMgycSNBNfn8ZsmlShjx1ioi7FSO930oXN2UemQZpGqlUmecNHP0mjsk/HqV+lDtewUSea38qfXac2WlazkXhxEFWeKxnyJ2EVNX7q9juhvW+IZENWFVmSRmVPuttN85ML9Sbf+fE5htoU1Ic94nfQeRLBl6xRBtxmd7UnZlf7ArprvDPsQwX75enhROSvjdCv0nC8ZkXlFWa+jGG0xEBzPd2A619yJ8Q2YhVmec6XhaibN1VJ8FMZOxRr7iqnRL5gqVVXiSV7uggLpe90yAuDeS0ze45R/2eeQn3c6diC4u6BCDnHfs9o8PnyDmRtIzhtFMtZppjOqkak02+57Ayd8Pc5ylKTEKVdxYuzy0vLlwSO1bwzuHyHN70H0JfiGZYOcv9mKeeE9RByY6pRJa1v7U3DRF7ROwEaeF6PZlVsbE8iee5VB7nzXiOp0E=
*/