#ifndef BOOST_MP11_DETAIL_MP_REMOVE_IF_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_REMOVE_IF_HPP_INCLUDED

//  Copyright 2015-2019 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/utility.hpp>
#include <boost/mp11/detail/mp_list.hpp>
#include <boost/mp11/detail/mp_append.hpp>
#include <boost/mp11/detail/config.hpp>

namespace boost
{
namespace mp11
{

// mp_remove_if<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_remove_if_impl
{
};

template<template<class...> class L, class... T, template<class...> class P> struct mp_remove_if_impl<L<T...>, P>
{
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )
    template<class U> struct _f { using type = mp_if<P<U>, mp_list<>, mp_list<U>>; };
    using type = mp_append<L<>, typename _f<T>::type...>;
#else
    template<class U> using _f = mp_if<P<U>, mp_list<>, mp_list<U>>;
    using type = mp_append<L<>, _f<T>...>;
#endif
};

} // namespace detail

template<class L, template<class...> class P> using mp_remove_if = typename detail::mp_remove_if_impl<L, P>::type;
template<class L, class Q> using mp_remove_if_q = mp_remove_if<L, Q::template fn>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_REMOVE_IF_HPP_INCLUDED

/* mp_remove_if.hpp
TvoB6EABNsMAVJapxHGZlNP3kGB1qW7cH99/Y5mk7sv7yh37TqHrC4dlDmqs9QHrTTxqO3b5zNkyM7ubeEfvjY5f9PW3SApReRarkaiU/UrHfEy2bo43Pq6191f2hePxicUwnPXFHztecWU9XXBhPV3W1os6XCbvtCYPHLdp/TcpF/WzMnJSEln8TNt+rLG1n4QUyuoztZwc353OIYU5PzslWXuPr2OdKNX2y9e0j0HSR0Ck
*/