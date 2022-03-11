/*!
@file
Defines `boost::hana::maximum`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MAXIMUM_HPP
#define BOOST_HANA_MAXIMUM_HPP

#include <boost/hana/fwd/maximum.hpp>

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
    constexpr decltype(auto) maximum_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Maximum = BOOST_HANA_DISPATCH_IF(maximum_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::maximum(xs) requires 'xs' to be Foldable");
    #endif

        return Maximum::apply(static_cast<Xs&&>(xs));
    }

    template <typename Xs, typename Predicate>
    constexpr decltype(auto) maximum_t::operator()(Xs&& xs, Predicate&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using Maximum = BOOST_HANA_DISPATCH_IF(maximum_pred_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::maximum(xs, predicate) requires 'xs' to be Foldable");
    #endif

        return Maximum::apply(static_cast<Xs&&>(xs),
                              static_cast<Predicate&&>(pred));
    }
    //! @endcond

    //////////////////////////////////////////////////////////////////////////
    // maximum (with a custom predicate)
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename Pred>
        struct max_by {
            Pred pred;

            template <typename X, typename Y>
            constexpr decltype(auto) operator()(X&& x, Y&& y) const {
                auto result = (*pred)(x, y);
                return hana::if_(result, static_cast<Y&&>(y),
                                         static_cast<X&&>(x));
            }
        };
    }

    template <typename T, bool condition>
    struct maximum_pred_impl<T, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr decltype(auto) apply(Xs&& xs, Pred&& pred) {
            // We use a pointer instead of a reference to avoid a Clang ICE.
            return hana::fold_left(static_cast<Xs&&>(xs),
                detail::max_by<decltype(&pred)>{&pred}
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // maximum (without a custom predicate)
    //////////////////////////////////////////////////////////////////////////
    template <typename T, bool condition>
    struct maximum_impl<T, when<condition>> : default_ {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs)
        { return hana::maximum(static_cast<Xs&&>(xs), hana::less); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MAXIMUM_HPP

/* maximum.hpp
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
*/