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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FOLD_RIGHT_HPP

/* fold_right.hpp
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
*/