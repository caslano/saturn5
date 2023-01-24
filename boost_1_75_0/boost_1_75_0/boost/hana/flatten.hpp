/*!
@file
Defines `boost::hana::flatten`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FLATTEN_HPP
#define BOOST_HANA_FLATTEN_HPP

#include <boost/hana/fwd/flatten.hpp>

#include <boost/hana/concept/monad.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/unpack_flatten.hpp>
#include <boost/hana/functional/id.hpp>
#include <boost/hana/fwd/chain.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto flatten_t::operator()(Xs&& xs) const {
        using M = typename hana::tag_of<Xs>::type;
        using Flatten = BOOST_HANA_DISPATCH_IF(flatten_impl<M>,
            hana::Monad<M>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::flatten(xs) requires 'xs' to be a Monad");
#endif

        return Flatten::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename M, bool condition>
    struct flatten_impl<M, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return hana::chain(static_cast<Xs&&>(xs), hana::id); }
    };

    template <typename S>
    struct flatten_impl<S, when<Sequence<S>::value>> {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs) {
            return detail::unpack_flatten(static_cast<Xs&&>(xs), hana::make<S>);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FLATTEN_HPP

/* flatten.hpp
A9YWJFHt2WrHWlJUiVEPeUkeaybcpSJS0e0FaXJX3GKKLih2mqWl7qvy/oAzqkISDljPmM4m4TW2m008YRma1JyduHBgsVe13+KoEC3Sy+LBfwpp3Apr8HIy7mD/tbkKBqshmQ9+41rbLKZ7K07aKQGsbK+SYyJ3hS5EAY35kxrY4p98PUajAyaLZg0+HU70OqyRq9F5THltWAhQYFKi5gqQvisnDFi7VeRP7AMXwdgHpcKngFwF3HwxVxsqFhqoDR27XaJ1PVKnxCzl96w+efguBfF2Q5wKMwyBuOAgC4z7TUQ7/OLvphc0o2LdA8YjDIuEN3bKNmlsjiJ/KsyCqyJueOMnI5tJLI9PWbLZhK8LWtNTGrUeYKQrZELVJi+EK7efGkG0i0X/IcDlMwCO0iRHYCEsXyEoTxbgAhZs4p54T7cY5PS3CbhFirNHgzwfjD1LE+wO/V43wtHNo5OOGqW5OEvLXV0V1F4R3rp+ytd3Y0z52gpok3i37oIpBSx/P0hBgzPSZs8iu5jrLI4wDDi2ZmndOrjvv4b6GRjqGFYKkZTokEgHavkzJ+jWGnuCAOKv2B2yXz1Lz+cpK07pYTrkMCyWJUoXEHYytMA+Tku3CgsCjQk6Tz73+KNfuX+3dFft8ekprAnPvUW82A+YqFSYNrG/aEaSbkjiuFNqpJP0Z3ukCYyIFmVZfsfKQfxSCvHKoM/L+3XJoOS/
*/