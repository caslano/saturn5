//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_4_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_4_HPP

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


/* polynomial_horner3_4.hpp
5jpgp1LigqYP+EFr8i9TeKl/NU3Kd6pS63L6BPwvZ/hVDfRnrv/MSW+P7Ma8lG8blu9+Dz8BUEsDBAoAAAAIAC1nSlLM/2p31AEAAAoDAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTA4MlVUBQABtkgkYGWSb2vbMBDG3wv8HY6U4K3MVRzClnnGULLQZGub0Hh9r8nn2kSRPFlpl2+/s9X8gWGwkfTcc7975NRh66RoMWNprUtDny0e3owt2owt8nzdv+BunrMoqrVDWwqJLOVnVcp9IbtiV7BB+4o2auuCRBYbdSBBIZzwbjy+iWE8GsHqZ8C+C4cJPBj9CcZT+LFX3ckU4kky+ZqQ5u4hD5g3TKDjjNp+wUuxxYDNDOFoF92jfnFVAp/7LY3S1UYnIJVpL1T5ocHO5a/jjRK1DljAotKYiPg9X8rfeftBZqruyvwgsl+QxANkrHKuoYLjElItdpidsoK32lWgjBSqMq2Dy+gg5V4MqTS7ndCFt0s4Hy5Wm3y5Toadz3r1lPN4NB1DNLk0ONsSwMkhbSzKCuU2Yw1aBRHCoLFUBGFOyYHFP/vaYgsFlmKvXJ8n+LmgZxRFQedtCHUJHyAczu6X80eiCUEjhPH4y82InjiEj98G1Pnc
*/