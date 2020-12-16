//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_4_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_4_HPP

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


/* rational_horner2_4.hpp
LkhexKdutuN0sSZU1r+bRsXPdizJobnRBIewAQ6ODGUfJgXpJ9iHqYLDhhsvRjyino5L1PWhyYg+MNsHXYbyq64KOneCpwkOc565eXt7o6iysTYBERpwmGuGA2OWiCZCj1/XBMXbRJLDLYLDWXdsh1d5L7UGlZ9tc2g1w4ExK0IToe8/q4L0KOzkrYLDqW+djAq499EmD3JtcfY7sivvelFYWdz+jbPAiibEnR9SHnTq990mWBzY+j3GO4t2JCEPHXvxRkMsOG8oOEL+0x2F2c4dhRa7lLhtL9/mnR9ONydU8J1+dhTyr1nc77DIhm+ZlWFIL8ZXlrLdGNel6PvR0iANxhyZIebI2wWXI/t4jvOGaAv25VHmfXm8l6yRXF2Ifi5eqmKYd2gxzAanxuUY7EdLmPdg8W6yRjE7CvnXc+QBWkO7/WOIxTi2/DpNiLvGxAVBqoZe3Cn04sf8wbfK1gepFnvzNT5pLyYbsBdixyx+8qKADD2WOTJIMXC4y363/al3t8iRPkQF4LAJtboaeOeHeGH/spzB2UOdX7hg/IMg/dxjpLIZd2s242HHZkwXP4M2k0cOZGVSFo4dIr8zGo3dpah5ckSQzsLetF6wmBzcsFyO9hFq7Yf7bp1Q37Ar6/3weC8PCcUqSvlebnGJcfviw4PUF7pxjx3zXrK+SbY+SuUp0A3Uxm24j3VtVR01gyMuRdmOQUHn7dB7BYvz+01DftFjtAm6kdUZ9Q5N6Qajn6EJcddXTw3SSuzR7rPrqw+L1zSbS5NPlb9l9MA8yTDEoriqlC3Uq0vR67slBelY6MUswWKPfgPek6N9nHoiv6Y2Sb6V6KlmzadQvRRlfNntp5Ki7MUfASfmPVuLec+jJrwaWBKQvnjmLEP2gvOUTJeiryWCxR5gcb9gsen5A1BbYD493MEXD9hxTmZfo72XRaVVIdFTXhRKiP5OR8DxMeZoPsYCqgGLZkvOkdpL2edITq74kZPL7GPoUpTt/DlAV4BFg2Bxx9et9e2N4sbDcET88lA/eDr/HLF7mZMrqgexZeTpUnR78WOAjgKLBwSLF8/bhve4n6AGsHgFLDyzTbGIFRWy3f5xiXGfEX0foKfB40HBIzNl+/my9Ul6JVm9y2DzqDPGI5rH6m8pKfp5smCRDxYP2Syev/7ceOWNETgXaE2QLNoMsmDbtepS9HnyZYCmgcXDgsX2E9JRLfUpWtMd+9YUWaunaRVrnZoOvayMFrJFP11i3P7nloCT0/yI4PHXyZnHydanRe4J/AzYjej9pnSjwowRhRjt3mBzgL6DP/6o4LH2mxE4KXmGJu8Ff9wreSxabWR9FR0tK+W7G+QS4z43WRugR6Efjwkex/d7szcqUoiaVjhDSpY88szx4Dtd1aXoec6CxU1gMVewiM5YPkmOdgktwswYiTWl5WVTLEoreTdrmhhdN94M0Avg8bjg8djoZbj88SwV+JCPAt0oMcajOBJmd0aVGC3+93KAHgCPeYJHxYwjsmXrc1SH9wSXwnbsWGWKR7jahHpAivK/VgTIAov5dv2OOyrgaTRScTL2KZgrtQZZ8KX9usS458qygFN7eIFWe/h5asJcWZuEtyaN8eAObmhi9HjoUhXfWKjFN14gTxf5W138DSD+uFe8ozG2A3ldir6uNAYoEyyesGPDuWVfyNG+SE04d83HuevklcZ0o9iEfw4pyv+6M+DcNXxSsLjr9VN/guWktafI367sjrc3mVlEKgqiE8rGVvCZDE2C8slnBmhf6MMiweCStj+OlaN8iYbDdmbH3xRcwc8gUhGqLRzPlpHglqHWkDsUh6c0DstooItDliEOjA+muWWotWNGgO4Ch6c=
*/