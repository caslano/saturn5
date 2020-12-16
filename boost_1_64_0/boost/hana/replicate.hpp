/*!
@file
Defines `boost::hana::replicate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REPLICATE_HPP
#define BOOST_HANA_REPLICATE_HPP

#include <boost/hana/fwd/replicate.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/cycle.hpp>
#include <boost/hana/lift.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    template <typename X, typename N>
    constexpr auto replicate_t<M>::operator()(X&& x, N const& n) const {
        using Replicate = BOOST_HANA_DISPATCH_IF(replicate_impl<M>,
            hana::MonadPlus<M>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::replicate<M>(x, n) requires 'M' to be a MonadPlus");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::replicate<M>(x, n) requires 'n' to be an IntegralConstant");
    #endif

        return Replicate::apply(static_cast<X&&>(x), n);
    }
    //! @endcond

    template <typename M, bool condition>
    struct replicate_impl<M, when<condition>> : default_ {
        template <typename X, typename N>
        static constexpr auto apply(X&& x, N const& n) {
            return hana::cycle(hana::lift<M>(static_cast<X&&>(x)), n);
        }
    };

    template <typename S>
    struct replicate_impl<S, when<Sequence<S>::value>> {
        template <typename X, std::size_t ...i>
        static constexpr auto replicate_helper(X&& x, std::index_sequence<i...>)
        { return hana::make<S>(((void)i, x)...); }

        template <typename X, typename N>
        static constexpr auto apply(X&& x, N const&) {
            constexpr std::size_t n = N::value;
            return replicate_helper(static_cast<X&&>(x),
                                    std::make_index_sequence<n>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REPLICATE_HPP

/* replicate.hpp
7fDRDAOur0DibG3H5gjyJeq1PjPyaWp6WfV1B/VlIm6EFgEGuU0A3vc+M9JrWdcoyVtaOSpYfNpU7jmGuCIZj4a1gjcgr+BbVnhAwzCZSehGh0uGNgcZn5o5H2ChLQt8ywoC28FvQr8Zl1eNrcuuSeX1uXH5kY/PZzNcq74Ssmo5g0+PH3w7fe9Dnx35p1Ztq8paM6gG5Z6I0jl+izwMZbM7g/LL0f3X9tT+jKM4pnXGTzG46jhpRMU60LniRQBhYjYi4my8hRBdacanZLJyuhamYvdb3d2CLweFQbwLn/DULigrtrKHSRL/IOOjGbBptLNVmA9oq45vcyFwIV7MaAw/yqdjSloh6sKyqDSnYUuPYUweKJPFLjbciE66VCheW/BBB7qEvndon055LNWybrrG2QG5BzaaVCfqwv5M6YMJqqtkAIqADhYj8DyCIXj5z2XlassLVakAETS3HL630nIlTFAplJYt+MX5cNPhsQpYQEuxd9OyR7Ky0EZheC+7nt6raC9pvXVWVrCeO9MURcNOwIEKugfwjQGpaoLFs/tcVhb6WAkDm0SJcwvs2mJYCmh/4BA0PeQDLeK7W8arYUKLEk60hgESSYdsxrbiwkY+BWJofi6Pk1gqbsG5+0jcsfCXsT/CG7P6NbOy9FB+GorOW/1HokkB5bWYxvRjGa/C24hZIbtqPq+Rn3ZWVjErGsU7Sfz2/YD02/lkEnb8bX6T9yfo/Ppe65yPBFSaRx3EajGtHbef4QgqW9u2aRmwCH9Qv4t77ucze8WuqyoOM4quS4Y4em/NeRfWigItQrAA6o4PUd5lxYToGijEwzy5D50nezDdIk406VT6RrelfHrW2b4p+6JjaXTvC576+XAsrKH/Ji17rFS1LEEjEFFV7o9tviVidX9+7PdVVx3sJ+y/M3cJNgA/vWHyc+ktXAZPxLd9SE++95Aq74+0iIkFt10gjenJpoGb+DaI6Zcf0ouQjryj/UIwAULaaKNw8n7WFScoj6vE9sHhCm42mB5tFECJ5JkjfbJTkPd3FpIxPdklABdvmkDSr4H8Qw628ZrT9JiW8LpM15Ly10l8C5ONyXUxvjN8B5J+vTSGQzLyvvFAf8IR2pvE8YM5JCnvW4R0P1D3s8sC6CIG13zdKdQB9g+/gPx0Y09pv4Y0cpsOab8Z6IYU4iv06kt6uRmmU4qRGt94P3QZSJ8vryPNg6+INGNZHGl2Dh1EM0G78KdcE2iSTE4wub50Lfg9v9Nj3qXvGPKojI99On9nnwcXsGhUhtgKH83PDdupyqjKJb+TKBbOe0+cYulTHqJkriml8v4m/ToIWlNp65EAYYOWT4k3kW0upny8Oz0cpq7vQXyHssOROBnrbZ9OyxwDwUb2vdJsb/UUtnOCcTuzvtas58aqrpJMxScq1PNDdwmHVNcbafmLWqul5VyyXd/LyXoud78tq0sxrkXFORfsxCM34O6R+INN3Ob+OQzdMLVZ/+kLMrm7NbrjPUAGbe6NYsRl9XDWwO7PnYrvngCc8oiNIPxgSfIO/NOsbMt4qdq679RB3x5g6NPDwCPxHf1jtJ1V3WjZF46t7uzeJfXpkXj2UFroTddZVzdVwToBzu4ekYvUSvdzOPaLHYZjwyifu9S6NjA+nKUKEZ+h/tg45lhbN4WU/7G+kY/EWcrnmGx7uAQbwdBEnGL872R9NMyaVhkrDTuxBwL9KtQDRpUb5+fWywhG3eeY398C0RrZ3wzqHkcxpyDeVBbjZu17eb7aAFt4IIAsjF/04GfAvT/WEfeSVfTnCeXhzFkJ3ZxidWf983r1vpS6b2d9sMG27dQQA+VuMGvCdQZ+DXOIxHNjR0Zx54U=
*/