//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
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


/* polynomial_horner1_4.hpp
iV9iM5o98UuVQuvoCW3yVjnlu5+ThOZT98jyQTWOPXJ46Xktbh7RMzueKXoHCiphf7JCWSJewMPmMfLGUHnSZQph414rFoILY+ax+4FTlPxoc67jAbYoNl78SUV/YLE4teUMXoIY4+FQT4M2FxWYjz732zAPOQvM143632Ae39Y5mGcJev4BWukU7UrOPgrs+a2i3xXCeNwIdmBKSPRiKD4UsmDDXpzIgorPAv4VUldOpy5XOMwYsvqB83nnNoFsN753KYU6uPg+E4U6aGQXX4CRmt+EzMXvampJUDhlFyqk+OmpenoX4u+AyQygnSkskuANP6maHjvRmTsD2czdslHQxwvQ9fGqZ8P7SJ0bSH2jVgIpU04lCaFfhsbs5MJlHXXyOtbJ9tX/7zvp/pF1shA7WaR28qEz0EmYSkZouSaMBif9LYIGT+lp0FJRxvWNMMJbc4leCmTEJiDO8wcznu8Z09KP+kgE2jsWgdapBPrKD2EESuc/7+bYhN7U/WqM3L+o27+C5u+KZ/RbAijEA/TuU1Jkg6DzBSmO1VLmARTJbDuAmUSX7wtPMm39ad4K3GdnN0jRKiLqstswiF3oFgJOiYU6Jg3+ZcC/bNE/RoRfG/wD1XdM7qpZouifVUBrSQFjH2KoJkidIIZJkfIeZ8nUVtnYG+N+Av1ltPTMOs4MN3jAgyOZLukrMiC7GTAEw89st1tgvE22XruE
*/