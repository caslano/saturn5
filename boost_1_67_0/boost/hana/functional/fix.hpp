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
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
*/