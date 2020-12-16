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
G0r/2hbA9pwjRoD3+4jBt6L7pfFJdYdgh/EZ6zswHxmBPSxCXPMpuQD8URNiu3LENwfw8cOw20cX89vAyNrX71DfdOTiS8b2Q+KxZ7Hf3PdVdmKrT4j/K5MnYn4x9jfkiphmGPJ7gPzRecpkLsqYgwLgYEFbtvbAFmBHnnwHOSBevfgdz9uInFB3xaGOxMDn5kHYJuynPYD4JIqYuyp5G659OI4YITe6+hX7TNsg71McOdIf/rzON3NDmX/w/MvEHS+XJG6qgI4zb/bH981CP4OYb+QmN1ASH14GWYiYjU8/Cl+xLf2oc2Y0svYz8/zPbbkeb8tnyHOzIbYUYv615TlsTSBxTQIxzGT8YDC6VBLfSP31P8bnwv8PsN1liBsi8eGDrzFPPABfahIzrSLPgZ5MXMic8gTyXRx/g22qTD13oc/4jniRducbwVx/Azxdz9jT/w0hxKvMI95Ef8pSdzgxUGX0dwp8nASmg6nAXRucCeaAWfq8AOwBR8EpcJs5RxvmwxdDmB/nc+SLv2Nnj1MGXgcXRn/w/VZ2W3Zswm/WJq4hV/Qe899y5EwOdUa+etnyIjL095H42enk6Vi1GcYcJDvtzvo1z8xoSxxxx6DqjpSryhhjpyqNYhzJK/Wsi20hvn47CpmCt3+vSM5orSXPbLBld13sd0FLquKjixRT662zyKGkr29L58yMK7x0qlAeXcsH79bD04GNmX+jz+EvEDM8zzORmxen2fIEOdVu2MPC7AdI8MNvUM7Pnb8gc5s/wLZ15R5kW07YUn8h8yNi2m0x5BqI6/ogix9EELsQj+YrhH9tjq9mXlJ3OLkAckHNmMtuGEB7ia83Ma+8Bi+nEJdfp3/V8OmTalFfFnzweHwwSY/XZmAr22HLsYNrOhCbQv+K2G9VJHLhj38owTMX2FIQfi3Yy1yL+VLxfvil09T/BjkecoKH6tKO/rQJW+budegO3P0D/P4ez2bswWwwFywAS8BKsBy4/ng6qFeauTC+p1Z7W14vi78p4EjRDMQsnyCDbfGVAfgtmzHHT5XGT33fwMGoY+9rE7Pz/KVfMIc4CY+GOGIXQ5dyE6OmxwY8hT4Tt/rPxmcjW9HpuRd/trYPsUEpbPl5ZA3b/kZD5rz78LPE4J82J3dKjvFx5pKxg+ELujsKfe5ahDioM7ZuJTpHnqIH8vNINUcmhTE3JD8d0Zh8yhpLisfB74a2JC6DT/WRySrIGM8q7Y+sYoNX0T4rAV7nwx8txj4z3u58/Kln4TMx9fwFjnTGtkcvZY6NLXyVWK1PN0dujMFGufvjWyCHyOpmfFbPteRTJmIHKL+QsS4bT15xJeNEXHduLfLzMrnmcsgs92WtQqyKHazyBD79R2IDx5Zzt5l3hBJ/XyW+CCKmpNzGdfzuHnO/Jh9is5HD28z/RmIrTyy3JF9xaLS1wdvEx+QjOiwmvt8PH+OIzVrgSxmbqduI9a8jx9STtRc58WD0kznI8kIAG92WOsJAOIgEbUAsmABeAdPBbPAaWACWgeUJxMTMW4bip8LRN/8uxHPb8EvEcrHYv8b+xNITmbc8bdMZ7Box9+UhlhwOI27vZ8tF4nTMoi/mHjLIknrvMs7z8Ll/45lXyLPH4jMTLIlvQ4z1JvEV+e482Iq5xHY1GIfSMdhxZLJEP+ak1RhLYuj4t/CvxJA5PifnUR87A80qZcsc/GKnm9iPHawF4C/Lf8lcGJ0af44Ymbnctz8yLs9hg9uoHEez3fiXDuhVDmxgJmL0M9ippui5G3+HEg8TQ//wB/b6Q/L62P+/OcQb5NTfoK1fE1NOzEu/GxB/Ya/drzBUSkSu0PUxwcSQTZjfZEK3yME0YJw=
*/