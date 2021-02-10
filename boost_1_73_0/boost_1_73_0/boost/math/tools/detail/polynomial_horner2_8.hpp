//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
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
   V x2 = x * x;
   return static_cast<V>((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_8.hpp
Oq/WIRnfFUqywj0SQ0ZDdqJGcf8/C3+Whf+l9u5aSrud0hB9XwVC7gRoYCcp0EDyJaud68h8v81K5DQPSBr2bL1eXTFhtp3TZHE8gEzxluT+td6oypC6FrAXSj9ThxkM0vyVGJNrNPhCJnTbclUMGaRRdPL2ep1frdIT77+6vsmjJH6ZwCSHRldR17th2wc06bNiUr/wAwhHMc6iQ9islA2Cv+1i/CDCeMn2QuABgw1C3zWaF0O6Xuw5KYDQqggjzsKcu9ogslL3/hsVoFd9e0fc0mWwsh4gus8r/x5igv4jGlluh4t46cjeu/q8oeaW1IcUZ2xr7cYs+xRsKUBntNNCN0vmAR1Q2HEsIbZp61J4BNaIfSBIJpcVXZ2G72x08vHNzfrq+v2IXQqBHb1+Hj1/TLRz4vWbzx3xLAVShwlV7qTqj1z7p5F6VFX8RFXf117f/qGzezLQcP/F2T+F3siLccgkeNtOK0sWRTkXWL64W0z5LMYXi2L+cloU5/PzYhovFjwZ/xzW/xKqWXTkTRYdyBQd/539AVBLAwQKAAAACAAtZ0pSj2Zo0sYCAADNBQAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEwNzJVVAUAAbZIJGDFVE1P3DAQvVvKfxht
*/