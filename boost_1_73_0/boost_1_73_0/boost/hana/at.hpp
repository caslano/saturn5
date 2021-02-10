/*!
@file
Defines `boost::hana::at` and `boost::hana::at_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_AT_HPP
#define BOOST_HANA_AT_HPP

#include <boost/hana/fwd/at.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/integral_constant.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr decltype(auto) at_t::operator()(Xs&& xs, N const& n) const {
        using It = typename hana::tag_of<Xs>::type;
        using At = BOOST_HANA_DISPATCH_IF(at_impl<It>,
            hana::Iterable<It>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::at(xs, n) requires 'xs' to be an Iterable");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::at(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        return At::apply(static_cast<Xs&&>(xs), n);
    }
    //! @endcond

    template <typename It, bool condition>
    struct at_impl<It, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <std::size_t n, typename Xs>
    constexpr decltype(auto) at_c(Xs&& xs) {
        return hana::at(static_cast<Xs&&>(xs), hana::size_t<n>{});
    }
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_AT_HPP

/* at.hpp
KhaEbElpqyRQcpP3UVbtGlCkahYk3bY2hPIp59KvmcnRqiZKclQ0LC9Hrc+iAE3zDo1zEOmx+izwU9EBDSDkzmW0YO4eCxNF62S1nMTPZwWtYQeELnYXCVomcsx84/tcR5TyhMyy2LEtZ2Z7m663io9z3dqa2bvEc1MBM7wNSOndeK0ZPHUlN5JAYdX8spTZV2Yx9TyDVgYbjW2buOkn5BugyKg49IfHUbqD/XFnwBxc0wnbgf1pR81Frw3N1cHG8aDP+F3KAzqNxcYhniwLUB5ggohKGKCTYLbqCgFh8gibOOtoB6x/wWzXxdN1LXEqRiWFs/kCg/EcYXT3jJEWB8VL8F1KgGUBX4BQsupDgpxZfjLRQWyoV16a7IlYFR5qs2w/yrOhtNDzToT5DDlJs8Mm7Q/HphxqWmJiNkBPPGyWppHSK1/JYC9WzbMKla61E33/PcpC0ROGzCfDrFb/RAtcZ3VxVqK3A5UESQALeSqZp0gCjB0jfh0/pKN9nGVzYnYc2/fyTCsetryd3aPcDzh3M94JwYzkEQOz347DReAqKpY4XGhigFQr6/6BFn1hlen412S4KVgHyCdnC+W+Z+0eZ4JzHbEppN80jBtL2ABQfsy+/z5qmiQsjg7bBmYzIzBPEnL57ESFCGDN
*/