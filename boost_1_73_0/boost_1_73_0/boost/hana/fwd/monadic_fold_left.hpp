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
KG1Af2q1vGno9Xve2JlpvvLC7rnv0OyVtYT7BITAVaYD59UzndYM2zlfsj8roZhzft6hi4t2kmct/JsqySMwaFhds3K3ZT9xtOFVA+/Wv7hAJ2PqlRlXjr1xhYcnMC56/4V+MFa+/yMc3befYccR7hZgwnB3nllVz/G7n75Fj+Iwfgz3dVgFYVGj7zuEa9a9eQiw2/G1db43uHYa+n94YsLU9fAm/OT1nZ1WxEaPV+gzh9E75qKDCw8uO4c/0hkahLDoUUiGG5f6iL0VCan3JeALyUD0WR7DMUs66yz0rvz+2Dd57XuDa0NuA+/Wmc1ae5RyUx7pu0mpOeHhh9a99nP2Gsev404OfMI9lw5ry9unZ7hcmhxsffvYvESVkCH8DF48He5O0L8+0hN8VLpz5pJFD2e04K1E5KwFoRdFdhLWWR1xPwiGgTMD1dCTcXun0stAR1VH+PAEgMCuJQJ/PO1PnD3gppJ7A82ef5sOJ/6ls19+IF97eaOZKdxqNbdJmG+UTY655xltmtCYMpvtw9hSefauxrRvIPgXUEsDBAoAAAAIAC1nSlITgBTrdigAAGfTAAAgAAkAY3VybC1tYXN0ZXIvbTQvY3VybC1jb21waWxlcnMubTRVVAUAAbZIJGDtfX1/27au8P/9
*/