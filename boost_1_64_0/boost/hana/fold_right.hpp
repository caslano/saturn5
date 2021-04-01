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
aX4WVXvGu2PbSbeil+sWepiJoAnuSRB/ehqQlUA0CDf/Hy/SxoH9guDcZCD31EFl9IQIYSYTl8Lyx8h9g2HJG1plzfJIiubdijS1/mBcF652l+p0sa19x5pPAHuQcasqidsJRKBTpgccXM73MndCSPqiSjmeJOmykLHhlj0pgiRPtZd4RTh3JeBEPKciFW8i2IT6cKmkAxDaH5WqtXRkkeOE95uNwCDLeiwU3MeAR5Y9obqOz6SxTvOPMk4F1yTeDxXAgm34SiEXPYps+qY70tNKc3ebj7nZW/kNx3EnCvHYXwMbKWGzuGBQ9o0SPJ15MZIlHuZDM/L6ETLSCQHUCIFjp+UOTF/H7Jq5rKPxQbF3a6ehsHYiO73BwSjjWsgQZ5aGDc6Qee1989bQINrqROpQGz/TZAqRYg6i8vlrSqX8Fs/7VwUkSbCtKmL2WyzlSaL2VXTAD4vtZdxobxmmO9fwmGwu7XXBNvUjipqSE7TdGdcCndIq9C2kSslQs3PsVihXuBwBpLnTTUXNwcGk1cBtiF6zJJf5tCMhiZRh25R66PC2Fu/+qow87Q==
*/