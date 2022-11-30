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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_UNIQUE_HPP

/* unique.hpp
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
*/