//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
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
   return static_cast<V>((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_6.hpp
pWPUfBLPgbM05Hkgrv1NWTUHNv7KzbyCUzc7G0cz7puwgOkbBgz9FVsNHZlYQ99u6GiIMHGJd2I6NpF2vbnlNgiHTSSMlwo3twtw16fiKX134/bAe63N3t7L3nIn4NvULNg4GgjvmwW7lvvzngE4I9FiL90ZYdtMgsmv2AvYTc2Bye/w3TAem1Kbh58hXKsZM23vo/ssFk8LrLzheyFM27TAntthrD8tMLgr98M4PNxbHe15IOA2NTtG7uWBeFyn2x88AGck2rb8wwZ7PdM3m59dE5gXm2KbxuUGdz3TSxtv4fwU8F6LCbV95TMPAZ5Np1Amf8OPAPz1mVw9jq3+aLjdXsOMYa0Lj7C4vDaW7PcHzfOayVNP40a+h3B27gRYidN2e/4Cfnc/DgouaHbtdw6V3b6XXMM+tFnDNstQ2J56jLyQkdaV/LUUB/mhQ5x1LG5LP+7RlYO8u8LdtB+XPC48mDaynLEiHRpUVItjWzAOq87Gpti7DXDXXDWdW6u3Rf7WnAE0MRLNtz+3fLvS8u2y883Mk7/t1qHsgevIFNt5Yj/ON223MvO+7/hYNKStaRz5ro9DQ9qabj8TF/C4XyVpGOY8ut724477lRz3TbJm1LeY+wwBprUIBvO+GxuMn3071t0EYXz12vc8burj+ifApt/d4OptSXodoOHI1NkRH9cv1LaDb/hYPNSa+eg323F4WLByiY9HCrDrtc63+nBW4Q7uSD/OKt1d/w3A6S0Rjdvx7Xac2lqxuhyA06Z+Zblr9lZ3fQK31zzlQRGI+P9przW0V5O0ba/3Mu0VMIOKYXGvuBHGYbXgO9AWh6vjflrWTSymXSVW3sWbWqxfbQ8yd48Bs2nTMmXpbMN43LQsjtysHefPYYZvjnB+tzLl/k0rDvfVSPs3fQzvi7MoitI8Ckls3sudhPA81u43AX7G/f3ofUhOTlhNBedV7cs5tdwuyfiMIzmcRIJWCU0zX878mWNrCzgv+0zcEVcGhb32MozjOL/e9m3uurjyKpLVEXizRupxwjqF0CCQqaiHfcDPobIEpKhSTsOkIlV6SD5TSx998DHcsNo99jHN/xmPP6/yqoZXFyNomgcmZ86sdq/G/3WPn1dlnqd1RcKjvYXeYH5zj9DlL0nGUhEXCSdiZfHM8sqSPHw0uo/0OeZll2eKhUlz5kyEXJd1Ndq8celiJ+MyYnVe1iSAPMF/lexA4/+F8BKbZGkckHAQfsvH0bu6dVznoL0a9uMkj8Hr8u5w8QVco0tqVhaErpw4Ch5hlseWd6/LMylYksdw6nWo253TxZ107aSQdlLkwpwPqC1u08fnt7ZjwCCtuu9RDStcH8qu7ffeDDDqJMNQ7bnDG24O9IYAPklmfPjeR93+U5A6K6uKV9fuN6D6z12ccj9qqDmxgeC7chG5cOKMc+87uZGhG2Kl+xDKSwmPUBeC59n15sW9Y37Q5qW3cHLZ5HPfjfpo0jcFeM2YY+gNo1OGvTc1NM1o5H50GNPAEJ9add7/+TyM3U3QBNg47R1FKBtvqdOK6/TMfnorHX50Vg3myx7GVseqzs+Vi+0YkOT6LS56dSPqPKxyeu1+i6ad3NvUzaGhPg0YPS7eBOh+8Z3Y3cOG7gsxmJdssxisIpvOv26hMLj4RsbwTkv31WPmi59COpxHu+CODqe9viaquCx4cO133Bsd4nXgzNCg7XerqxdsAVxr9lC/fTS022Q2Z9Hs4f2zU2PuvbDhJ+E7F1kc13HBYzIyOjY+MTn1kOn9QUgZjxo7aMu85aPePinNwpTy6y7zHXUswGbdmPDD8PRUOnOo475HJ/89ZkifDM8eW1YrYq2HfTdG9PnuaQVwZFw=
*/