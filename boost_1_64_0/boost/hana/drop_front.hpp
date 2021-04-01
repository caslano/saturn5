/*!
@file
Defines `boost::hana::drop_front`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DROP_FRONT_HPP
#define BOOST_HANA_DROP_FRONT_HPP

#include <boost/hana/fwd/drop_front.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr auto drop_front_t::operator()(Xs&& xs, N const& n) const {
        using It = typename hana::tag_of<Xs>::type;
        using DropFront = BOOST_HANA_DISPATCH_IF(drop_front_impl<It>,
            hana::Iterable<It>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::drop_front(xs, n) requires 'xs' to be an Iterable");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::drop_front(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        return DropFront::apply(static_cast<Xs&&>(xs), n);
    }

    template <typename Xs>
    constexpr auto drop_front_t::operator()(Xs&& xs) const {
        return (*this)(static_cast<Xs&&>(xs), hana::size_t<1>{});
    }
    //! @endcond

    template <typename It, bool condition>
    struct drop_front_impl<It, when<condition>> : default_ {
        template <typename Xs, typename N>
        static constexpr auto apply(Xs&&, N const&) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DROP_FRONT_HPP

/* drop_front.hpp
Wltmac6pHqzufb2pRjSYyhxNGjufx3GTK+5nGfTe7BbYzeaLPFOm/pWV3bcp3AvzabO8wZk4X+1+W2UUp5bWLmrbtdU8EILw1+BOJ7tZYYX0pWq2GNPgpldPhYKUkUcz497Y1A+pTWi3J4YipqQ+rIp4VKhrMrrisp7I4eRdK5OS3VawDkVJvYV7VPbsRraIJzWGzmo50UJky1yXPvAmgSv3RT4z2i39kwHKJWRvY65l1S/2fQAUthkIRChnU0RKZ1bJi3abf1utmmc4VF3/pDne9R3fMWu9S5S4/tDX6/jSIXYb1Mb0m9ktpn1+pdOI8bk18ORW0XyfNBq+ERYDcXDGQtraOzoZXfvxeTVaNnaSUJzBXi0pe8vX8HgOp9PobtRGkEumvzqN8BNtoGrn9lOI2QD2xjrnnPL0U0AC5x8RQukOnJIFNYFSIyhPSZs5IZ4nmJOfS4BivgJbMOdUBDLlKmo0f0jY4E7h/bfyym9zWpml1tgHsNcZL2y0jYQf0QT9mTPSGxr35hSz81Ib27PqlBR+gm0NUt7tfFbYZs4B2kWGodkac2hpUw==
*/