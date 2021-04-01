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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MONADIC_FOLD_LEFT_HPP

/* monadic_fold_left.hpp
oYAbvwmiGyLaoYi+H72l9bnJ8685gvs9T0c0+nxpCEeHJCyDWUc+THQkaxY0vJSRK+eszk2PSGlocLZfzwykcwZWMJ3I+lbIeNQN17i70NiQCN0zT+7ez4qmq/Q4TcVmLygOl4ojWVYOpAaBW0Qmga5/wooTAHfaCdX8Zs9pV7Q2nWY+i6NvIeEf64+gIBfBeM9YYQCUGuIu6jAWDzDZln1Z5MYtQvz2Nl4no574mVquXMjgr6YsYARkVEuZmEFbBqGT9T6OE5axpl7poiYh8/w/qb0eg1RTs8J0EWjj8KCL6+m0EjXIaNNKVa/cEye8u45PsbrvANHazeThfDZSMiuk/IOs4rb3eOGiptMs1TyoTzWuD9GrjajYWcp01fi0E/VluP/LcJlNXhhOuciNkQi1fWtfx80i+1gxyLRENrn5QHHDakWa2LEHjCmr0itL/V8VQKKXhmIze0qjt5RlgU2314u6oi91A113rpRmLJ9yYYnlZ+x8oajDCMigAe5wwEMj6CB07NS7bBGtGVwTwah4Z2MSpl2u5RCYHv4zwN9Sv6wCMzbEh4xE9A==
*/