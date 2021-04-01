//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_3.hpp
Vu/a2aVATbumMTCVVXIer6b2o8922L42keBUEaL1674Fik+RjSD/yeT8cID9h8SdlSNTAkT1Sx3fMPttY9SQb1tLpGuMD4tj37Nb64exDY0I2jHjdgxgLehYCA7dhyRBmD+bKo+SShf5sVChQ1JgELG9+TFdCKIrR8aSCUBgge1w7sxEmJm7coQaamSXKWThEOGpbE9cOUUncdYz3AJpV4dF72dBh0Z5ORiZ/JmIlyKg4dRVkjUqlU1KUKCG5VfoYaVq/js5KDLGFlMxfpK8Sn/x5Vwb7YmE/cFVIF1SEDIrhjggKeXGXFS4Vz20A3zBaY2ZniRQG5VvhxRMnqWoRDy2ewLNbE9L3upH/rYUyWAjcsM1pCfTLpY1HBDt0V2Q7Rd92HcYZRAriU0e3qesVGCguJ4UUWAGaUDkvco7vJ1lS9EIukt9TQz+V2g2dyYMg4ZzmvynnHSXDXa8Yg/jMheFtmoARjuand0Q7LH5PnpNkXfPEHnRYmn/cQZH5R4DaWAY7QMKuAOLkzbork+VCGOD0C3TENu1MjMvFxrZjOgPxWKdpoaQ6Eov7Q==
*/