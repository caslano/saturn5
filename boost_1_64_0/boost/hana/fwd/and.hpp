/*!
@file
Forward declares `boost::hana::and_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_AND_HPP
#define BOOST_HANA_FWD_AND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return whether all the arguments are true-valued.
    //! @ingroup group-Logical
    //!
    //! `and_` can be called with one argument or more. When called with
    //! two arguments, `and_` uses tag-dispatching to find the right
    //! implementation. Otherwise,
    //! @code
    //!     and_(x) == x
    //!     and_(x, y, ...z) == and_(and_(x, y), z...)
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/and.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto and_ = [](auto&& x, auto&& ...y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct and_impl : and_impl<L, when<true>> { };

    struct and_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;

        template <typename X, typename ...Y>
        constexpr decltype(auto) operator()(X&& x, Y&& ...y) const;
    };

    constexpr and_t and_{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_AND_HPP

/* and.hpp
BdTGiLWjldNmvPSf1VJA+CJTiqDCxQyOugRTonXPhfmJTgOqoTACntpE5kofLu+0vwr19ap30cow5aLIFmSzf0ibbGx2Zp9SfZHQ3fW6APzC2P0t1Exaec/wjRvMvlXDm85J1xgTJfbBxiy26Pwn/L7jUVaXypS1Z7/8fr4jl0pmv6H3ShXdZ9RTCBW8dzJQYvxFnR9ZWUO1dnM/hOwKA0WPVq3SezNWOQeLeqf5PRl/wkiaE5tY+FpuFclzOj0aPxCWRskkWclI1Uu1ijCtjGZ5hlTSlZKLArI045KqBoQV0/kQIZacWQH8xZiOLBVCwbT05t+2pzQPIuqqFbPE6yQ+PPQyphxyXFZnu3cG2wyDSU3zKT8KcA+kW0AJ5Hl27oEwEVXAXlN7oKi1zyAGe+Ls/+nL5BNd2b16YB1dQXc0MyadG4FbFP1q9dO2gLYnxlaGkNwCJgfqpGbzIqMyBItC5hQujTW/bYx/SiJXV901t38WEjRgGLjxwa1YHoYzRU4z4Mt9r7clRCOTbsnjPSgk+iZvEeIX3RXMYhYPOZNVWd9kFbkHQ9GBag==
*/