//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
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


/* polynomial_horner2_4.hpp
w/3oMVuXFQFZMmoTSoVAeEzQiJ3LOdPMmcKnDV8XgT0yjJOwANrWoWMy0K6IBOfbLskYmU2s9RIHXeNM712GblXC5MAHIpLKolA5jMYHSV8pCnyMwcyx2J7UOmsBp2fIO4GlRJapK6h+zkz8BcOlkmnvgo3lIvMIQIGLCy4u0MsH9L9bKDTm2CjrITsLNnaORG2Q1Qt5S+zBJ9IlYlxDcSyAxfNw3mmcsMk66lFvfgJx9dRybNRy2SIN0Q6g++9IE+3TRT6XNmBif8ot+Uh4YXDIl+PbpVibJhwKMqrlEutwCQ7L+iDtP9pkjoUJjEUgMgNow8lMCI4nS98HRpZjxr+vrOWcOoSor4snU1BMPll6Hwidw6AJbLyKstfRWjVIsD+diAhs/fXEvK+uM4YhQbI5vyj1ReRJ15PCW3CdtY1rnZraFdCGEa2OmiXCJl4nObjyfjtYndI5ctO0snRo5L5JPXhJ/q1hdWpYvvJKunOT/HLlLTnUmad5+9aGrWk62uohiMTkdmjyJI5aL8q+s+eanKr9FJW05ndt5Tusx1HOxTgKTaeIw21vfQ==
*/