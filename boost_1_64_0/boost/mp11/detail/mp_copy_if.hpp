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
G+8BowAhEZCH4G8g9AkGFeNT2EXwxk7KWFonpUGse3yoz/sgWU/Z5IyGlHqcD3egTzticKZ44DrEb7stkXY+X9IgnyGBo9IBuzH1kX6/5Mxmc09yiwer1qP57yPptuO5T4lTOSwM+NNnfphScx1bfdEl5OGJ7KVxOrBzfUyweFVdEwyMnXml64UW/0eGLolTBTkVgVxkVL1MyFrxO0io/2RiMx6Lp5B96sT0R2rXukR/++SD3mYFETeBaUw0MhmhRLfU4UTOr38KdXJziYnP3cE9XcB5i8KC5bvoQMm4kyzsYURdTMjhZQ32kOWRbmyKkfMIgm5zAmBwXUX51StgNRIb47BGFvBvZtyJA/IMamo+wJazG6cvQpp6XG9AVZmVOnGFngzU9AL1yQ3xt3kOfKqaITOYrDVQd5rcgeHiGSrHjR8DYYJGnU8vXuoWyZ9G6ZBNGPnx+DOplM04Ai9H468OK8/pIsGbf8SIzen8r4POn2X8qcpLm6UpIPlotvKZL5Af/cjw+6VNBegkgME/9xZbWXSuzjMoWY+2deh4vVQFl74fQ5OMvLmxAQ==
*/