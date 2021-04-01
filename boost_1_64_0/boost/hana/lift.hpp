/*!
@file
Defines `boost::hana::lift`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LIFT_HPP
#define BOOST_HANA_LIFT_HPP

#include <boost/hana/fwd/lift.hpp>

#include <boost/hana/concept/applicative.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename A>
    template <typename X>
    constexpr auto lift_t<A>::operator()(X&& x) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Applicative<A>::value,
        "hana::lift<A> requires 'A' to be an Applicative");
    #endif

        using Lift = BOOST_HANA_DISPATCH_IF(lift_impl<A>,
            hana::Applicative<A>::value
        );

        return Lift::apply(static_cast<X&&>(x));
    }
    //! @endcond

    template <typename A, bool condition>
    struct lift_impl<A, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...args) = delete;
    };

    template <typename S>
    struct lift_impl<S, when<Sequence<S>::value>> {
        template <typename X>
        static constexpr decltype(auto) apply(X&& x)
        { return hana::make<S>(static_cast<X&&>(x)); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_LIFT_HPP

/* lift.hpp
B0hWZYDrUH9R5TWksDZA72U2VppFA7PL8k3LypWZ5eiq0fjWi+pOCUPUqBw44yyDKVNl5sF/B822ub2dEBhd0x76dQIdBneAEJwM5LiNfoPRBqeffpOL9l7aBzI7odBEeaDxXhp/GepyJZyKkpoeoXfIo1Utml4TxkjyrliWCi0NjpU6QS2icbRIbyja4+tH2QqfNEG1oXZ39Y83+eZQsqfGopTmtZWxdLzWPHS89YMHU8bRIFqpRgcjkwtrfbXot5n8BaCguXjSwgMWqq+X4GEFIyqaXTFy2c95SrDx0PTIFimB4KEvmB/xlPkI+F9QyuM54A9JafPCymqNClFPcw3MnIKIyojdQlXWXnV+pZ564gEFBwaB1rtMWlmbh08svyK8vlRRxR+PAFenaW+u9vgCuYEDHjtGDPtFTiMTWkwZok8jPPqQq0bfBbYb6Am2jqv0vwLv5wnrhxAv0ce3DC9MPKWdikRfxZHIHls4H2e8U8ozXSFtRpOvXsGLkkfyHZKJCB2El6DbjDG+U3FDWQaH0Pf01tRWcEiUxWKZJHQKptPfVZzjnjkETQ==
*/