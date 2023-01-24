/*!
@file
Defines `boost::hana::prefix`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PREFIX_HPP
#define BOOST_HANA_PREFIX_HPP

#include <boost/hana/fwd/prefix.hpp>

#include <boost/hana/append.hpp>
#include <boost/hana/chain.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/lift.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pref>
    constexpr auto prefix_t::operator()(Xs&& xs, Pref&& pref) const {
        using M = typename hana::tag_of<Xs>::type;
        using Prefix = BOOST_HANA_DISPATCH_IF(prefix_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::prefix(xs, pref) requires 'xs' to be a MonadPlus");
    #endif

        return Prefix::apply(static_cast<Xs&&>(xs), static_cast<Pref&&>(pref));
    }
    //! @endcond

    template <typename M, bool condition>
    struct prefix_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Z>
        static constexpr decltype(auto) apply(Xs&& xs, Z&& z) {
            return hana::chain(static_cast<Xs&&>(xs),
                hana::partial(hana::append, hana::lift<M>(static_cast<Z&&>(z))));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_PREFIX_HPP

/* prefix.hpp
xiaY2lXT77Vxr/TWpFlbJWnlo+mIIcX+21e3QHfAWJiDocOJv+3l2u3DlLPC12LWGrWB26K2TrRHIhEHU+FCorbzV05/sum4aPVwmyWYrKN6OnZRNXu86tFSY6Jxsp3iP2cch5PFtBwUomU5eSne7T4Ul20py0eMAB/stPIB9c/rv5vxCXcvrfon0jflEn5GvAj8nlZQH21/2Ml4ISALCmBt+hSxpPTt+gtFxPPZA5WqH0Cv3bR/hG/jTn3QhOxMjOnBurAX/5pAWKr2c3hBstEKyicG1WkoH9LVJ3wpHmGdRbud+EYg1aRHGGJWeezx2RatU3eQnG5jDnfZwXDMnBIk1m56P9Z77NrocdrreUYSL6hZPjGHvv9soQFl+uEgAOXMptOUypSKNrvsxqHoGasTS5SX+I5RxSR4gULrGR9Rdrj8AXZf7Y+A3MEsn8ee1Ht0c+pst0NYbSKvH6bL3MW5QiCKyOd9flz5C7g/9NmO8TyaeNRW9GIKXP0BM2Wkrpp7rhphplV7r437QKGJ6ZOHsfeFpY5O0GFz2Br511qT7AFIAAYf1xGkl3ore9Dw3dyUk2i2quEcqdLep5R3yp0+cX/2MMjjP/ZWZZoHe0mcwPnDsOiLoL/sjlLwUMjYsDP56mJU1/DiX2MzuF9K0A6tz8vIC4+oGNT0DIYgvNB+ZtI9WchZoDAEL1Rt+t3BTnpWqQQCWSkdNWWE
*/