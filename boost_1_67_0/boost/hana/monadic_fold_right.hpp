/*!
@file
Defines `boost::hana::monadic_fold_right`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MONADIC_FOLD_RIGHT_HPP
#define BOOST_HANA_MONADIC_FOLD_RIGHT_HPP

#include <boost/hana/fwd/monadic_fold_right.hpp>

#include <boost/hana/chain.hpp>
#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/monad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/functional/curry.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/lift.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    template <typename Xs, typename State, typename F>
    constexpr decltype(auto) monadic_fold_right_t<M>::operator()(Xs&& xs, State&& state, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using MonadicFoldRight = BOOST_HANA_DISPATCH_IF(monadic_fold_right_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::monadic_fold_right<M> requires 'M' to be a Monad");

        static_assert(hana::Foldable<S>::value,
        "hana::monadic_fold_right<M>(xs, state, f) requires 'xs' to be Foldable");
    #endif

        return MonadicFoldRight::template apply<M>(static_cast<Xs&&>(xs),
                                                   static_cast<State&&>(state),
                                                   static_cast<F&&>(f));
    }
    //! @endcond

    //! @cond
    template <typename M>
    template <typename Xs, typename F>
    constexpr decltype(auto) monadic_fold_right_t<M>::operator()(Xs&& xs, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using MonadicFoldRight = BOOST_HANA_DISPATCH_IF(monadic_fold_right_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::monadic_fold_right<M> requires 'M' to be a Monad");

        static_assert(hana::Foldable<S>::value,
        "hana::monadic_fold_right<M>(xs, f) requires 'xs' to be Foldable");
    #endif
        return MonadicFoldRight::template apply<M>(static_cast<Xs&&>(xs),
                                                   static_cast<F&&>(f));
    }
    //! @endcond

    namespace detail {
        struct foldrM_helper {
            template <typename F, typename K, typename X, typename Z>
            constexpr decltype(auto) operator()(F&& f, K&& k, X&& x, Z&& z) const {
                return hana::chain(
                    static_cast<F&&>(f)(
                        static_cast<X&&>(x),
                        static_cast<Z&&>(z)
                    ),
                    static_cast<K&&>(k)
                );
            }
        };

        template <typename End, typename M, typename F>
        struct monadic_foldr1_helper {
            F f;
            template <typename X, typename Y>
            constexpr decltype(auto) operator()(X&& x, Y&& y) const
            { return f(static_cast<X&&>(x), static_cast<Y&&>(y)); }
            template <typename X>
            constexpr decltype(auto) operator()(X&& x, End) const
            { return hana::lift<M>(static_cast<X&&>(x)); }
        };
    }

    template <typename T, bool condition>
    struct monadic_fold_right_impl<T, when<condition>> : default_ {
        // with state
        template <typename M, typename Xs, typename S, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, S&& s, F&& f) {
            return hana::fold_left(
                static_cast<Xs&&>(xs),
                hana::lift<M>,
                hana::curry<3>(hana::partial(
                    detail::foldrM_helper{}, static_cast<F&&>(f)
                ))
            )(static_cast<S&&>(s));
        }

        // without state
        template <typename M, typename Xs, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, F&& f) {
            struct end { };
            using G = detail::monadic_foldr1_helper<end, M, typename detail::decay<F>::type>;
            decltype(auto) result = hana::monadic_fold_right<M>(
                static_cast<Xs&&>(xs),
                end{},
                G{static_cast<F&&>(f)}
            );

            static_assert(!std::is_same<
                std::remove_reference_t<decltype(result)>,
                decltype(hana::lift<M>(end{}))
            >{},
            "hana::monadic_fold_right<M>(xs, f) requires 'xs' to be non-empty");
            return result;
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MONADIC_FOLD_RIGHT_HPP

/* monadic_fold_right.hpp
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
*/