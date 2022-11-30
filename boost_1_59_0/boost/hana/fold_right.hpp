/*!
@file
Defines `boost::hana::fold_right`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FOLD_RIGHT_HPP
#define BOOST_HANA_FOLD_RIGHT_HPP

#include <boost/hana/fwd/fold_right.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/variadic/foldr1.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/fwd/unpack.hpp>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs, typename State, typename F>
    constexpr decltype(auto) fold_right_t::operator()(Xs&& xs, State&& state, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using FoldRight = BOOST_HANA_DISPATCH_IF(fold_right_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::fold_right(xs, state, f) requires 'xs' to be Foldable");
    #endif

        return FoldRight::apply(static_cast<Xs&&>(xs),
                                static_cast<State&&>(state),
                                static_cast<F&&>(f));
    }

    template <typename Xs, typename F>
    constexpr decltype(auto) fold_right_t::operator()(Xs&& xs, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using FoldRight = BOOST_HANA_DISPATCH_IF(fold_right_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::fold_right(xs, f) requires 'xs' to be Foldable");
    #endif

        return FoldRight::apply(static_cast<Xs&&>(xs), static_cast<F&&>(f));
    }
    //! @endcond

    namespace detail {
        template <typename F, typename State>
        struct variadic_foldr {
            F& f;
            State& state;
            template <typename ...T>
            constexpr decltype(auto) operator()(T&& ...t) const {
                return detail::variadic::foldr(
                    static_cast<F&&>(f),
                    static_cast<State&&>(state),
                    static_cast<T&&>(t)...
                );
            }
        };
    }

    template <typename T, bool condition>
    struct fold_right_impl<T, when<condition>> : default_ {
        // with state
        template <typename Xs, typename S, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, S&& s, F&& f) {
            return hana::unpack(static_cast<Xs&&>(xs),
                detail::variadic_foldr<F, S>{f, s}
            );
        }

        // without state
        template <typename Xs, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, F&& f) {
            return hana::unpack(static_cast<Xs&&>(xs),
                hana::partial(
                    detail::variadic::foldr1,
                    static_cast<F&&>(f)
                )
            );
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_FOLD_RIGHT_HPP

/* fold_right.hpp
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
*/