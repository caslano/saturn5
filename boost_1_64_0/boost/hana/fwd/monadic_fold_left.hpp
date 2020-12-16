/*!
@file
Forward declares `boost::hana::monadic_fold_left`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MONADIC_FOLD_LEFT_HPP
#define BOOST_HANA_FWD_MONADIC_FOLD_LEFT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Monadic left-fold of a structure with a binary operation and an
    //! optional initial reduction state.
    //! @ingroup group-Foldable
    //!
    //! @note
    //! This assumes the reader to be accustomed to non-monadic left-folds as
    //! explained by `hana::fold_left`, and to have read the [primer]
    //! (@ref monadic-folds) on monadic folds.
    //!
    //! `monadic_fold_left<M>` is a left-associative monadic fold. Given a
    //! `Foldable` with linearization `[x1, ..., xn]`, a function `f` and an
    //! optional initial state, `monadic_fold_left<M>` applies `f` as follows:
    //! @code
    //!     // with state
    //!     ((((f(state, x1) | f(-, x2)) | f(-, x3)) | ...) | f(-, xn))
    //!
    //!     // without state
    //!     ((((f(x1, x2) | f(-, x3)) | f(-, x4)) | ...) | f(-, xn))
    //! @endcode
    //!
    //! where `f(-, xk)` denotes the partial application of `f` to `xk`, and
    //! `|` is just the operator version of the monadic `chain`.
    //!
    //! When the structure is empty, one of two things may happen. If an
    //! initial state was provided, it is lifted to the given Monad and
    //! returned as-is. Otherwise, if the no-state version of the function
    //! was used, an error is triggered. When the stucture contains a single
    //! element and the no-state version of the function was used, that
    //! single element is lifted into the given Monad and returned as is.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Monad` `M`, a `Foldable` `F`, an initial state of tag `S`,
    //! and a function @f$ f : S \times T \to M(S) @f$, the signatures of
    //! `monadic_fold_left<M>` are
    //! \f[
    //!     \mathtt{monadic\_fold\_left}_M :
    //!         F(T) \times S \times (S \times T \to M(S)) \to M(S)
    //! \f]
    //!
    //! for the version with an initial state, and
    //! \f[
    //!     \mathtt{monadic\_fold\_left}_M :
    //!         F(T) \times (T \times T \to M(T)) \to M(T)
    //! \f]
    //!
    //! for the version without an initial state.
    //!
    //! @tparam M
    //! The Monad representing the monadic context in which the fold happens.
    //! The return type of `f` must be in that Monad.
    //!
    //! @param xs
    //! The structure to fold.
    //!
    //! @param state
    //! The initial value used for folding. If the structure is empty, this
    //! value is lifted in to the `M` Monad and then returned as-is.
    //!
    //! @param f
    //! A binary function called as `f(state, x)`, where `state` is the result
    //! accumulated so far and `x` is an element in the structure. The
    //! function must return its result inside the `M` Monad.
    //!
    //!
    //! Example
    //! -------
    //! @include example/monadic_fold_left.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename M>
    constexpr auto monadic_fold_left = [](auto&& xs[, auto&& state], auto&& f) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct monadic_fold_left_impl : monadic_fold_left_impl<T, when<true>> { };

    template <typename M>
    struct monadic_fold_left_t {
        template <typename Xs, typename State, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, State&& state, F&& f) const;

        template <typename Xs, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, F&& f) const;
    };

    template <typename M>
    constexpr monadic_fold_left_t<M> monadic_fold_left{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MONADIC_FOLD_LEFT_HPP

/* monadic_fold_left.hpp
lhOmqjGQQ61keg/+xb3aFg8r5Z0Q2COWJIet1QL6m6GTkfhp/nTHWiAwGktWSnAx98zxPlF9ZXdvVxhomD72iF8Xa6bTMC1SkGkYhKWuC7trHCNQjYNWFObFScnljju/z0nR53cK5veubhJuG/GQ5bJtPH95yveNTvmkLI7DK1dOCSymqr5qnGrNWTcrMX2/ks3NMhKga8CJ7FmQQEp52bCLc+V9ECCEK0iFDsmNvf0DNe7i3Ho1rja3PqbKBowowtbfjO3+ac/87vLIbSXScL9xuezO0TqTYCHxGele8+otHitnn0ppiMQUsfnFyvM4pbpVRX5aXPziQQTJy1DMUy/Fq58Npy3WnlLEHZREoGg67XpFsi15fPXaK4YAJbVV8/FuMbk+0T8as4KZcOaoxKUZxjJbQ8HYaPJJ0Y6RRvjNFB6hUJ84nG4Ej9eDmcEQf4pmyKYYqa/vFa9Ec6QgnPibO8s1kib1TnkanK25rj50iRH3MV9ylAd4SZTvtX4Gq0B6SRTUFk3eIJPn8eUk8clwkM9S0eYxsjwsL4eKIZcaPMS9CGLwlHIXZuhNrazGO+wvjDYU2ry4ghQYDISZqpU311c1VGvyaL0NlcNl3bNl3eP1uqvq/aI4+ZgTK2xgzF4xajilMs62/GJA8n/j2Zbhr67mQAztZpfQjcnFuNL9IH6BAeisacMBOeds50ppioT1baXiB5NpM/5wHwRjQ0raMsK9b/oyyuPFYUOSPix5PBVKxdVTKH3MMMhCrnsAUTmhhaS+KuhW+Bqu4q0+Gt8lQx0PMAPWyP7wxWo9ksNO6qra8fsrJRTuD0Ho1k8yrleBIkKa+rdzJW53qnylgYJCMoic8eD/Jr+IjfZMBnnFR+foQZdGSJRBX16eo/Skf0Qbk8rUqPqET+zUSm86bWvL3c//xxi8Ah3/+MSvRupEzUFk/JbLdKZ4OyN6qV+KNWj6zxnKwwstj9IALra/wxejUoAyl1W56f76ICPveYWcoQAZgGCc+gk9dfVGHEJQ3X5iwgciiW4BBOEneWB01F/kCk+kj1Pkn6d3pU8FBcBEGfj+CuuYvk7y/S+1T461NRLV7xivFhBRyNmHdahyQGBwRXKKC6XsvI7bGLiS333i4yxNySOQxSGR2VaPdn7uNBK9knVSruX5L3pepzpy2mb1HzLHevv5zO1UJqrNsGYFdzGkqOG5n6WHylW0AW+sOYxtSvnsPoHrUSVrGE0LxIvmoYY1kcbgWPOq3z366KMdOMx7fUM49G7svkL0zA7ce4316azhxMBUzu2FLyuRj7zS9eRG3K34Zvdib9OK3ac2TyKOwkHtUvwWD3lqSFDKAYHHV+itQ5KT6vfJweP2/mohSznS20rgfQaiVFG4ojsgCFzJDCckZG8r4sIVx4XUQr1LN6NLD1x7UpD6o0lC6tyKuzFzdGBZCV6je3EJDK+UinqOjpafe+3ngmzhj74skB3xFxgo2+EU68bqm4xzAhfojbsJjfvpNbqv4s/Mf6+RP+nI/OVGfmKClaLPXMuQxOoDL3s+cfFBX8Q8gdFt6D2m4PhI/XCIok1gkqt2A0iI4Q1GcE7E/MmGjyr7EP93T2xwduSesUhtwi2c+tERuuG388QAw6o0lBvL0qYHMqSBClajklNpAGq3R67yYNe2nEcgMILT06AeLJT+Sz5DowqrDzRK6aqCY/lqXABjHa6+YD841tB/QEFsYhD8I+l+eB1P3WAJvWvFoul46urQ9jgzLjCwT3JEOp4abXLvx3cswvjBrD/0cL/mzsZvHPK6X8NDvP7Q0z3RQlZ4UbBVDztDf7DpD73cE61I5UQqux7WW39w8INadNA90V4rMt0=
*/