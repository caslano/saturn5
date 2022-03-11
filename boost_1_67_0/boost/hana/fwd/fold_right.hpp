/*!
@file
Forward declares `boost::hana::fold_right`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FOLD_RIGHT_HPP
#define BOOST_HANA_FWD_FOLD_RIGHT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Right-fold of a structure using a binary operation and an optional
    //! initial reduction state.
    //! @ingroup group-Foldable
    //!
    //! `fold_right` is a right-associative fold using a binary operation.
    //! Given a structure containing `x1, ..., xn`, a function `f` and
    //! an optional initial state, `fold_right` applies `f` as follows
    //! @code
    //!     f(x1, f(x2, f(x3, f(x4, ... f(xn-1, xn) ... )))) // without state
    //!     f(x1, f(x2, f(x3, f(x4, ... f(xn, state) ... )))) // with state
    //! @endcode
    //!
    //! @note
    //! It is worth noting that the order in which the binary function should
    //! expect its arguments is reversed from `fold_left`.
    //!
    //! When the structure is empty, two things may arise. If an initial
    //! state was provided, it is returned as-is. Otherwise, if the no-state
    //! version of the function was used, an error is triggered. When the
    //! stucture contains a single element and the no-state version of the
    //! function was used, that single element is returned as is.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Foldable` `F` and an optional initial state of tag `S`,
    //! the signatures for `fold_right` are
    //! \f[
    //!     \mathtt{fold\_right} : F(T) \times S \times (T \times S \to S) \to S
    //! \f]
    //!
    //! for the variant with an initial state, and
    //! \f[
    //!     \mathtt{fold\_right} : F(T) \times (T \times T \to T) \to T
    //! \f]
    //!
    //! for the variant without an initial state.
    //!
    //! @param xs
    //! The structure to fold.
    //!
    //! @param state
    //! The initial value used for folding.
    //!
    //! @param f
    //! A binary function called as `f(x, state)`, where `state` is the
    //! result accumulated so far and `x` is an element in the structure.
    //! For right folds without an initial state, the function is called as
    //! `f(x1, x2)`, where `x1` and `x2` are elements of the structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/fold_right.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto fold_right = [](auto&& xs[, auto&& state], auto&& f) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct fold_right_impl : fold_right_impl<T, when<true>> { };

    struct fold_right_t {
        template <typename Xs, typename State, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, State&& state, F&& f) const;

        template <typename Xs, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, F&& f) const;
    };

    constexpr fold_right_t fold_right{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FOLD_RIGHT_HPP

/* fold_right.hpp
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
*/