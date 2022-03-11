/*!
@file
Forward declares `boost::hana::monadic_fold_right`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MONADIC_FOLD_RIGHT_HPP
#define BOOST_HANA_FWD_MONADIC_FOLD_RIGHT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Monadic right-fold of a structure with a binary operation and an
    //! optional initial reduction state.
    //! @ingroup group-Foldable
    //!
    //! @note
    //! This assumes the reader to be accustomed to non-monadic right-folds as
    //! explained by `hana::fold_right`, and to have read the [primer]
    //! (@ref monadic-folds) on monadic folds.
    //!
    //! `monadic_fold_right<M>` is a right-associative monadic fold. Given a
    //! structure containing `x1, ..., xn`, a function `f` and an optional
    //! initial state, `monadic_fold_right<M>` applies `f` as follows
    //! @code
    //!     // with state
    //!     (f(x1, -) | (f(x2, -) | (f(x3, -) | (... | f(xn, state)))))
    //!
    //!     // without state
    //!     (f(x1, -) | (f(x2, -) | (f(x3, -) | (... | f(xn-1, xn)))))
    //! @endcode
    //!
    //! where `f(xk, -)` denotes the partial application of `f` to `xk`,
    //! and `|` is just the operator version of the monadic `chain`.
    //! It is worth noting that the order in which the binary function should
    //! expect its arguments is reversed from `monadic_fold_left<M>`.
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
    //! and a function @f$ f : T \times S \to M(S) @f$, the signatures of
    //! `monadic_fold_right<M>` are
    //! \f[
    //!     \mathtt{monadic\_fold\_right}_M :
    //!         F(T) \times S \times (T \times S \to M(S)) \to M(S)
    //! \f]
    //!
    //! for the version with an initial state, and
    //! \f[
    //!     \mathtt{monadic\_fold\_right}_M :
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
    //! A binary function called as `f(x, state)`, where `state` is the result
    //! accumulated so far and `x` is an element in the structure. The
    //! function must return its result inside the `M` Monad.
    //!
    //!
    //! Example
    //! -------
    //! @include example/monadic_fold_right.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename M>
    constexpr auto monadic_fold_right = [](auto&& xs[, auto&& state], auto&& f) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct monadic_fold_right_impl : monadic_fold_right_impl<T, when<true>> { };

    template <typename M>
    struct monadic_fold_right_t {
        template <typename Xs, typename State, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, State&& state, F&& f) const;

        template <typename Xs, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, F&& f) const;
    };

    template <typename M>
    constexpr monadic_fold_right_t<M> monadic_fold_right{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MONADIC_FOLD_RIGHT_HPP

/* monadic_fold_right.hpp
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
*/