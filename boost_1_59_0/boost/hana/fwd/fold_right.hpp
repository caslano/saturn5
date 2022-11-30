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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr fold_right_t fold_right{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_FOLD_RIGHT_HPP

/* fold_right.hpp
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
*/