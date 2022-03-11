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
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
*/