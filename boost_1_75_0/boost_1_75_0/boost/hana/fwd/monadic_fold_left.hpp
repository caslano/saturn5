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
mNfv+wq4zk6BUnZV96bOfRrTpiK7oel7LP486ybRzVmodfHPiuqHyuskgo8yuCX5xO5NAyTy0dR/olkkPI5w9efZW/1ssSouRG1yrbXGKiRtMR82vyywZ13DKMnWFdkd5va7vzEQ4wmlH5JYuvzwJ6P3Su578qWLtqNF9DPNuQfqzxdNGZGWBQiLRAt74K/c5EoPNpo4WVgVw1/lyecwT+XWHXISubLZ6fahP2vEzNI0W65onuOo1uispM9d9dErf5JMfZWklOF2mscp999UyhFbpVylvIiUpKmI/yX9MXx+KpM0syAP/Yza6XY8vKPxW7qhy6CqQ7pphUGdtrI4eb54pBBXmc8+p9KZBJMCnU6nqDIGrd2mkop8/tEDqZxetOnXceKLzgdyZNV09WGqrxoR6TQlTgrc9nzMou8VyKOKk7g7uAREylYzEgpENu1ZVhYxB1jTtqvvGUxVkROig4AEAWctbLvf2wSBZFKeNq4yNo4KTcWFQ5RbJJjQTL2XqWhFyc0SMfP1EidEvj8UMNZ4qEqLKHzv01KS0rvLD+o+3FulidOYtVWJg1w7GUowPunLqw6VOWdcZ9bzTLnnxzym7w9YsNawWCb8IaWqNpwc7GUzp+lgFQkBptxGzLJt0lsASS7mpac4lw86p3Blmp/yBCtCFG14MtT28KRXbdY8mhH2W7iE0psUh/qCT8bikxLqJkUmfTBldfBI
*/