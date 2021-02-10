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
56fzYZE8bpZrU53Op9vx/O91lqx+22xMV2W/1v9Vx8uh/qWzdn/9+mmWfPz6qS9bGadunPpxGsZpHKfZOM3HaTFOS1JYmpNPSChkFFIKOYWkQlYhrZDXkdfx7ySvI68jryOvI68jryOvI68nryev5wtMXk9eT15PXk9eT15P3kDeQN5A3sB3lryBvIG8gbyBvIG8kbyRvJG8kbyRI0XeSN5I3kjeSN6MvBl5M/Jm5M3Im3GWyZuRNyNvRt6cvDl5c/Lm5M3Jm5M354eIvDl5c/IW5C3IW5C3IG9B3oK8BXkLfnrJW5C3JG9J3pK8JXlL8pbkLclbkrfk2pj0BheH5eawXB2Wu8NyeVhuD8v1Ybk/LBeI5R1Mq4t3MCmvSXtN6mvSX5MCmzTYpMK4w4RLTNykPXkH3GPCRSbcZMJVJtxlwmUm3GbCdSbcZ+InBc474EoT7jThUhNuNeFaE+414WITbjbhapMweYfwDrjdhOtNuN+EC0644eReccvV5sss2f69WpqHWbJ5+LY0vX+93K4x++vxYTvrXujjC3mevr2l0/Efpv8BUEsDBAoAAAAIAC1nSlL2p9mJXQQAAD8KAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTQyMFVUBQABtkgk
*/