/*!
@file
Defines `boost::hana::minimum`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MINIMUM_HPP
#define BOOST_HANA_MINIMUM_HPP

#include <boost/hana/fwd/minimum.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/nested_by.hpp> // required by fwd decl
#include <boost/hana/fold_left.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr decltype(auto) minimum_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Minimum = BOOST_HANA_DISPATCH_IF(minimum_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::minimum(xs) requires 'xs' to be Foldable");
    #endif

        return Minimum::apply(static_cast<Xs&&>(xs));
    }

    template <typename Xs, typename Predicate>
    constexpr decltype(auto) minimum_t::operator()(Xs&& xs, Predicate&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using Minimum = BOOST_HANA_DISPATCH_IF(minimum_pred_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::minimum(xs, predicate) requires 'xs' to be Foldable");
    #endif

        return Minimum::apply(static_cast<Xs&&>(xs),
                              static_cast<Predicate&&>(pred));
    }
    //! @endcond

    //////////////////////////////////////////////////////////////////////////
    // minimum (with a custom predicate)
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename Pred>
        struct min_by {
            Pred pred;

            template <typename X, typename Y>
            constexpr decltype(auto) operator()(X&& x, Y&& y) const {
                auto result = (*pred)(x, y);
                return hana::if_(result, static_cast<X&&>(x),
                                         static_cast<Y&&>(y));
            }
        };
    }

    template <typename T, bool condition>
    struct minimum_pred_impl<T, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr decltype(auto) apply(Xs&& xs, Pred const& pred) {
            // We use a pointer instead of a reference to avoid a Clang ICE.
            return hana::fold_left(static_cast<Xs&&>(xs),
                detail::min_by<decltype(&pred)>{&pred}
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // minimum (without a custom predicate)
    //////////////////////////////////////////////////////////////////////////
    template <typename T, bool condition>
    struct minimum_impl<T, when<condition>> : default_ {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs)
        { return hana::minimum(static_cast<Xs&&>(xs), hana::less); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MINIMUM_HPP

/* minimum.hpp
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
*/