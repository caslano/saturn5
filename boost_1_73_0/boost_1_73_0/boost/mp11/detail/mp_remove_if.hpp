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
PEOjhUjgRbpOoA5OkhjglEX5aorBEkt1eAT45iLLIZIMZiIuUvQnMkeqpYUWSi1zjKAWPMmZVcXEiq3vqU4WKk3I1p7/77HIPiZ6UqC5drmj1mCBkeaZgjTi2aEeRPIxPoZ4geVZx/HTx09H5C+sle7EHxpfYcAuqn+oL7LZBcE//MLlljN4xtEVGveDgxB6bKTHXjjtTPp96gfuH/QYTptn583mcAcp/BxDbfdSqO3CGVDfu+sh71bN7CJ4S/3OOND676J6P/SmwbXrTT0nuJ263o5iYdebXlPqOUP3dr0VCll1GGDrAo7ZhmmKZSnmL/m3lccYtkI3ZrWIFMRRlgmFOa82eY9c+GBJ59gSYwaoCE9WJ3AvCkyNFRZqwmKFRQCMI68EzYCUepMUsMFxXUw600smM23aK0vmJ6TKF23Jne+GtOeEDnIawgjEw2ckXwpMPya/h/Yno27ojkcb+LzIYm3hjwI+dXq7UWvkW5gDSq93Y9bItzBT3x/7ZRnsQB72EP/fuB7tTK7eooUR2M3AAbqO+m8hLyX+jR3B2J/wrc+p7T6yZBKPz1QXQ5nxm6UYrxBZsayW1i1oNBkOLyqmQmage9qRaVl/l80fKOKwSvKt9l+2R9vSp4g+j5Xky3K8D+GCYZqva+op
*/