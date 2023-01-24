/*!
@file
Defines `boost::hana::insert_range`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INSERT_RANGE_HPP
#define BOOST_HANA_INSERT_RANGE_HPP

#include <boost/hana/fwd/insert_range.hpp>

#include <boost/hana/concat.hpp>
#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/take_front.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N, typename Elements>
    constexpr auto insert_range_t::operator()(Xs&& xs, N&& n, Elements&& elements) const {
        using S = typename hana::tag_of<Xs>::type;
        using InsertRange = BOOST_HANA_DISPATCH_IF(insert_range_impl<S>,
            hana::Sequence<Xs>::value &&
            hana::Foldable<Elements>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<Xs>::value,
        "hana::insert_range(xs, n, elements) requires 'xs' to be a Sequence");

        static_assert(hana::Foldable<Elements>::value,
        "hana::insert_range(xs, n, elements) requires 'elements' to be a Foldable");
    #endif

        return InsertRange::apply(static_cast<Xs&&>(xs),
                                  static_cast<N&&>(n),
                                  static_cast<Elements&&>(elements));
    }
    //! @endcond

    template <typename S, bool condition>
    struct insert_range_impl<S, when<condition>> {
        template <typename Xs, typename N, typename Elements>
        static constexpr auto apply(Xs&& xs, N const& n, Elements&& e) {
            return hana::concat(
                    hana::concat(
                        hana::take_front(xs, n),
                        hana::to<S>(static_cast<Elements&&>(e))
                    ),
                    hana::drop_front(xs, n)
                );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_INSERT_RANGE_HPP

/* insert_range.hpp
qPlbRc4/qY3K8+XyD6WxihIbBDeVKVVHaVW8krjh4ZpH6uV8Y9DSjRATU7Pz+kffEbw0GLMIfKN5/HyeuhWeUjtgok+MhpYYAy0Te41U3uPEgO9Q8EmGt1YqYBLESGQxXuEfFK4qmqRcLLysHiqqokGZmjKM9zM71CD1I3p3/2iGPI1cSqgmvOtQaineNeLkfYiRx7PL6si7zVQnnzmC7w+fMvVV1fcP8ngeGjBWEs+x0Ov9KpWsuphqwStq08p3NdGCw9+O3OX537uf8E69iL9n8irRo6QY6ibPoMuHkQa8rw3yejXw/pgkI5rLtsRZytvBczSw6uIoRxlVh4mA/7G1V5dGqqJMUpgIzh1sR4lA03geVpkbvk8wTCx/VsT5i1T3Eu+L7kJeUnidW3lcB2/j/1wST5vPcXMfey0nD1F1f0X1r+T7w+cvcem/l/PD5ZvqJVH/68v9n9bsf05bDm9rdt77MTFuViv6tkSwD1a0J+ndJfWfajfHvNtaV9G2sfaM/B2k4+NyCqutsuUiHdm8NNQuaLzSzT1+qapvJhqrfpYB/ye4QzDeW2dU0Yd7pK0QKDMCV6T2LvqI2JEiPI5StZzWIh4nv5q2Xjkc1XsOTx3TlcZvPeH/nnwMh2PcJDYKcGxiWlRyakwMn2R49XXaKno1qs9EPqOgksdAytFQ9gRe1ggIVcJwboqmFx810rvJxMfQZjFmiDfb
*/