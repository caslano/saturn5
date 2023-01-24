/*!
@file
Defines `boost::hana::unique`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_UNIQUE_HPP
#define BOOST_HANA_UNIQUE_HPP

#include <boost/hana/fwd/unique.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/nested_by.hpp> // required by fwd decl
#include <boost/hana/equal.hpp>
#include <boost/hana/front.hpp>
#include <boost/hana/group.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto unique_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Unique = BOOST_HANA_DISPATCH_IF(unique_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::unique(xs) requires 'xs' to be a Sequence");
    #endif

        return Unique::apply(static_cast<Xs&&>(xs));
    }

    template <typename Xs, typename Predicate>
    constexpr auto unique_t::operator()(Xs&& xs, Predicate&& predicate) const {
        using S = typename hana::tag_of<Xs>::type;
        using Unique = BOOST_HANA_DISPATCH_IF(unique_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::unique(xs, predicate) requires 'xs' to be a Sequence");
    #endif

        return Unique::apply(static_cast<Xs&&>(xs),
                             static_cast<Predicate&&>(predicate));
    }
    //! @endcond

    template <typename S, bool condition>
    struct unique_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return hana::transform(
                hana::group(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred)),
                hana::front
            );
        }

        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return unique_impl::apply(static_cast<Xs&&>(xs), hana::equal); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_UNIQUE_HPP

/* unique.hpp
sXEzIhmmaRkq9AzvHSE7NMkErhG60h0RXXTXn/fHxDQTIHPvHy5KoIaqgW9J4+Av0sFviAE/OFwHr2+i01VPjk3cxcxNaYt1XTU4ny/t0FinXp334fnG+lM30bZjTPVmxEGo7x4biPOz0nAwKJdxB6EmlpOPG99S60eEgLY+zY/4dgxLIycCy5Sob8ej6eREYLns/6ZvR9plfIkT3qIcqrls3DOzWHMi+PjSWCeCvks1J4LYxJvnn+vfcXMO95L+0aWxi52bb/tPvhudR86H056b/ze+G6+kE9f8Z97Qhc5X07XVbF8RrmbPqf8hov2uJRraO9lPJuMmw/Y9KYh37rsxfhqh/bF0RHsbX81ui1nN3s9Xs+HV/u9ezXafs5rtYn9Mj5X8i3Gn4f5Y3w1kOFG0V6Zrq9kfaFttxbrHyHejU3EcViralQrN/wLE+wzyYTjMfjmZ76fbT4L965Oi86g1XRsRNx8mf75Of0EHeyjBaIDe9DuOkYTuydfAuIaA2RAD5q1pGpgLD2uedb8GGJ6bKGMHScFmETU26VKvGTejYTEmkGrhhpHsWZuAnlr7KOntcB+0ovcjQlqbgD56zHuFmh+CTh4p7lycP1hSntXgswaFkkJMsh4YnOf2KXxXX4UFTUTH9PdAa1B3ckVhz0/jC/z7yY/sL6nRlXnzNG1lvuR9clZsYW9cwl3HPo4ncLrUgBXfT6860au1
*/