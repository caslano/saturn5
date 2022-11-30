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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr make_pre_demux_t demux{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_DEMUX_HPP

/* demux.hpp
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
*/