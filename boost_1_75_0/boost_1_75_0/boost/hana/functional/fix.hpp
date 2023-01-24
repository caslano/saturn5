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
1SJs88t9RtN371To0Vz12my3yxlZYyGbuGi/XIK94IQU+GeFtHT12lzIwdp8D+oer8mF7QoLraSCxBC58q+0pZd5I+KM3muz4bCWDRucFeYJbnPXWmHiABwgsWbqOlzLdpNJEGzj8+juTNrORCJQrjLWLwfuH90vqAlJ33z4Wv506mCLRZww6LAaRKvHQN44g2T706GBR1BO3zLdYYWuwXd9nmYJZwbWQcJgCzp/gjZCOYvQgF4PPRbyALqOhqm8AzWgpwfEm6i9hXjVInpzf5H9/zD37vFNFlnjeG5N0hJIkAIVECr3FVQ0XA23gimoFFNiEy62sK72jdHdRUi4KC3FNGsfxqi7q++6r7Kvurrrru7KriJVuaSU7QUQCvJqEdwtWnVKqhYpbYDS53fOmedJUi7u+37/+vGhT55nLmfmnDkzc2bmzDlVwftgEDv27YlroXOlPQ/8Cxz92ILY/EQofo8XUbFbU0MfHaqEDu0Raha9JKb8Hmv67NrQV90tR7Fm1Tpr+X5RRZu4ieu1yx3VtoB2HsD4THvsWxx2YNCxMurSWpzrRK98EdeAIPvutaRpzpOF888K2o59O+MgIFhissv/rJ8XW/LPY/Yjor9q5zBnx3t65NUma6jOViw5OyC7o6pk3Lg65mzrcLYBW4XloHbeYd7hbNeCtB4w44RfBm+Hf9qOc8Knnznbwkdw0YXSWlZMb5fnheXl
*/