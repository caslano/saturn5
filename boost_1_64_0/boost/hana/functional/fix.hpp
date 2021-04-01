/*!
@file
Defines `boost::hana::fix`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_FIX_HPP
#define BOOST_HANA_FUNCTIONAL_FIX_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/create.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Return a function computing the fixed point of a function.
    //!
    //! `fix` is an implementation of the [Y-combinator][], also called the
    //! fixed-point combinator. It encodes the idea of recursion, and in fact
    //! any recursive function can be written in terms of it.
    //!
    //! Specifically, `fix(f)` is a function such that
    //! @code
    //!     fix(f)(x...) == f(fix(f), x...)
    //! @endcode
    //!
    //! This definition allows `f` to use its first argument as a continuation
    //! to call itself recursively. Indeed, if `f` calls its first argument
    //! with `y...`, it is equivalent to calling `f(fix(f), y...)` per the
    //! above equation.
    //!
    //! Most of the time, it is more convenient and efficient to define
    //! recursive functions without using a fixed-point combinator. However,
    //! there are some cases where `fix` provides either more flexibility
    //! (e.g. the ability to change the callback inside `f`) or makes it
    //! possible to write functions that couldn't be defined recursively
    //! otherwise.
    //!
    //! @param f
    //! A function called as `f(self, x...)`, where `x...` are the arguments
    //! in the `fix(f)(x...)` expression and `self` is `fix(f)`.
    //!
    //! ### Example
    //! @include example/functional/fix.cpp
    //!
    //! [Y-combinator]: http://en.wikipedia.org/wiki/Fixed-point_combinator
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto fix = [](auto&& f) {
        return [perfect-capture](auto&& ...x) -> decltype(auto) {
            return forwarded(f)(fix(f), forwarded(x)...);
        };
    };
#else
    template <typename F>
    struct fix_t;

    constexpr detail::create<fix_t> fix{};

    template <typename F>
    struct fix_t {
        F f;

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) const&
        { return f(fix(f), static_cast<X&&>(x)...); }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) &
        { return f(fix(f), static_cast<X&&>(x)...); }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) &&
        { return std::move(f)(fix(f), static_cast<X&&>(x)...); }
    };
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_FIX_HPP

/* fix.hpp
NoBcvGDWcwus9IVqP7x7S+W1rfk5cHSZORaOiCvNYnaX3Ph0ASbp4lIO/gAvETjke82sbtB4thvOLgPRQWhnbwki3FPiOgEX7GrqD55jFJRo9dE7pPNeSxa0fyb2ulzO0a2TN39Ixd7ELhxZ8CauFbNbTzogy2LruCXvsDeepDK0pgRQ/d7/Ou9ui7dTNlDwEUZ8ggDEiMYzoI7soaQJyFjFUl+xFLeDyM0OENXIiD/4q+eyf4f8qO9AoDTwkVepIgHc4TwrXBmvCeu32S5qukkpwA9rsovtdJ0s+q80bv0qGahplHbto31sIonAPnO92VfX6S9O/5eG6jb1lPOLbbeD+SRH5OUI+WgF2LCy5ymgkdOYC9rpoM4zQKvMXl1ZfHV+h5fCESvyY6nv8/cZmgLDjQVVfCG54UVQo5uJIw0NWPFm8+yFD1DfCrFIDB0SLDWP5bOC8Z/cJ4ZVhXPKR61SYO47KdUdfzV2Ufaqqk6ZHQXb+zyvQVXsN5a/pUWeYhCZLjHOFvJqSUOua2qEDUr0v8W8T9NW7Q+Pwvu7pvtUHwLyEJvrL22k7A==
*/