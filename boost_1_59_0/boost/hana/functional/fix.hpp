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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr detail::create<fix_t> fix{};

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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_FIX_HPP

/* fix.hpp
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
*/