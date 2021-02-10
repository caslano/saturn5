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
l0GHBO4m86vr2zncjWaz0XS+gOvvMJoumOzHZHpOpdck5gHXtcdA4h70sjYaVaf5fiPtDbQtTKMQ+lw8ETA29bDq92ij5FZym11wn6Am8XLYCiVnp7tKzpoN5AgWUW1z+EBXt2NVkG9gFU0YFm1VbKAVEaW9V8Kkq2SUrWp6RFAdtTT6NwIJ003PvfQb0CVYx9+EJ/kNU3APKxwxjDlyohal8wUKJjigGjTUUNotlIEArHH4pdfDNdXU0uWxIcJrtxDMy4LpyHeAli4lUFRdHlh3Z/y3mfL+H1BLAwQKAAAACAAtZ0pSY26f7LOMAABsFgIAHgAJAGN1cmwtbWFzdGVyL2xpYi92dGxzL29wZW5zc2wuY1VUBQABtkgkYOy9/XfbtpIw/Lv/Ckb33FRyZdmy2zSNm3QVW060cSSvJDfNtn14KImy2UiklqT8cbd5/vZ3vgAC/JCVj3v33XMe9TSWSGAADAaDmcFgZn/36312nF3nwY9L/7vwgb9U4yKO/vSnaXlp1/3L4f+g1u/w96FG9p2syl9uw3m4yl9Onaq40spP+N11H2rod+wb/rOPNX938Ss8gWpY8yRa3cfB1XXq1E8aTvvHH586e87hwWG76Zx6YeAvnFHqhxM/vmo6P83oyb9de3d3rcR/
*/