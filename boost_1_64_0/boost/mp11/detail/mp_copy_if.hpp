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
sbSHHfggVgC6MaMU/zo7SQPhocC8iM1xDgoIhoMC+Hymn85qigBM21nN7dTxKHU8KjoetUEeHWRgBjwuT9wAQ36b5cxZwrAK3hqXpnNC/TtuBGAneqOVnYYrWt4ZGW3wKSG6Y9ONIy1DItIy1qnSkO1U6SrqdYTm7oiYuyO2yR8duRkKR0s44jQQb/JnR09+pmdMwnEsZyAcy8mHUTlQ1E9pn/1g6rtyEaBhdN4pw4bnTh62+POxvejY0EA48OLqxA3whsBtyU+QRp5KlCIjFoMxIhbNKIGvzEK/0A4RnooJ4dfeETc8dVb45LgBQG549yvjE/ofeVA/2ZuN938tmF58nZAR4myD6Y6msw2UofothVxRDtnONixwneGNNXZHY0K4o6vOJb9vwXBHJ9Vjwueshf8XM3Cf6nzsfaqgbZ+qzhlHJRH6QHSr3CWlNREjbDu97U3cKjuTi2yKjojlSKromAc6hDO5jfZRMMMopLTW0cbbPbYDHe/JPsM7wuxMhoR5nOvc1IInGJqoo+W8F0ZHyylD9Vv27XgPT7ZvzelZrNugjjshdNwJyxZYrFbNLrF7bNV2YP2jiVvljbVFKWpMSc6vEwOWEo5LeCPLtv33dwcrP6iE6qyERio/KZ2K/0yyVnnQJVapxFl4E7UiAgIyYm4lhmxbiS9ysHaEQIwyEHb1KrpV/ItpbJVRs52w7z1/OlGrjNoim84ljnPE17miz5QFk58pC9rOlBUjbHiggs8HYMJQyijTpg5sBSAT6WaRx/+D9uP/0ZukQdsm6YPnTsdRs0yBljyoIGgLKrg1TqvxBFq2XVRExxIEo2IJzO1Y3pqVg7Yd18fOIhTDuHHoGzZ2DZXhCDsqmDxCIWiLULg7catsXBVZjpnE2fnLscuK6ICFQFTAAvHTQ0hKPHJs27pHQwjdEJkbQ8LcGIrQuwPJwyACtjCIrclajeZn9FiNjHIIREU5EG5uQsbFuNn2gv/4D4TiBEFxQkBxIhK35LETAVvsxCcSt2rilsigMCMmxIGTEEkFzFB5L7nFQVIhxCdwbPvKFxIQx1ArB5ueVXL5mMVIi9UqdolpbJWPsdjiMLrPJGkVRcyiVC0OcTLTPBDRTNC1UjYVUlrzU9pnP5l5GULXspYFqZPPe7FVBJlxDkREHkEafMacOGaUiFiJAqTlQEbMLfOQbct812mk1QCtGQNizRiIWImiW8W/mMZWeX2zxZ7cHKfVeCtRTkQYg6C0CDkxKT1BlJ6kbLgSQtxa4Yc0U3qCcJtk3DqDCEU/WZ79wvLstxA4Vqv4F9PYKvPPFshyZ+JWmW1FMc9GsVCIjl8JRcWvnKVCRKaF0nKIExpl4v2PpxCKXvJ19QpfV6/FXoBWk0fFhGxRMfcna5WFfNgKmRXnUExubJxFlEx4YRsm6EYIuuGzVEg4D/OhJU5olInx788jdD20BPWIJagnYmGLbtXskruX7bE3H07WajTO4nCZuYBFhNyw6nCCZgxmQCHNQ7p8InwVBGZiyA3j5iYoukl16BaqQ3eEQhLdKmFIXXJQj2IP5PnG35O0ahPyObGEvAjfMVW/AZowmKHy1Q9884Qf0qz6DRBqxxi1qwiILvLEdQlPXFeEBym6VUKQuvRT2mcPCnoqkKRVIeSjD3A6w2yLjPkJRsX8ENv6CZlewbZe+tnPuFUTFJ1E4E5B4M5ItiWPJAraIon+8bc4rcZhW260rhUdOyP4GXGWn5fXHUT5nZRNhZTW/Dt4ebWd5d+A0OFhZPamQUJ40yAz+pRovMgiIRXMQCdhGVOgE2WoeLMDFiLNxY0PnNAwE8H56V+RWIfIhj0kbNhDEZZxdKtml9y9bA+f2pY=
*/