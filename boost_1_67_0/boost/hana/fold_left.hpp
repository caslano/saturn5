/*!
@file
Defines `boost::hana::fold_left`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FOLD_LEFT_HPP
#define BOOST_HANA_FOLD_LEFT_HPP

#include <boost/hana/fwd/fold_left.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/variadic/foldl1.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename State, typename F>
    constexpr decltype(auto) fold_left_t::operator()(Xs&& xs, State&& state, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using FoldLeft = BOOST_HANA_DISPATCH_IF(fold_left_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::fold_left(xs, state, f) requires 'xs' to be Foldable");
    #endif

        return FoldLeft::apply(static_cast<Xs&&>(xs),
                               static_cast<State&&>(state),
                               static_cast<F&&>(f));
    }

    template <typename Xs, typename F>
    constexpr decltype(auto) fold_left_t::operator()(Xs&& xs, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using FoldLeft = BOOST_HANA_DISPATCH_IF(fold_left_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::fold_left(xs, f) requires 'xs' to be Foldable");
    #endif

        return FoldLeft::apply(static_cast<Xs&&>(xs), static_cast<F&&>(f));
    }
    //! @endcond

    namespace detail {
        template <typename F, typename State>
        struct variadic_foldl1 {
            F& f;
            State& state;
            template <typename ...T>
            constexpr decltype(auto) operator()(T&& ...t) const {
                return detail::variadic::foldl1(
                    static_cast<F&&>(f),
                    static_cast<State&&>(state),
                    static_cast<T&&>(t)...
                );
            }
        };
    }

    template <typename T, bool condition>
    struct fold_left_impl<T, when<condition>> : default_ {
        // with state
        template <typename Xs, typename S, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, S&& s, F&& f) {
            return hana::unpack(static_cast<Xs&&>(xs),
                detail::variadic_foldl1<F, S>{f, s}
            );
        }

        // without state
        template <typename Xs, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, F&& f) {
            return hana::unpack(static_cast<Xs&&>(xs),
                hana::partial(
                    detail::variadic::foldl1,
                    static_cast<F&&>(f)
                )
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FOLD_LEFT_HPP

/* fold_left.hpp
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
*/