/*!
@file
Defines `boost::hana::lockstep`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_LOCKSTEP_HPP
#define BOOST_HANA_FUNCTIONAL_LOCKSTEP_HPP

#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Invoke a function with the result of invoking other functions on its
    //! arguments, in lockstep.
    //!
    //! Specifically, `lockstep(f)(g1, ..., gN)` is a function such that
    //! @code
    //!     lockstep(f)(g1, ..., gN)(x1, ..., xN) == f(g1(x1), ..., gN(xN))
    //! @endcode
    //!
    //! Since each `g` is invoked on its corresponding argument in lockstep,
    //! the number of arguments must match the number of `g`s.
    //!
    //!
    //! Example
    //! -------
    //! @include example/functional/lockstep.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto lockstep = [](auto&& f, auto&& ...g) {
        return [perfect-capture](auto&& ...x) -> decltype(auto) {
            return forwarded(f)(forwarded(g)(forwarded(x))...);
        };
    };
#else
    template <typename Indices, typename F, typename ...G>
    struct lockstep_t;

    template <typename F>
    struct pre_lockstep_t;

    struct make_pre_lockstep_t {
        struct secret { };
        template <typename F>
        constexpr pre_lockstep_t<typename detail::decay<F>::type> operator()(F&& f) const {
            return {static_cast<F&&>(f)};
        }
    };

    template <std::size_t ...n, typename F, typename ...G>
    struct lockstep_t<std::index_sequence<n...>, F, G...> {
        template <typename ...T>
        constexpr lockstep_t(make_pre_lockstep_t::secret, T&& ...t)
            : storage_{static_cast<T&&>(t)...}
        { }

        basic_tuple<F, G...> storage_;

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) const& {
            return hana::at_c<0>(storage_)(
                hana::at_c<n+1>(storage_)(static_cast<X&&>(x))...
            );
        }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) & {
            return hana::at_c<0>(storage_)(
                hana::at_c<n+1>(storage_)(static_cast<X&&>(x))...
            );
        }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) && {
            return static_cast<F&&>(hana::at_c<0>(storage_))(
                static_cast<G&&>(hana::at_c<n+1>(storage_))(static_cast<X&&>(x))...
            );
        }
    };

    template <typename F>
    struct pre_lockstep_t {
        F f;

        template <typename ...G>
        constexpr lockstep_t<std::make_index_sequence<sizeof...(G)>, F,
                             typename detail::decay<G>::type...>
        operator()(G&& ...g) const& {
            return {make_pre_lockstep_t::secret{}, this->f, static_cast<G&&>(g)...};
        }

        template <typename ...G>
        constexpr lockstep_t<std::make_index_sequence<sizeof...(G)>, F,
                             typename detail::decay<G>::type...>
        operator()(G&& ...g) && {
            return {make_pre_lockstep_t::secret{}, static_cast<F&&>(this->f),
                                                   static_cast<G&&>(g)...};
        }
    };

    constexpr make_pre_lockstep_t lockstep{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_LOCKSTEP_HPP

/* lockstep.hpp
0c3EZhYX97s7/zVY3vT193J846baPjAYxmy76SfdwybzUTNxl6EjeIbVxtIqvRAeeeAof/Mh2p9V0T7zEPJCM+3qoEbdK9hkx9kZQtIMDZyCZPWVkHzjvIrk/T2QfG5cEsm5D6cg+ZUhiSSMpL80wmcDiHWj2L7I+gTrHQJBqnkRfxAp0ijwKZih4lONiHzhB0Sop/hln7Zbb7v/ZZx0XfmVY2E04PJDKRqlrW6PFzin/f7fYxLpgTYpcuBbWusDriXoNkoK132LuqKt38FMJEX4d3gnq+FbvOh1FJ9bTsCT9+1D3tkqEMlIGINcShY+9QbFOkxGZbpGV9byGV5oplJ48XD1VU1c31vAwUMx63YCFOJma/kSHM95urXcBl1nPtmjRr9UN56dBenCq/Wom4oQUvuotKUJs1fp8rG1IviBHYvjiUwss/K2WXoQ7MKIkP24FCa0t2Ei6HJrynYiNE2EfgI5sFgaC4P5ZmvZuXuD15RNnRDs7aoYKgJZPDa4oo/1XRQWV4rzhYzceZtN0MTpFcZ5uWWzNMHdLIIkK66FNpWpEJmox/+ejdq4GABg9P4+yyPh5m+FNadf6hApjOKvAL+3bMIdpTPStkYkFyFb6+zCI6lUnBUWJMIp7cCHxxVGtFYgE7OdGKzw47VenvYjwY99gB/fhnECmABY8hpvJIIlcRcWS4X69Ye/EwV786FZj1zEkebuSKQZ
*/