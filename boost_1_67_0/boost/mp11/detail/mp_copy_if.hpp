#ifndef BOOST_MP11_DETAIL_MP_COPY_IF_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_COPY_IF_HPP_INCLUDED

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

// mp_copy_if<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_copy_if_impl
{
};

template<template<class...> class L, class... T, template<class...> class P> struct mp_copy_if_impl<L<T...>, P>
{
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )
    template<class U> struct _f { using type = mp_if<P<U>, mp_list<U>, mp_list<>>; };
    using type = mp_append<L<>, typename _f<T>::type...>;
#else
    template<class U> using _f = mp_if<P<U>, mp_list<U>, mp_list<>>;
    using type = mp_append<L<>, _f<T>...>;
#endif
};

} // namespace detail

template<class L, template<class...> class P> using mp_copy_if = typename detail::mp_copy_if_impl<L, P>::type;
template<class L, class Q> using mp_copy_if_q = mp_copy_if<L, Q::template fn>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_COPY_IF_HPP_INCLUDED

/* mp_copy_if.hpp
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
*/