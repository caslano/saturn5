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


/* rational_horner3_4.hpp
dK08o07kJcAk4MhcKslCR1q3DK2OQKwn+ebnifDNRvLrG5FvHk+Uv1k/k/q8CVZtjBZwFS0aIskBfUmW1qRcC9FCPAQimvMxBIYLI8UIHcmhSTpXmFZgHDAQL06gDio2mJO0vreGLVR4egfU2zHBmmmkQ1RSlFgUbZ0XpIjonH5BN61GI2obrNBqwr0sLUVtHTgy+VgeE7U16KHOohe1WnpYQ7+gJuzbZIsKMh2EjEaJFBNB0Tb/cSOpH4LNv2S5lpR5r6ilSw++9yEyiRfEXrpoW0wwPC9+qQ/Q3NTPjwqOyryVEmTqUiCIMSRHXhatFBdc6A1buRRT1wdIWtf5fgjcJ40nL0CsmXnCsgH8bzJng8ejzWSEmrK9lU2XSCyh37fobKn+juHkPvi6CTYb3DSLeWbxiiBlj40M72qy3DJ5HyX6mqi1FYLtGQ0EdUgTvPOELjn6RUHgaTm6JL1EQw7mPw0u4d4TYGFDyhOCrbde6JI/s5qwt0ii//RCxtUi+xVwGW9zVbDNbZFY2A4mjm+fETKKA/SvNKRum7AxT7xV8e/RLzgEvn7WMMGWGkD38NlIz+e2CIu2ZUJuQ8/BWQhsmxYlnorM6kF9m2zPeUuGBRlUxgssJInpEKjzaJvWb4Qv9TGzxRglw3UrdaJpkVFMqm6JN/jy1GOfyCh+XL9gNT2I02eK1OEwHxKZxa8lw36cLkFJl6ykG6ek
*/