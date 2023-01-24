/*!
@file
Forward declares `boost::hana::less_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LESS_EQUAL_HPP
#define BOOST_HANA_FWD_LESS_EQUAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_than_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Logical` representing whether `x` is less than or
    //! equal to `y`.
    //! @ingroup group-Orderable
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Orderables `A` and `B` with a common
    //! embedding, the signature is
    //! @f$ \mathrm{less\_equal} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare.
    //!
    //!
    //! Example
    //! -------
    //! @include example/less_equal.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto less_equal = [](auto&& x, auto&& y) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct less_equal_impl : less_equal_impl<T, U, when<true>> { };

    struct less_equal_t : detail::nested_than<less_equal_t> {
        template <typename X, typename Y>
        constexpr auto operator()(X&& x, Y&& y) const;
    };

    constexpr less_equal_t less_equal{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_LESS_EQUAL_HPP

/* less_equal.hpp
gYcIBogiTpb9TQza9ahPmu+j4E1eGs3ZpZmTFmcM2kXZkdqh/+D0bwMeyj3ZOtW6MgLAjh28JEjoFZqniopN+GmNvl81vo7b5BO39AcFTkmtR/nUqNZJL/wHT7IyqiAdf4xWaPkgON78XOCZ7sk+iDJ6S+Cz6qV9a4bljDottZW+n9bJn1YFdjglTp6f2COqPzL0hpEF8bWuX9Ail5/a4sDzFMG4yOaCwK4g7Zg+lLqUCusaC944r3d1eWT5olUB++7VT7GnNg8ZXZ/J2zerOfACBwjYNb7JPkYGCjWHxHWoqR/rAaMF5qlOsC7k3JsFaJtMkDfVvjoZRfqDFOG6+ASeCwK+f44CVtRH9/Z5vcBt4y4A82Z8A8cHfB/GsyiM1jenUoakwrooYrUUL0sj+LUtBWMSdvkNoy++IXH5+C9rxfMewNypvjgmgcSMn3zgqLllAvkbbD/LzqCWrplqDAjfcv5qeK6m2nxbf91W6kEfa4YQwecDrfulGXPM9fstE/V2x5kGka7HymixuHzhb+Z/mKcjMFh3RbZC0e8cIgRZI0cMPWtOUwJeWkKNzR8Gwlf6ymuFYiPcpU4GZccuxe4Tocl7M7Jpu4r1A+RO51wJOUSVe4sBi4MWf9lvxJQ0YASnfb1RIL/FpoejnhvaMLjIkaqtsiGZyOj5rvGjh7iUyrDKTYyshjjmHjkUhvNa0ouWgd7yE2Pjs6ef
*/