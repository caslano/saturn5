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
2d9kKQL5fzk86oQ3H002v9wJUsYuFUCC7YR6P0L2s3C/zuwYcO/PuP68bW+6Y+ZrST3VIWu2Rwvfk9AesysppfT8V09kAwHFIIOT0Zn6iKDsNB5k0OiTd7DUrbvK3q1sPT/F8mmxyp9tkK1HMpad0mbigCPTVJERGtSqE7dAW3SSS8w8Vc4NNQu6YZ2StLChkgKNZKrVmJcwBBBBs/A6DsGgKscXdJeJ4xClnR08soBqka4V8KbFjF135kOLQHe0YyJkZuj5s5nCovUTux9+0EqJf+o4uGxswnp1RHUu4lT1eJLd2Tv5iWhT+Me0+KnqbEw/66F9tu/IJGr55Qcu38P7wSt2H4RT4netRX5PsAlRum1STk+Z+goRtlQz4RKOA+KzoEyJG8o2mV6qgZLjdx03PTPDnQMp/7EesKPeZf9JsflbLLltF/w9BYlIYFN3XTeSZk7RKWFj5RAL4tvusvpQnxJf/TZTnB5kd00sSIfdj8IXQFDQl0OroUqdBb9pNAAvMhuZHjwxsf9SZQql17+PfoSVy1YaOVcV5I/Re49gyT945stPUBvPeSO4Un+9nyZIivBEPkyU8fzd3WNkbX88UOqwBjsXGYKoqftA/5U8zA3cRxrlGn24CD1Wk57lI9QbFeQhjD/AuWbwyOJaFJhLUCpDATuuI5YPQFknKOtjdbPDsC0IlhOHyvXb6r3UJyz49vGUb+MZIbcD
*/