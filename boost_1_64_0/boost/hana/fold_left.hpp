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
P8JAQOU1jNdubJPolj2W0aRMZGlEctsBeurpiRiKrvh5JrUouGKTqOvVZMXpZEFUgl8JnueKISTw5dRs/4CwRKtLbyybGmGIz15qhKzKHE3gR0P2dnaELJlj5QeI8pARDW7IQ+/yxTA7hsHHTvfLHld/+IU1OZxjuYt6Bmh7xvc8JPCdEuyVGPmdI2jFQpWVGMtwKnAPU2p+nn9VYqV1GzuVnJXMptQiZPS9+V86+w0VEsedoXPgcZe5WZJ3QYNNgPPOlAjKRE80QZUgvFbMdkINtnhIf9CKKmkh+neoirQMFeqUQsRdFHXmARt+KEubBMZEO0UIAYe2YOliktsezijN9Kk+x8K/1D1+0HlpyqAjFkE/+9797cZJf2qkSlmK94gCQzliAf5TwpBlLDgSiJpf2lCQdMisl2+i88CVX8pDZkn0mlPMnl5hbk66WF7sJU9OPlgeQY3MRCS17cuwzCCTDFUR1A4HjgtBQ5zx0P01kW8lcMN0M7Pdgw00tLYNAh/S90o6GeH/NV3IBx7lyaQP2LtsYwm0mqIKHuKJ6J65Fb7gtbNBnGuAyQ==
*/