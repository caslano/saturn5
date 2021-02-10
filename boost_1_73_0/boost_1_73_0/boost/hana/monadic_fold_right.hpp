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
ApW13w1BkdtYnUpU1ic71/lg8ObyYiMUo1zp2N+PcD4qx8+vy2r+Z3c4gCGOL4f9qtpGkcpxnAz6fRDyN45BylTC6JycdC82g+AitWNLscyXGb3vnzSq2sCXm5vAEjUtxj7UkPvvg5cbG8MCDzeIpbZqtNsZnr+vapBebmyMSmQNOUpjrKgEgsuHMLoNa8yKP5K9Z8il+EAQHaKADc7JugqLX/E/emuKaswVSFZT7hB1LRYtIoBBz5pScLKew04R/MN3U/rDbAN3QPqBvcUywBe/+f3gm2MtRZeZB6A0HoYQfJc77Ib1+ho40tGhmzakYd2kseWW1CstrbYo6SDswG06YMc+qq0YIIS4HVJNBuP87NQuGcU8/JrzzKn1I/nR0C1gfaj3GwHfc9p/6IHjvOzoqYMyx/Y0ySmx55AyGoB6eKe9ceBxmMxh1yLXHu3yxoWmUBN0IRLPaTNU8pJ/x8clDdoI8WliPrUEdGT6NOckRsNfLONSA6yT8G6QFcYyAsooC6Pdax9rEaisxE+ZzFMJwxgB7NbSjYMmWUCK/4r8oXFbDvYT0C2eSihy/OsQjo1ui/CsbBXCjRIVCLdgfD2EZ2A/AeFJNP1AT/41qNbNbYvvXIUqpOeLVWC+CG1r9Gvx8KFpyLVBc2EM
*/