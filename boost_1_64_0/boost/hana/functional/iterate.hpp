/*!
@file
Defines `boost::hana::iterate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_ITERATE_HPP
#define BOOST_HANA_FUNCTIONAL_ITERATE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/functional/partial.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Applies another function `n` times to its argument.
    //!
    //! Given a function `f` and an argument `x`, `iterate<n>(f, x)` returns
    //! the result of applying `f` `n` times to its argument. In other words,
    //! @code
    //!     iterate<n>(f, x) == f(f( ... f(x)))
    //!                         ^^^^^^^^^^ n times total
    //! @endcode
    //!
    //! If `n == 0`, `iterate<n>(f, x)` returns the `x` argument unchanged
    //! and `f` is never applied. It is important to note that the function
    //! passed to `iterate<n>` must be a unary function. Indeed, since `f`
    //! will be called with the result of the previous `f` application, it
    //! may only take a single argument.
    //!
    //! In addition to what's documented above, `iterate` can also be
    //! partially applied to the function argument out-of-the-box. In
    //! other words, `iterate<n>(f)` is a function object applying `f`
    //! `n` times to the argument it is called with, which means that
    //! @code
    //!     iterate<n>(f)(x) == iterate<n>(f, x)
    //! @endcode
    //!
    //! This is provided for convenience, and it turns out to be especially
    //! useful in conjunction with higher-order algorithms.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a function \f$ f : T \to T \f$ and `x` and argument of data
    //! type `T`, the signature is
    //! \f$
    //!     \mathtt{iterate_n} : (T \to T) \times T \to T
    //! \f$
    //!
    //! @tparam n
    //! An unsigned integer representing the number of times that `f`
    //! should be applied to its argument.
    //!
    //! @param f
    //! A function to apply `n` times to its argument.
    //!
    //! @param x
    //! The initial value to call `f` with.
    //!
    //!
    //! Example
    //! -------
    //! @include example/functional/iterate.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto iterate = [](auto&& f) {
        return [perfect-capture](auto&& x) -> decltype(auto) {
            return f(f( ... f(forwarded(x))));
        };
    };
#else
    template <std::size_t n, typename = when<true>>
    struct iterate_t;

    template <>
    struct iterate_t<0> {
        template <typename F, typename X>
        constexpr X operator()(F&&, X&& x) const
        { return static_cast<X&&>(x); }
    };

    template <>
    struct iterate_t<1> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return f(static_cast<X&&>(x));
        }
    };

    template <>
    struct iterate_t<2> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return f(f(static_cast<X&&>(x)));
        }
    };

    template <>
    struct iterate_t<3> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return f(f(f(static_cast<X&&>(x))));
        }
    };

    template <>
    struct iterate_t<4> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return f(f(f(f(static_cast<X&&>(x)))));
        }
    };

    template <>
    struct iterate_t<5> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return f(f(f(f(f(static_cast<X&&>(x))))));
        }
    };

    template <std::size_t n>
    struct iterate_t<n, when<(n >= 6) && (n < 12)>> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return iterate_t<n - 6>{}(f,
                f(f(f(f(f(f(static_cast<X&&>(x)))))))
            );
        }
    };

    template <std::size_t n>
    struct iterate_t<n, when<(n >= 12) && (n < 24)>> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return iterate_t<n - 12>{}(f,
                f(f(f(f(f(f(f(f(f(f(f(f(
                    static_cast<X&&>(x)
                ))))))))))))
            );
        }
    };

    template <std::size_t n>
    struct iterate_t<n, when<(n >= 24) && (n < 48)>> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return iterate_t<n - 24>{}(f,
                f(f(f(f(f(f(f(f(f(f(f(f(
                f(f(f(f(f(f(f(f(f(f(f(f(
                    static_cast<X&&>(x)
                ))))))))))))
                ))))))))))))
            );
        }
    };

    template <std::size_t n>
    struct iterate_t<n, when<(n >= 48)>> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return iterate_t<n - 48>{}(f,
                f(f(f(f(f(f(f(f(f(f(f(f(
                f(f(f(f(f(f(f(f(f(f(f(f(
                f(f(f(f(f(f(f(f(f(f(f(f(
                f(f(f(f(f(f(f(f(f(f(f(f(
                    static_cast<X&&>(x)
                ))))))))))))
                ))))))))))))
                ))))))))))))
                ))))))))))))
            );
        }
    };

    template <std::size_t n>
    struct make_iterate_t {
        template <typename F>
        constexpr decltype(auto) operator()(F&& f) const
        { return hana::partial(iterate_t<n>{}, static_cast<F&&>(f)); }

        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return iterate_t<n>{}(static_cast<F&&>(f),
                                  static_cast<X&&>(x));
        }
    };

    template <std::size_t n>
    constexpr make_iterate_t<n> iterate{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_ITERATE_HPP

/* iterate.hpp
db+Ql3rzcC9ljpWjP/wd4O777807AFyvtYb3HCibnZx9Je5/pRXvcbh5Ed6z4DUgH6NedvvtR7tBtE27QSUw4xGez7lpFt4d49rvDjTwPrSBnNuDF7j/adAfXPFTvBui/39DaBvnTe7/utwiP+hZqY97d8Kv3jbPzUz7AO2hbp4pqmxvPR64PR/tPPg9E++lZOAa97tpnRjwEdikz4B79Nmgb9KYxzBHM6YD4SND7PvN4R/d35kB18Av4Dr4FfwGfgc3wB/gJrgFboM74K5+QcICNnCAn6386yMgHUgPMoCMIBPIDLKArCAbyA5ygJwgFwgAuUEekBfkA4EgCKzieUvAUrAMLAcrwEpQDawGa8DrLu/Bm+At8LYrz+Dv4B2wDrwL1oMNYKMeo/fAZrAFvA+2gg/Ah+AjkAQ+Bp+AbeBT8Bn4HHwBtoMd4EvAlJKf+1O/t7sb7AF7wddgH9gPDoCD4BA4DI6Ao+AbcAwcBycAr7Lx+or63efT4Az4DnwPzoJz4Dy4AC6CH8AlUBSeFQPFQQlQEpQCpUEZUBaUA49qmQ8GFUBFLf+VQRVQFVQD1cFl6v3JlXVwFQSDCqAiqAQqgyrgMbc85xqgJqgFart08DioA+qCeqA+eAI0AA1BIxACQkFj0AQ0Bc1AVdActACuGWsJwkErEAFag0gQBaJBG9AWtAPtQQfQEXQCnUEX8CToCrqB7qAH6AliQCzoBeJAb9AH9AX9LKXTA8BTIN5Suj8IJIDBlrIDiWAoGGYpnR4ORoCRgJ+3IwZRv1P/vKVsySgwGvzNUrZjDBgLXgIvg3FgPJgAJoJJYDKYAl4BU8E0wDYqn92YCWaB2eBVMAe8BuaCeWA+WAAWgkVgMSgP0rm/HQseAZlAZtf/gqwgm36VKwfICXKBANfvgDwgL3DNfiAIcv2Ma2/d+SIoBAq7dseNC0AxUByUcOMFUAqU1j6rLMCk+77jVt6ND0EFUBFUApVBFVAVVHPjAlAD1AS1XH8PHgOPgzpufAJwL77vpD0BGoCGoBEIAaGgMWgCmoJmvu87ImsgDLQE4aAViHD9OIgEUSDa9/0B9b2CdqC96/dBR9AJdHbnT+BJ0FWU7e4OeoCe2o7Hgl6+33tXtr8P6Av6gf5gAHgKxIOBbtwGEnzuFVkDidrPD3P9hxuXgBFgJHjGjRfAc+B59Zod371T35b7m+unAGlIX7zwkiifOA6MBxPARDc+FPVdvCmifNVUMA1Md32UG9+5IQaYLcpfzQGvgbmu33Hnr2ABWAgWuXkGsAQsBcvc+BusEPV9v1Vu3APWgNdF+dI3wVvgbbDWjYfAO2AdeNeNn8AGsFH7uvfAZrDF9atuPAQ+AB9qn5gEPgafgG1uvAY+A59r37kd7ABfgp1uHAq+ArvBHndeCL4GpKt8McUBcBAcAofd+Rg4Cr4Bx9z4DJwA34KTbtwPToMz4Ds3HgZnwTnt6y+Ai+AHcMmdz4DL4Cdwxbcegd8G18AvbjwLfgW/uXGCG1+CP8BNcMudR4M7gPSTL+6xgA0c4Af8wSOu7lsq9ssAMoJMIDPIArKCbCA7yAFyglwgAOQGeUBekA8EgiCQHxQABUEhUBgUAUVBMVAclAAlQSlQGpQBZUE58Khbh00doCAoBAqDWqAGqAlY6kg70o60I+1IO4zj8TS7mHakHWlH2pF2pB1pR9qRdqQdaUfakXakHf/3xz8AUEsDBBQAAAAIAOKuvErXthokNtoKAAAsHAATAAAAYmluL2xpYmNyeXB0b01ELmRsbOScBVuWTRbHH7pBsLEwMVGxGxW7OwALRbFQ7O7G1sVcE1sMUFHEBhURURRbbAEVLCyM/f/Y3Ws=
*/