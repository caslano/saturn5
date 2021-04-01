//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_2_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_2_HPP

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


/* polynomial_horner2_2.hpp
LpocNbFGVQPDoeFmhwYroVs/yO3EkKdsBs0bIjqAZ5sOTh3l1lwD2B4srSRo6BJ+tOSDD/mG6YDzxgH61il+eHavTP+5+bWvFAyK4Ogv1vDl3t3DrH8uHglLrnOlba/2xF0JfWC0zKWEM1MRQ48BFLqlZETdPlt5wAT4CinKgXFdEp5LmcE5fqsKefs/sfK2T9W75soQoDSfYpG3JLa7z7KzBuY5UwFh52+p3Iq/DOMaUsIAEtgYRgLuwC3V9PaYyuNnrC5X5rrw4b4nu7FLEGoGMYjX93t8khblKO5iAFKeiqrmtBIJMBBYbFDw6nkmJat2rPNz9zOkxhyZ+H1JPAySfRZu3sd33DFxF30bzObXLvTWgnW1td7S7NK3R3vDzHsCVrb1XZ4DbpqB59Y+SNdz6Rm3Gzzxfs5d5w60p+REKuLhiAkb0xZRerH+R0wLjPd4/XR6nLSyPnkTqQWSm0imFMmlKZ3pjvulS9uGRx8pgq3ubSyn61T2xJMdk9VCsZM9YA3fGD1qlNH9gZL/o67fok4X1FbBHEk5xONgc4wNq70snnfK5dWr4w==
*/