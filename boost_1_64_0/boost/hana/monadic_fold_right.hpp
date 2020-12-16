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
yhpn+rhPeQ+dNmHPj5KoKdJGVAemNa7AzH2jTgnmR+HgKVR+wSYuikLjOZwvC5tOop30/o0V5sqHDTgpzEu/hwdioTEVYQjZV5242LfzOB64+bo9vyrzohbz28UFhxHZ66Fdjk2qLLzKryphrmamIzwP9W5m5ajKtVNJlFthnEXCV66QO66Aj3+5AsHk9AvoXu60oxaxnxdlEzbGNwdDZOPvP+y4WoQkmZDJRIfrrw6uUkRFFuVVHJn8AC0yLgejKT2/peCBtl0T9x4bVSofCoSmeTxk5Cyye6vcXIEZjrNESq/vbzRfsQI2ZH16lIMrFIHv53mSxBaX2c8uhU2Pj2/XxtTNc5l6SQVhvM3lhq6YQ3VytLGBMd462u3GeMOeeZ+funJBEha4phcBxzHHsVOQ/4FTv1Kyi1dUhe0ONjrVF7ZxTA/6rmWBlYMGR/wOndReWCRBjesIuVQyo05mX3GjI/ce46dVWfmJvmfMq0pxuHm9WmRNVKVp3djLxmxVZvP0nN48Rn4elX6QtmsGe9p/WzTgTfKtfYg7B0HpyTyZGURCe6pn5/nO3vqNIU9nRRVdpp2ZOs+UndlE2SPct7OTqLjtw33JJmJV2y4YWJNPbEW2X813solo8tN49GPfjQ1EVeM5Ta4wPNcx3x8hV5BVjL6bfBfmVsHwXM9+lytrq+z79c139aDI6d7AfA/lmhckOO/N9xua7+0Fwmt4nRvpMnCTt/Jo/v3Gtk4ar/LvN2nHZw1vnuWAjdtN9fcU53hEsDczOPRXhuPm+ruSkSEdMxy31t/Xao73NvpbtFKX3bfbm/mAboNw3lF9M3GGeHvv3H7HCOpccPT9L9fS32tMUWXzidzvjvPlW3ojwTvlfc27uNJeDvibyxUoM/U2znbvCseuTd/pXcHy9ParBq59cInbvRfXPX0TBAdKwKtUTGWrkgnliskpSTqi3LVrjaImyZK0UYqdy0CIH7r7zV9zN55AUad1hBUrmjZfFZYZ/rJpFnd0iuApNlCzhzR2/7lV4fq050WT+HVumtQ783v60gVeN8C+Xfl5WZSFUV6avcJej9sMTJvUKqZLvK8bxzTHgVSWrX7q4rR3D3fai43WS9PEywKxOjKEul6nIdrPkej3K7PvPlPzEUCHO2TdwORs/4eUywqBjZSYPNi3ZUlXhsuSW3ZK37EetbRwxqZ/6sqab0F2J5qa2/bvbmOvfXVGdkeIpeGqXF1N62qwbeGu+jVHfu8Dkpx/Ex1HiJWYIFaj0SHFCrvVDAyUKMdV28yowe7Q3lnu0IdtA/zs2PK7f61Xbrpv231XVp+Vq4fq3YNzg4sWz337eNoQMUOKk/J1c0d1et2Vv0GXY8p65RQ3o+jZCYd1HJZlIoK2yyYuwe5Bl8t46luduVM3h/zmqUCeJDdNTE5vLDdiPIOk0885OFKRlGGSRl4J2b232MZQuEGknJNH9vNFL5ZIiGYU0nNiiYA9FBY2CjPxOH7t4ImFH0Hqj2o5D4/i6L5f1KDsxaeXcVbIvOH1tSv3vGaYM+Bu5jw2e/2j1hSvYa+/760usUaNbc/KzXReSOA1hwrLL3lvlD/VlK+sNcNmpV5DVirQVj+qc4ZSSGp7nBe2sMFaUceUFNPQeRmjU5dNV9GUv7bfDgahbHKee+uB5saDreGFg51NbRf0TlMnWCNqGtd7+7hMse3Tx/5jn2gANI0vMhrmu27P12FLgtVj26Pp/s7tIxvJlu6//iNd00hD9yo3t3TNQJi+XePmLo1+7tHr35zPgWmAGeMh6F+CuK57E1aXDX9nW4O8YfcZKEYcGmai8x8MhjJnT2bvaVfh51IOTXoVJPrdZH8mx+I4YbA=
*/