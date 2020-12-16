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
S4vICyg2pnIlwO06PK1jgB5tdDEup5aeOMv9wmVdVY2MkB22NRdx32gaDht6AtB5ENQZxfGcjNYPN7bbSW8zeo6MogO97Wy6vrThxMfx4xraZQ9EMTZGCbBOOs8NN3+TTKswTMLa0LSKUxpPHs2z/4bzHKevgUxjL05D0DU4DDzpcl7F4QPoIKtUJkFeMdpsTg8nTsdZvrOPcjyn4yIo8yyRoKsXRy/HmkOzEWGW5mVc5pYmRnNj92hzNJcoiyt0bIP3tSwCv0gqNcaboymCuND7sH0HWnDGORRJFUNLWqZtbBvIlU8+MjQplOwG5VxFm7mNhYz9NElBa306NWqlEcVbcfonRZ2GVZl6crZ/6/tstShMO2ePWMw+h4egS/I96UsBrzqEETfty6x+n8MG4Fs/q/y6IzlFJq/JLuaMcdH0AH+QkdEMVEd3xMc1hnpQmU6oKTCp35gO7lWA5euzajwvzcNM1FNYh/aXCdUnWoNtJ45omjdVgSWgd1e7V9lxFaVr9xX6WZip6CYrtBdzei05/G0sVD2KGers8xn0sima3EiRtrpGnccC/66WaSlbfblxatIac1hMARZ4ulwZLj/XgQyCtA4NPjcYska3s6UtqCyDi4Gkt+ttt22NDJs6DuL5uExLNc5GlmBihYvyIzj9zEVeVWEga7V1Xm4/9d5COem2nFg0gZeVtVcLXFumGPte3kYOGwYiT+I0ybDBrMLyTKfmwaSoTelwRy0Eg4Mmi+xT336O4TlR+EGY+V4mpge9eFvv5HCFqMLMa7wqFmvgcXgsHoLnKTeN7c+HeZ3FpJJ+UtSN0PkODSzh/xSHrURclVLmpSciALsUOvzfPefsiSq9kwxTjMDZJ402euN1RW/PCJKi8aQycDV7hR6wNp+SWbVL7bRtw8i/w/Oc97tnSRFHyjQ8Q76DowkEAXdF8pzLbhywDzjrGs3wUj/3Ip/j6a/s/jn/wyc6Z2CdlHHiYWkzI6yRT28l7j4im6TSr8crGhxDfAmxgtEbl05e7DwNSggL6gzahqTnjvdzOGyE7Sor0yAuKjEZGaHiNNIo67zEIHzgHnvsvE34vltgmCqQ1LnnJ3tQVMMm0qX7KGefjkQe1pFKuVHv7Uy1ja9ZjoEyptzZhbnpaGKOBmctHtvkYwtuL/MI5/xkCsW/4d5Vim3OYVU+kzBt/KCUFBMrKFfRSV2VTr4Bk594/SVsbEVcRiWsbbFbGODVU3Y8HFqeqOvQL4tIrOqg4Os6+RZvJNmG8HqnsYPKrPSV3MKo2P480aERi9zPolA9++1MLqs/Fx1akRf6uUxhy364uzU62O3xyaa7t4NJgji38fCClSJqeyXrgqW8sOHqmD2+4PuY9AOvUqGYbXywFeKPbXffDMs0bjLIRu31lVm1m9QlaAYyBI/29fJgb2M77pyDx4rQi2Ph7T+Vm/+6Ifzgp2ZtIp+ldHaah2fis3+cfObh8kA6i0Fs/Z7eqf3/d06YlM0IA3AwbGcDMdMMzPs0DM6s4VPQm5GCMdAGEr7/5KOvYdtS7LRDthRxrzNtYjDGp3lq63+qV6aRtCcv1f8sg9lqnf82bdmXujJzE+/8Ub/OyrR7txFZud/sdxmMuZFR2Y9ZmdG20jj/XJfp7cCMkoaj8t+wcpYhm3AfG1s/33aS8Skgn7rvwTfOzK+5Bwe2T6/6mZkbjbWbGh5D4IM/cOePA9E9b8x5vgnSLKpCKcBrFb0FV9Y+qezZwdfKFiLKmX8Ozh3jJYA9pB1mlUQXEoP+srMveI6kJ/N1G4ssDYssyRpRKlXDeJdfLg4OtThlrdph9t/Zo3xq7MrVIYSYMPZFigDu59Z3W8Ko3Nrj4/4=
*/