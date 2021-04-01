//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_2_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_2_HPP

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


/* rational_horner2_2.hpp
UBNVh4MzcLKhAwgbA9UOPfykrqthYFROkS+8dwUV6iN6qvuflg3svRjcxNLwJYn/k0auaqjaFpOReebJqEP108HBxc1N83Ds2URvCExXI5oAkBco5c26j9nqbt6ex2uhWTMbz3mH4Qqdlrnr0nxSyGLUC2ndOFzswd8YrxtMfLWCggMzpqLQGMNjmOWjfKbI/YdMGAPeTv3xOgu9SXgDqxXS+QVTMGRhrYFEAMeCceAw9k42M+7QUeLfNUykK1FuoHsP/aSImYTF+kcmcgCrHNQq90/rqddOHPBcQm2heaJm91tCp1Z2Efwttb121/D5S5u+tWs5ur7+KxsQuz0ga6+9edgn3+HdNcAJJfBeqB07CP3ZhosvA1fJaNVlLy4nrHZXU9SYfDhwDKytMEWyJd+eccO5VRriz9hH+DyApUrYgSq4uwWb6nItSdz6hePy4TPjUiguamwYsaphV7mCRw+kOnsJFzLb24hRMYliYHavQ5ScNU5JY0IN6eNmNDC+/ul8CW98k4xoOCtgveeYzltu8tiMFyKebAx/S8ywUtcIHIiaR/r5BnEsKQ==
*/