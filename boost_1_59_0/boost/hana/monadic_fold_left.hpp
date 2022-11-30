/*!
@file
Defines `boost::hana::monadic_fold_left`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MONADIC_FOLD_LEFT_HPP
#define BOOST_HANA_MONADIC_FOLD_LEFT_HPP

#include <boost/hana/fwd/monadic_fold_left.hpp>

#include <boost/hana/chain.hpp>
#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/monad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/fold_right.hpp>
#include <boost/hana/functional/curry.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/lift.hpp>

#include <type_traits>


namespace boost { namespace hana {
    //! @cond
    template <typename M>
    template <typename Xs, typename State, typename F>
    constexpr decltype(auto) monadic_fold_left_t<M>::operator()(Xs&& xs, State&& state, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using MonadicFoldLeft = BOOST_HANA_DISPATCH_IF(monadic_fold_left_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::monadic_fold_left<M> requires 'M' to be a Monad");

        static_assert(hana::Foldable<S>::value,
        "hana::monadic_fold_left<M>(xs, state, f) requires 'xs' to be Foldable");
    #endif

        return MonadicFoldLeft::template apply<M>(static_cast<Xs&&>(xs),
                                                  static_cast<State&&>(state),
                                                  static_cast<F&&>(f));
    }
    //! @endcond

    //! @cond
    template <typename M>
    template <typename Xs, typename F>
    constexpr decltype(auto) monadic_fold_left_t<M>::operator()(Xs&& xs, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using MonadicFoldLeft = BOOST_HANA_DISPATCH_IF(monadic_fold_left_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::monadic_fold_left<M> requires 'M' to be a Monad");

        static_assert(hana::Foldable<S>::value,
        "hana::monadic_fold_left<M>(xs, f) requires 'xs' to be Foldable");
    #endif

        return MonadicFoldLeft::template apply<M>(static_cast<Xs&&>(xs),
                                                  static_cast<F&&>(f));
    }
    //! @endcond

    namespace detail {
        struct foldlM_helper {
            template <typename F, typename X, typename K, typename Z>
            constexpr decltype(auto) operator()(F&& f, X&& x, K&& k, Z&& z) const {
                return hana::chain(
                    static_cast<F&&>(f)(
                        static_cast<Z&&>(z),
                        static_cast<X&&>(x)
                    ),
                    static_cast<K&&>(k)
                );
            }
        };

        template <typename End, typename M, typename F>
        struct monadic_foldl1_helper {
            F f;
            template <typename X, typename Y>
            constexpr decltype(auto) operator()(X&& x, Y&& y) const
            { return f(static_cast<X&&>(x), static_cast<Y&&>(y)); }
            template <typename Y>
            constexpr decltype(auto) operator()(End, Y&& y) const
            { return hana::lift<M>(static_cast<Y&&>(y)); }
        };
    }

    template <typename T, bool condition>
    struct monadic_fold_left_impl<T, when<condition>> : default_ {
        // with state
        template <typename M, typename Xs, typename S, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, S&& s, F&& f) {
            return hana::fold_right(
                static_cast<Xs&&>(xs),
                hana::lift<M>,
                hana::curry<3>(hana::partial(
                    detail::foldlM_helper{}, static_cast<F&&>(f)
                ))
            )(static_cast<S&&>(s));
        }

        // without state
        template <typename M, typename Xs, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, F&& f) {
            struct end { };
            using G = detail::monadic_foldl1_helper<end, M, typename detail::decay<F>::type>;
            decltype(auto) result = hana::monadic_fold_left<M>(
                static_cast<Xs&&>(xs),
                end{},
                G{static_cast<F&&>(f)}
            );

            static_assert(!std::is_same<
                std::remove_reference_t<decltype(result)>,
                decltype(hana::lift<M>(end{}))
            >{},
            "hana::monadic_fold_left<M>(xs, f) requires 'xs' to be non-empty");
            return result;
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_MONADIC_FOLD_LEFT_HPP

/* monadic_fold_left.hpp
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
*/