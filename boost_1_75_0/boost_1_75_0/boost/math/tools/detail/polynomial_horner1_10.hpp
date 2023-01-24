//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_10_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_10_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((a[7] * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((a[8] * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((a[9] * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_10.hpp
ZLT1INEW9IpYx31EWXzO2C35b2uN2/+F+5Cd/tt1IABFZWM8UT0AQ4TyAjbCJ90qAX10AgmoHQkoO4KALttj0uGCE1AXbLeIsVCkn1twU9dLQaKfOTtaUc6C8nRYtv4Mpb1Nv1q2h5LypCB/+d0epCgE4ZvFSGTw6sa9KpFd3F1g77buYUTm3ZeH74cq7zftIRpDyO3S+wxlnxNXGmXO89+WGkVOUOY2KsPoDod4VVfiuwp90ciD/JGtI2tNyoswAsNvF+zRURhXRnrspopRIB3mAilgvRjDaAJzLA69OgqZY2ADbVcC7BWTplOViVhngb0kQfmCExPxWqzE0lKnqw7bJG/vY8IH5Pni4cxeQPEUGUARdzSiXJs2kil/T4uJQmgR/vG/KtCba/BLaBl/upTnmzaKy0EQ4yDFs5lwu3+XSWDSMlsfQ1T0g7FLq9v8UPSJZlVCMiPmGBeSmawexy4c6TapStEGgDC24paplq4o+03wtNmgMYnMCpiPDTgaGHSjjoKK/iy7e8pWATCPbu3C3aHUZlwVp3g98GeyoFZu8b2gDTCM587k7uhlyDWjeolDOilo4iv6nr5aNiA3JcMwnoF9c0oHkBTP6a6QRE/87Cc/PsuAq+/bE7oLykk8yvXtLlwTcOMBxVycq/DrhN/JOsprxpV8QIDF9ygmDsicyzln12zvCtzVvo0dwwdGtwlqA53bkt/o+RBx
*/