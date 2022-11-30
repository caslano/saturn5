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


namespace boost { namespace hana {
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
    BOOST_HANA_INLINE_VARIABLE constexpr monadic_fold_left_t<M> monadic_fold_left{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_MONADIC_FOLD_LEFT_HPP

/* monadic_fold_left.hpp
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
*/