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
jbVRKGbyj4yFdkNvYiHV2/Rptu/Cz+B5F+6yFrTMmed6yN/hi0XgML/6MpYox/zHVM+Xl/LBqDnlqJ6Dl2Loa38RPJErR+E71TOLPrGjEIf5JHwcfU1VPaHL+Hv+DhM1UEot8reZR7rfbWm5JCcuxIL02k2U8i+gfP1CS/rK5HWEmA8W6oLuKcHYQneLBTFlrCpD9r9AVrJQZmshKSTdMPEtDpIuxZY4NaHB7c/1EBpQ3MhbZ80Ugu4vBlv0+BApqclso28xDm2W6CEkRostKBMJ5KZIPFBmFp6khZ5I5/AWcc/NXQ4hYtI8A4lfpxs4oAakCDrI3iMFNjXZVng40DdXkBcT8PITq4jHHnkF1g1FormWrp1IikfyoBsrUdto3gE5qTugWAP5vkIJTGH6Zs95R9tG+Fxzq0AeVpAQOX9gEsKcVS3FZ13IvxuF/PsmU+AIoCk+A+oWaFv83xWE2fPKbXA2O9Ba9fyAHk5g6EkH+4igj35dY8AlUSnNTFRLZhX7GxqJxZYfJ46dBKoXn+aznLz24flMFSPAFOGXOUwcoA7+8ZMOknaGjsPsZwQpJsHbOKfp2iqJb9G29noW4KG0k4Pds1ziAvac6oLdeVwqbUW7qMMIoMOCspNpU0/tlwS2XrU/YF87Fk6iyTwMpatHe110QL5MXNfyDu5qx3Zk29V1K/nEIWzvgqkcDgjApXquHeWwNDC+nVQY
*/