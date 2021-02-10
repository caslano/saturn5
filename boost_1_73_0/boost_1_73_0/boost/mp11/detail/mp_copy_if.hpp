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
Lr1EbVRJajPp1eR6HZAIr0McDgZYMEyNLVr9CboaERZyQ5UXg+u7o7mWOacM4AOdCI9MYWa0JuUroyPcGWMAwuHN7Wj8+ctpvwtA/ucK4GYQwPofVwDD8GtJlpxsbmDS0DMBqL8sCIDBAla5kbFR+yhrq/dsW5H2R71V63CIaxWcQun9nhNOLsZa7mj6fr94qHyJf7xkNJxVbM2BD09BrvpJXEd0hTBWZreTOu+gIiH688Uye3iM+g3G4yLNRHgbjpnDeyCbR5ptAyuyVVFjOyKy8GTRl4SNQFhKh2sijT1XGt+D+K2N5RJ7a7xRZjuFposWAk8DFcDcOB/hByYBPLEQV/cvDM4D82q3or9K0uXD4kcA90rRnn9fistO7DMEkxyNcYKzp/R78pwms9VzkqaLFGKy1ljWipUYNT3+5sfiRJbN84P7BVBLAwQKAAAACAAtZ0pSP+74Wt4BAACCBQAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0MTdVVAUAAbZIJGDNlMFq4zAQhu8DfofZlFwKqexuoaxXNZRs2PSyCYm3d0UexyaOFCylJW+/kuwklMKG0kt1sCV55p+Zjz/hloyVwlAGvFaldq8NHV51W5gMpnk+Dw/8PclBVnu1oQLz
*/