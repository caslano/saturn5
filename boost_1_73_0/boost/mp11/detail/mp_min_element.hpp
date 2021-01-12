#ifndef BOOST_MP11_DETAIL_MP_MIN_ELEMENT_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_MIN_ELEMENT_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/mp_fold.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>

namespace boost
{
namespace mp11
{

// mp_min_element<L, P>
namespace detail
{

template<template<class...> class P> struct select_min
{
    template<class T1, class T2> using fn = mp_if<P<T1, T2>, T1, T2>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_min_element = mp_fold_q<mp_rest<L>, mp_first<L>, detail::select_min<P>>;
template<class L, class Q> using mp_min_element_q = mp_min_element<L, Q::template fn>;

// mp_max_element<L, P>
namespace detail
{

template<template<class...> class P> struct select_max
{
    template<class T1, class T2> using fn = mp_if<P<T2, T1>, T1, T2>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_max_element = mp_fold_q<mp_rest<L>, mp_first<L>, detail::select_max<P>>;
template<class L, class Q> using mp_max_element_q = mp_max_element<L, Q::template fn>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_MIN_ELEMENT_HPP_INCLUDED

/* mp_min_element.hpp
/EqM89NvaC48v9lI5nvtcWr1egVMP8o6uVgmpz7HPYM0n3rkjS3PYrZuN558twNp0/neGTU/13/3o+2cUd9HjzwD3sW2Ha5nnIB61va62RGtHpRr43YFp8ezHvW1+upNTLHtg48YyimfHXC+OeWPn2e51wtW5sgIPWCX5PN6bctqhq8QAQz/QzfuZedtgkMfSivlXQL92be3Eu9mmbyOqsvkcOiq3w79XNgOgz7W9vE/HrPv
*/