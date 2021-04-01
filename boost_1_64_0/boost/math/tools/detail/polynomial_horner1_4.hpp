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
aFpuCRcQ1nxKO34lbF/h3apcLxBLuSYwSL/+hUeHsQBDlYgwc/ZRA/wZbUhAtbwPgLAMUVaZNzz0JalSh9zL91/QfDT7TXVydFLqDRt15v4v3C3olMn0vX4tFz2pWWFwF01vPG7s72cHz+6knI2V09Wovz94FQHAC0TA85mlL7DMSjckDPXJDDk2DfWLaZwf58a0WsLcvxjdXCufEwLGQoS4YbVPNrz7lEi2IPuTqEfNJBpLKPLGWrp7xTwguqzVK8xzCOSqUejGE2hauYT86Q/JLQ9635C4jhpYeXo3GqlqFEptP8J52SeMdIrxAyrWbtPx988DwSFBAEGf8zLERxICJJxTiyHnrrcpQymm52YLz7Oe1T17uga6y2cD9oR2sAHOC+W+wzJT3nrJ1rzAqS5MwgH77ji6W7Fq98t/ORas9uOob9xAj5HVh3+2rZR52m52dP5OQHuNhKQgNtA0PB2PisEeL49qgWNr+riUxU1kgrFW8nVhSd7Yi2iiNCt91ebRM54A9xhN03atrK7M9YUvfn99QoH4aqgX/I+0yQiq0UFWultqE7kHkA==
*/