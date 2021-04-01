//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
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


/* polynomial_horner3_3.hpp
mC/xGObxK7bX4DyrPfwNHOtPfAbm1T0NyJjgqVGKNWauMDk4PRnW2oTgwRfkuVlQzlE7Sng1vXSOD8WF5TSxC07x0qDTDeHn8xAVCvYm9TCe8tznef+1SSf0v5P7+mLH3E20GO0X2B2rh1oJb4f2WEqw+TS6Tc3yQ436YcmHK/QwtMpyBFkSpMVkulKg/wnTiXdOq+lgze/Ux3VovA8FgDQ2irTMwXqlG9hNTl8PHzCrNS+Ugl5pp8oDdwsYcAzCnMwumHZhMYpNAjiMrS13iR97I8iNjvZhOrrFItx9jUVjaC9E3dhVxCgqIw1q60LCxB14aD/qm54pk+U+fkH0WO+9rVWeWhg7WQqeTFTr8kLCIHYoHmV2TfrF3fF7zIDz8y85/UHdYj4d8F4tr54TbaJpUonHIsB4r65wCiCQ1G8kxgmDTG49Rww00CW/WNj1mA6ax7Bfcz2PnuzRdwuGc513mlkIfVzVv9nYfKTut3tksYrZ95J2An3/RoKfaze9e2vJ5MfaN1dt+n5cdO1ZGfSJzmgkPYqUI/a1zyJkFJVj0j9dFNhHd4iJjA==
*/