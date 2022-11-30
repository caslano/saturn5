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


namespace boost { namespace hana {
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
    BOOST_HANA_INLINE_VARIABLE constexpr monadic_fold_right_t<M> monadic_fold_right{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_MONADIC_FOLD_RIGHT_HPP

/* monadic_fold_right.hpp
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
*/