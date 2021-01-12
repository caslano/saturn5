//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_3.hpp
bcM3W2z9h3TvEc6S95RMUe5dxHgMUJ4d3+HcNlhS0vmX50h4uEd+i0vYPlRxeq6NebpsF5Rh16QerGlKW7GL8i8in53pj3tF01Zo1gG1/A9K2QKk4f6OqEmcIOpTtr2vOMqWaKClj7DQYpHTGKPy4Nvv2m9T93erE8rckmNjklnpNfnJriRtBuFJ9JR9rC2vOvITxyqbakpIjoyRFy3/gf0sdRn3r2wbeSRRkehLNPTnn12O
*/