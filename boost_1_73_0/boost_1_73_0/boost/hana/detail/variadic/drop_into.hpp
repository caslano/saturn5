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
8f1bNyR+S5PJXJ6h4FwugOxoN4AyPCs9B14CP0BqQHBzGDxMRQKl/r7ygc/hyiF4HoGE8Vy5fghgEF7gpoBchLON3MDpb/epm/3tXQQmUNBjgoJKLjTVU6CpR8Ry+jvbL4hGoBzCjCW4PQQjyidmhf6ew2Tq9Pu5ukRkc6dzMTh/N7qYnI4nHwZD59Ej56H2aPTh7ejgYHTg/OtfTvb06Oz96cmo26U17kA1fPjnyU+j8/HR6QnA+fNkcHx8+jPU+x568XQHlmYcQ9MbirQ8RxGygzO8BWs3G4OcaNVbfXE3aI+XPfE5YHwfz48nbz8eHR9MjgAROyUvJs/LX70sfwV4tb5DZPZ5NQF1+XJePvuL1cIZnB05ATD8AKmchYgguuU9F1m/wWn2aaqsLUz6O5On1Qh581rMQCmAZw0APKsC8LwBgOdVAF40APCiCsDLBgBeVgGAWayH0O/vVMLYawJjD2Awj008ybQWHopFJKtGSAjIiUhKALJBocdjbkVE4sSrMPVhV8JVA0LWDBc/bYGpf+kHyLJvQWBCOTSAfStl7jaFn7CYPDcGwSne2MdKHRQ+QX7gElCACG6LgGfcEEGDGBTjlwWyrQBHD/Iq8HSEsrEFj6dR8nlLMPqthR9ub3QLRDv+eHZ2en5R
*/