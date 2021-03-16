/*!
@file
Defines `boost::hana::detail::variadic::drop_into`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_DROP_INTO_HPP
#define BOOST_HANA_DETAIL_VARIADIC_DROP_INTO_HPP

#include <boost/hana/config.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    template <std::size_t n, typename F, typename = std::make_index_sequence<n>>
    struct dropper;

    template <std::size_t n, typename F, std::size_t ...ignore>
    struct dropper<n, F, std::index_sequence<ignore...>> {
        F f;

        template <typename ...Rest>
        constexpr auto go(decltype(ignore, (void*)0)..., Rest ...rest) const
        { return f(*rest...); }

        template <typename ...Xs>
        constexpr auto operator()(Xs ...xs) const
        { return go(&xs...); }
    };

    template <std::size_t n>
    struct make_dropper {
        template <typename F>
        constexpr auto operator()(F f) const
        { return dropper<n, decltype(f)>{f}; }
    };

    template <std::size_t n>
    constexpr make_dropper<n> drop_into{};
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_DROP_INTO_HPP

/* drop_into.hpp
WLJwl/JWxnIVpHZyYSClxeq8LeYCm1I32lInm63O32x1WiCH+lNCFTRqjUGrqJx+Z/DkGHIbtQK77zjmQW0TPTpktVL2juq2fQP05PnLbWUhYfAirhGl/fiQXY4JeLRh2199tZGyTBQ/zvclNeFYpjuo//h14fdj/F9XktHh8iyEVEPEFKN3flAFnOvXbFuUt72ZiE7RDpS0t3ek5FbHPXnRrwLcxEo76BOO3v3jxPiQIMf1XoT8Vqm2C5J5028=
*/