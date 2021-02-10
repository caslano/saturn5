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
P/B/ODryUubJ3kpZjTCULSxlrAmt23dFPtcmthQkJV3663u2suShAyE43fd9953uZCAftPJUwid87IauVw6DxfEZrzOQnWlsCXJDh1fral/CoqpW04Wrpwp0uzMbqrFyyviGXDo32tadeQEpzhwposxYg9yeYb6rCaSjbX/gdK2Cisoi/5Lh1yzD5W/0r1731lMCP1WgAqsdfcbsBu/tniF5hvlVcXVTMPjXnyqBqFxM1lM/BaJRG6YnsO5VPMBeYjUpjtXZ1I++IxOOpvQUMCBqlNCGsGX4v1AaNVB5+gJsnB3QB26aQTGHUtthUKaO5EKI2WL5WN2titlIWy0fKrF+exN5dv0d0wpTZp4YctIqYbCOMLTKoDWE60Og0UTMMfzokt0/k+uaA45toWoC8QBbihNslcc1kcEL39pwAXI/YVlg62yw2vYljD2c3RyHkCewsD4U+MF4Ak/8E+ntC5cvUO9cL2bP84fHu+V9Arda05afL8VlAh92guFxXRKY/92SZmCeZam2JnRmNw0q/5b8r/EEsjErxdm2FKdexHmJ3wFQSwMECgAAAAgALWdKUt8BQVMKAQAAsgEAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMDY5VVQFAAG2SCRgTVHN
*/