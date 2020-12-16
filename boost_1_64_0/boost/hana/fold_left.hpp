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
HovQDzH9E/FL+QSvXkNvqvuo/cB5/FX0CPuTnrUuulYf/kl9jTPwVlfP0z/Req/PP+Y+zfjDcLzh/rYHQ32CB3qEfRDxpNdS1cm6pfL5WbqtC1x5gJ7RX6s+l++qoQPle5q+b8oCuvoJfoFuiO2AF/X0pTquv9S8D6NXbzPe0/H1YM/B72Xh9zx4X5PGh39sfvFWU0m4DkkXdoWvD4gHnRHjB6ct8/pBfGQpPUTn5yTCg+fl3Ui6oBR/XEi//yTuE6P64voov3meVOsJ4lBUgfdjfOxN+PQP8aPLpz7Gjw+EU7Pgd6jz36ATrwu/p89+KfVQNVXcCuGZ/SY9+eeCP+RPDdxvUu/zjTMVXuHvuXxA/p3uv4/e8n5ujyify0ck8dPH0PHyMrkiOFbIj2VrrcOc7P5R+JJGDyWo1zI6+Gt6MOyHPi0OYV/0Qfr9EfUS+lT7Veuf58+Gqzs+cUoW/V1MH/GNy0M/dZX9gOf6++lIcJ1x8G+xesCv3Qbg8ev1w7vjocX4dS09043fsm5ZUS8e9HPuxfJKPRSvNa/0VJSPyDxcXvXEt6ON+0l4f5L9L4P1W74I3o/SIXPawoEW5idJnRwR/g6gvL6A3ub3Yt96viF0gX5T1irrC8n0jT5N+jrndzFvB7l/+H3Zbenn++Dt4fY1fitPPW9Vg3kqjPn/furH+khLPFJ4jDz6LPx+VDwWsw8CX1Tzl7FbPW8i/dJJHQyAT23E8Ur5v4Qfu9n19H+2fxbqZ/p+hvHqW3a71Dj3i9876m6n/kmFOgt54zx4ZzxzJtHLmfp/cHjW9+bhNfHsi//lXwU+L3jD/FyJFw9Wd+o5qY88qqKPPN/2eeG6fvg7tXD5N/k4VHxa0dfpMXpUPrbSN7ha/p1EX7bXV7wDjlykv/gLvg/Xbb6N6C+GOk0cu9knkRzua3a+19Pk96rw+wpPSLSvgs5+lu95Ak4WwP1fzecTdP7L5mUzvd3XuloyHRP+3ulznuN7n+8G1++yDlbDj221LvwYXt+m/n+jT9LhYq11v0/1m7+h5/Bwy1+tY/SCxwvF137rIrxeX+P/cam/gsvg10b1CS9nnOV69mMlZ6ibg+VFHf5aTwf/pj4uoKO20S/8RKyVOrOfuay3PH6bb/hNXGbq9+srFd8ivz9SB8Yz+Qv7gu4W38/pDOenXiiP/8Wfw4+q39XJIeLXHH8mwtF8/b+B8HS3uG3hkz40T3xqajmdMUCcW4Z+0nhT1FeR/nNKFG7Kl0yfv0L9z6H39OUWum91nI4br68CB7Lp/kVz+Ihafjmivp/hkwb5PJydqq6K9dvzH1BP1pOmvcs3ngln9C8yV+DJLfAWPxU9bH2mD38coZtvo6/gQN6v/NC9+hpv0Ft3i+PF+gJf8zMb+Z3Z8u0n9bAW3hyszr2+8mfj/sJ8ycsK+qukRh6fwQ/Si1niP2Uunl8vPv34lzOtB5fBkdvo2Bb6DyfQeSWuA//qJuJPOFd3J51/ouvpMywfAfeW2w/WCY+q5/QFcKFzxHzGgr9/9LwXwNlM+JZp/AvxZH91d3dwLM+Qb8PpdDhaSvfWys/2YR2Pg7u30zHp9Aleqx8sLx7l6y+iO/rI/3/4N9ApeDnHesSb5rVNJDivhK44nj+9k16wnlfWUn/MPFRE9SFO4x+Hwb0R+oQp8OlGefODPBmBT1uq77F0PF06dwj9new6F8b0M9XXO+Kq3ioW8NtZ9GS471M/ruB4OjrkyWecNzUSvJ5mHB/yN03mf5Y82+m+bewj3Sl/Q51+WnAs3efz9hGmFNJtNfjnOLpmlnwSz+qP4MhKvvor/vZY+PCZOlulvv/mB8Rzdr062kXn8DM1ZfI=
*/