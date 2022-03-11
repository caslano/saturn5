/*!
@file
Defines `boost::hana::demux`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_DEMUX_HPP
#define BOOST_HANA_FUNCTIONAL_DEMUX_HPP

#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Invoke a function with the results of invoking other functions
    //! on its arguments.
    //!
    //! Specifically, `demux(f)(g...)` is a function such that
    //! @code
    //!     demux(f)(g...)(x...) == f(g(x...)...)
    //! @endcode
    //!
    //! Each `g` is called with all the arguments, and then `f` is called
    //! with the result of each `g`. Hence, the arity of `f` must match
    //! the number of `g`s.
    //!
    //! This is called `demux` because of a vague similarity between this
    //! device and a demultiplexer in signal processing. `demux` takes what
    //! can be seen as a continuation (`f`), a bunch of functions to split a
    //! signal (`g...`) and zero or more arguments representing the signal
    //! (`x...`). Then, it calls the continuation with the result of
    //! splitting the signal with whatever functions where given.
    //!
    //! @note
    //! When used with two functions only, `demux` is associative. In other
    //! words (and noting `demux(f, g) = demux(f)(g)` to ease the notation),
    //! it is true that `demux(demux(f, g), h) == demux(f, demux(g, h))`.
    //!
    //!
    //! Signature
    //! ---------
    //! The signature of `demux` is
    //! \f[
    //!     \mathtt{demux} :
    //!         (B_1 \times \dotsb \times B_n \to C)
    //!             \to ((A_1 \times \dotsb \times A_n \to B_1)
    //!                 \times \dotsb
    //!                 \times (A_1 \times \dotsb \times A_n \to B_n))
    //!             \to (A_1 \times \dotsb \times A_n \to C)
    //! \f]
    //!
    //! This can be rewritten more tersely as
    //! \f[
    //!     \mathtt{demux} :
    //!         \left(\prod_{i=1}^n B_i \to C \right)
    //!         \to \prod_{j=1}^n \left(\prod_{i=1}^n A_i \to B_j \right)
    //!         \to \left(\prod_{i=1}^n A_i \to C \right)
    //! \f]
    //!
    //!
    //! Link with normal composition
    //! ----------------------------
    //! The signature of `compose` is
    //! \f[
    //!     \mathtt{compose} : (B \to C) \times (A \to B) \to (A \to C)
    //! \f]
    //!
    //! A valid observation is that this coincides exactly with the type
    //! of `demux` when used with a single unary function. Actually, both
    //! functions are equivalent:
    //! @code
    //!     demux(f)(g)(x) == compose(f, g)(x)
    //! @endcode
    //!
    //! However, let's now consider the curried version of `compose`,
    //! `curry<2>(compose)`:
    //! \f[
    //!     \mathtt{curry_2(compose)} : (B \to C) \to ((A \to B) \to (A \to C))
    //! \f]
    //!
    //! For the rest of this explanation, we'll just consider the curried
    //! version of `compose` and so we'll use `compose` instead of
    //! `curry<2>(compose)` to lighten the notation. With currying, we can
    //! now consider `compose` applied to itself:
    //! \f[
    //!     \mathtt{compose(compose, compose)} :
    //!         (B \to C) \to (A_1 \to A_2 \to B) \to (A_1 \to A_2 \to C)
    //! \f]
    //!
    //! If we uncurry deeply the above expression, we obtain
    //! \f[
    //!     \mathtt{compose(compose, compose)} :
    //!         (B \to C) \times (A_1 \times A_2 \to B) \to (A_1 \times A_2 \to C)
    //! \f]
    //!
    //! This signature is exactly the same as that of `demux` when given a
    //! single binary function, and indeed they are equivalent definitions.
    //! We can also generalize this further by considering
    //! `compose(compose(compose, compose), compose)`:
    //! \f[
    //!     \mathtt{compose(compose(compose, compose), compose)} :
    //!         (B \to C) \to (A_1 \to A_2 \to A_3 \to B)
    //!             \to (A_1 \to A_2 \to A_3 \to C)
    //! \f]
    //!
    //! which uncurries to
    //! \f[
    //!     \mathtt{compose(compose(compose, compose), compose)} :
    //!         (B \to C) \times (A_1 \times A_2 \times A_3 \to B)
    //!             \to (A_1 \times A_2 \times A_3 \to C)
    //! \f]
    //!
    //! This signature is exactly the same as that of `demux` when given a
    //! single ternary function. Hence, for a single n-ary function `g`,
    //! `demux(f)(g)` is equivalent to the n-times composition of `compose`
    //! with itself, applied to `g` and `f`:
    //! @code
    //!     demux(f)(g) == fold_left([compose, ..., compose], id, compose)(g, f)
    //!                           //  ^^^^^^^^^^^^^^^^^^^^^ n times
    //! @endcode
    //!
    //! More information on this insight can be seen [here][1]. Also, I'm
    //! not sure how this insight could be generalized to more than one
    //! function `g`, or if that is even possible.
    //!
    //!
    //! Proof of associativity in the binary case
    //! -----------------------------------------
    //! As explained above, `demux` is associative when it is used with
    //! two functions only. Indeed, given functions `f`, `g` and `h` with
    //! suitable signatures, we have
    //! @code
    //!     demux(f)(demux(g)(h))(x...) == f(demux(g)(h)(x...))
    //!                                 == f(g(h(x...)))
    //! @endcode
    //!
    //! On the other hand, we have
    //! @code
    //!     demux(demux(f)(g))(h)(x...) == demux(f)(g)(h(x...))
    //!                                 == f(g(h(x...)))
    //! @endcode
    //!
    //! and hence `demux` is associative in the binary case.
    //!
    //!
    //! Example
    //! -------
    //! @include example/functional/demux.cpp
    //!
    //! [1]: http://stackoverflow.com/q/5821089/627587
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto demux = [](auto&& f) {
        return [perfect-capture](auto&& ...g) {
            return [perfect-capture](auto&& ...x) -> decltype(auto) {
                // x... can't be forwarded unless there is a single g
                // function, or that could cause double-moves.
                return forwarded(f)(forwarded(g)(x...)...);
            };
        };
    };
#else
    template <typename F>
    struct pre_demux_t;

    struct make_pre_demux_t {
        struct secret { };
        template <typename F>
        constexpr pre_demux_t<typename detail::decay<F>::type> operator()(F&& f) const {
            return {static_cast<F&&>(f)};
        }
    };

    template <typename Indices, typename F, typename ...G>
    struct demux_t;

    template <typename F>
    struct pre_demux_t {
        F f;

        template <typename ...G>
        constexpr demux_t<std::make_index_sequence<sizeof...(G)>, F,
                          typename detail::decay<G>::type...>
        operator()(G&& ...g) const& {
            return {make_pre_demux_t::secret{}, this->f, static_cast<G&&>(g)...};
        }

        template <typename ...G>
        constexpr demux_t<std::make_index_sequence<sizeof...(G)>, F,
                          typename detail::decay<G>::type...>
        operator()(G&& ...g) && {
            return {make_pre_demux_t::secret{}, static_cast<F&&>(this->f), static_cast<G&&>(g)...};
        }
    };

    template <std::size_t ...n, typename F, typename ...G>
    struct demux_t<std::index_sequence<n...>, F, G...> {
        template <typename ...T>
        constexpr demux_t(make_pre_demux_t::secret, T&& ...t)
            : storage_{static_cast<T&&>(t)...}
        { }

        basic_tuple<F, G...> storage_;

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) const& {
            return hana::at_c<0>(storage_)(
                hana::at_c<n+1>(storage_)(x...)...
            );
        }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) & {
            return hana::at_c<0>(storage_)(
                hana::at_c<n+1>(storage_)(x...)...
            );
        }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) && {
            return static_cast<F&&>(hana::at_c<0>(storage_))(
                static_cast<G&&>(hana::at_c<n+1>(storage_))(x...)...
            );
        }
    };

    template <typename F, typename G>
    struct demux_t<std::index_sequence<0>, F, G> {
        template <typename ...T>
        constexpr demux_t(make_pre_demux_t::secret, T&& ...t)
            : storage_{static_cast<T&&>(t)...}
        { }

        basic_tuple<F, G> storage_;

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) const& {
            return hana::at_c<0>(storage_)(
                hana::at_c<1>(storage_)(static_cast<X&&>(x)...)
            );
        }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) & {
            return hana::at_c<0>(storage_)(
                hana::at_c<1>(storage_)(static_cast<X&&>(x)...)
            );
        }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) && {
            return static_cast<F&&>(hana::at_c<0>(storage_))(
                static_cast<G&&>(hana::at_c<1>(storage_))(static_cast<X&&>(x)...)
            );
        }
    };

    constexpr make_pre_demux_t demux{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_DEMUX_HPP

/* demux.hpp
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
*/