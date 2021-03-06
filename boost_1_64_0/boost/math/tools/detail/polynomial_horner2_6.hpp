//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_6_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_6_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_6.hpp
IJuOw1AteyR7ope8V/96LRElIKWEE/dzdLju9Mm35BKXDdnD7HxwxlBkJWMwOMPwBKSEUyWfm80amO2eG87mKZUQOBpLZzAl6H5KOEchlXIrzwL9r72CG3LsAPNq+j3CEtuL1UypEnENTXsIEuJlM9yI0PFwJ2t3tU8xmz1qo4P2CPBqE050WVLKwpW5zuy/DKYcAj+6/cflXlKBKG7gLxVyABUz63oWgUIZZgNmH4GZbuiCbR/AsP1PpMM/BWAOQe9qq9LzQEFFKYZE+1j5bpHIZ5i1Rdljy9jXKQrVNw2oQWkhrv2tPO1QdZKXtYil9VUI20l4ejMaTGlwRJhgNXvZ+Ez8mApMLVmjUVFtn2d9/nXgxoXoInREZjfqPnf5s15VD/eNzBCgtVYjw2T/bDhdjpBWYWpKbXJf711a81iDYQfez3kwTowOXbxhsHGWexRH2Dle82rexxHy6YDenAQ5SpthRXm3iS1VnguE+meChJOvLUFgjJSOm6SHSUl6RFpjRiNdDb9WQ2BPqfSG4bOh4GftyoH0nJ/Iq7pt2iutR2KRAA9YUgSbhg==
*/