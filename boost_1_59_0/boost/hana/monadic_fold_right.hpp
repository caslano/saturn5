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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_MONADIC_FOLD_RIGHT_HPP

/* monadic_fold_right.hpp
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
*/