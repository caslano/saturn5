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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FOLD_LEFT_HPP

/* fold_left.hpp
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
*/