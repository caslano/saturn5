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
5+NxpWP7IvR0JMzXtAxS98px+kdB4y24PZUrzysiRSEe0/eGumUlk187mjn80gqjn9nPyqnzxX0Ln6dObuOKk/eyPdI7jdT0/yT66sDnXh0Jfn0BNNYbpqbGZIgz0lYjKCz4moIbW1F6DGcpggjias1rsjaDyIox0vD/tXJCv+3pdm4cCRwnbXU/3u2gowJLb96vuQnpHJI3K1MHDi65ZUelbw8Olr6AUUMUe3LCtcnnzwQMbl4bdWqO79ntFMaUdR7W7kS48zWrz5Cj/cE7kpZMDhzF/MU7O2wVwnL3Cnkg51OVMaBNPMPipvuK6W0Wl9fXTLMvLJjZCwWxvHL0KFEsLmaErvPpmqjyo0UDJltB41bnXELQgnabj/aQL34g5hPQaN0odYjGXei7+0Rx7XeorqUP63Zlcy00EQKXs4DvfK+N5joO/dRhTLmgaG1L3R/QWq+CnhLe+pG3fa+QWOyq45IqVNpaAhczeyXYo44CLS97fcMXPILfJz+w95Jp+LozkjCFxOg9dROa0QOXEiOmVsy893L1y7NUK4xCoh09lxgo8XsW+Z4gCA==
*/