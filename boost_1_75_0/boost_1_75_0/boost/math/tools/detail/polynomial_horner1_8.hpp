//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_8_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_8_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_8.hpp
JcQmkW0gdufoollitGGlJFVDtiEeSzLzIdSqMd7BdyfT/p8vmKQu5ZcO8r6ogULrHwoLFCrOLs+lHp0SZ3+YU+Oej2HlL4LOmHWdGQr4DW4fkkqd4QAkydbA7SbBvwmLYzzMi3WRLm1OqQayDsWs0eWm3I7walEYz/9C58Yv34uA6u8NUc8Npjyk7VNStqmqRwYLb411ZLCdjgzOIDpVQ4x1p1tPQmc+x9WwTYwq1Vg+3bdTNOxP2UdGN2uz+ccUmGdzacyy2Yc07cNa9iGNfbBpH+5iH1hYug1K1PSM0FcnQMdQNjnDFxY1nYdIQGt5+CYMWOseCfJv4tdJ/LTje9/wUjba3spC2mazQmxHibaZXt3fWVuFiDCom/hzbonYFD1d3RStWbvRW+5pM9WSzxiBRZ/9m9vC5M1rJ9jvCyeM2vqLuoI7Zr1m/+LdIMeAmEtA6OCykDQyAX7SpZFmnCzSyK64/IQHyYfK1k234QCPLaEbOWXrOnhE5d1vgr/p/jEJEp6TGmOGn6H+MV1Vs7f+UwVcdlgqgq5wOeyfD+gDQZ4KX4gUiqO2PzOiKsLxHE7kAxbmcCIVS4VMw0sRHP8PbV8CH1V1PTyTZJZAwgzgQBALUYNEUyUahcS4ZMgMvIEZCEskLkiURVRUhBkJRRCcRBifU2i1xa7QasXWtvCvbQm4JCFKgiwJoAZcSlSUNx0VtErAKu87y33L
*/