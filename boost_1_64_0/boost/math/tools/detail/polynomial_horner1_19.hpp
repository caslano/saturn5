//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_19_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_19_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((a[10] * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((a[11] * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((a[12] * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((a[13] * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((((a[14] * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((((a[15] * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((((((a[16] * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((((((a[17] * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 19>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((((((((a[18] * x + a[17]) * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_19.hpp
6AsPsRwhgtQ9lvXexxsTvHe5eBPonQCrQZh0+/kkMy5hZibGONVAXiHKDK6tkWh/6znTbd/O6WQnRF5+TkhAdPGE70v8uMjfRlaO6LpbAa7PsTi+S1HkkyFV3daYo8PJzmR/y5+gGP8+RHp7JN7ZujdMM9NWW05xXk+rK9gdYy3cG9ZXTTV2WnfQlyHsxiCDchmD2kYJqZXuinXXv+Gxk8p0Yygfd++iD8CGtS0lASi897Pqm+W298Is2+Qgvw/kOeKSmaYRua09OKi/Uf4VQL5FhmqNaYXRhfWN6fal7Z3J6tzMjnFxc3mLqKCNbmlXsrOYDgnUxLVMkbeWVIKqFl1+6OmHghbjZYZ0fhqkUyCmGReKFEU6g8wtHeR/DuQbZCtBsGIMxlvfXqEGFm6M/3+fYpw2VprWMG/pynRnZXLg20Cq/Cm2/G2BHEFUKdtSL3cwubg99dDFjhge6h+Qa1GtsWK6UpnBKyvK/9Eh97FlCz9DB3RwRHTFDbM2rDwOt2c2+/iwYfdj76C4P7WTyy7jSlEudBvKtXOUPiz94S8DrAZpqbWVTYW8p/2FyYE3c+go9ORwa2+zfA/q9UAeI0o4rhtbZfZGZOCjCuQYkqIixJo24E49d2ckrFRV9FHNZR2yhGDcStmPnSv+GaiJ91ovfFQBnkZGtNzW3uBwGWPv4NAXp4/U22+skbDZnh514sMYDHRYJKXEWmJ6pX0pmJL0HsId7wvinFBOK9PUfp89VWASY+YB/y2MpeO87s7Yngju8kUfpFz3kmANZqahaO/Zu4PqzAcp5z0nnSaMsa6WXZ57n+9czm+QqVirqePoYG9nYjc2jvbXY/1aj+dHID0mTK9of9miz5c0v3Q578PatmKG1iZcaKt2pnvFG2aPuhZoI9oy2mjcDPeg/SS27HqP4roe2tEKbYyQGh35C0hwp31hwod2dd9ib1Y5YxvTlneg++lziY3ivQSgp0KcMdIwxTvwrPb0+E30HQJlhUlDsBUcPWPynMeFw5nRGuP9Ob9FbUuMJFKijaoEyd6wv28ZM8NZabCNNnamAbz43tKXgWyDmKUVw7xG4Rm/vXDtOA3bynegQ/7G2BlAvkatbarWauP7g+1n+aTK3lDng9sOvdCAfeJ+xZ6L5lRbQ/M70/PQ26Ed5PKkQkTVotKNi3a7WRpABizFlIC+exWkhaO6qhymFUNhlTXN8t6tbw99d/SfyGUdYpa3Qkg6VOlqZ859jhcDPIaMqWrFmUaT3a113/dsrowm6pN2WDsVdltH2lYZPq7THrobbP1AAIasZPdHi3RwWWnTah0C24ctrp1xXPpnxbuVuaxFVDVccEL758iA2btDO/o1wCOoaVpbGyPQZoh97MPRb4cXDJMgH+YD94dnC1y3pHakjjY3HeiVTE7rolyPQbypqaK0Rf5wxnf6OnXl2Xz6kQAbo0aauiXKohCieQPElwd3BxyQqxCTssGYo60932mMn/Jbj2dqQK5FHAtatVpFW3HABZHto798rF9AB0OytnXjmMnGzZ2LoX1vXZqWvr1vzmWXW+qEkLryLWEHzNW245ygwNLGcqZk2EzeOVyHLXjAin0XkCXIEWcwpal/Dqv/pYgL/Ha/nss+rFGScVdjtHkp1Z/0Xl+RRqt0axxzeV/TzWbj03kpjf8sytG0Vmja9Bf1dnzYOveExzbeu4zJ0f7NyQfA+Yu1vJbKyflxGWAKBjvff79szFy03GmOpUQk20c7GPrURYAnUEMEr1RNU38ORthYb+JYnssvklbXihqCNtJeWuqHnpjzkgrVlhLBBI22VQNmHF1L3HTPKtdlkTKNrKxV4K5lTXQvl+rAR3Pf37OiUto=
*/