//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_2_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_2_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
}


}}}} // namespaces

#endif // include guard


/* rational_horner3_2.hpp
B6bfGAmh2IyEcpeEQ45GgeeCTaofCvvzQAZcdvsF5EG8KVZM+nuhCnbK/Lnoo+BkgzA6L649eaFltSUg3DSG52ZuH4tuz4eqTzT6V3GcqVpx2840wSrTwCGtY71wzPP1xktICIdrDXfPZsd5iB0XX4412mtwPQWmSx7yXC0V4wUfe30m2xYzXM4oYenAbQFI4kbsqc11LRA2gBdEYERGzlaQFJG/JuZzjgw3ogcqemkRAUOpQX9ZRJY5zyO1n2DmTmMsMu/sV3cXveuRBj/ef0Y+KL7aIStfax7qBHGAe2ZDsv2T0mslpsgqC+t1U9z7ZyDH5hL1ieLM14ICbmCgVUECaZ/VbocdwUD9+/CHKork023JsksJEPxH7GHz9BP5FklH3UbV+vh+VcdbilJFMCYmc81J95uluHZa2vDfmGQ39NcCW7ffbKxpViPlI1zEAKPyLUJ6CvXop1cOpFFH9Tu6j/C9CR8o0uCR5jnB2unk8pa4EtklJnvNw9LMbQ41CFzvEv6JEPURtnsTx15KHulobYjVRbLi7Yy9ayZZwd7Mkc6YM6p7a/3lTw==
*/