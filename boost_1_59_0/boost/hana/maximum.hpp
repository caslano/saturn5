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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_MAXIMUM_HPP

/* maximum.hpp
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
*/