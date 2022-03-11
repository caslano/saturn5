/*!
@file
Forward declares `boost::hana::reverse_fold`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REVERSE_FOLD_HPP
#define BOOST_HANA_FWD_REVERSE_FOLD_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Equivalent to `reverse_fold` in Boost.Fusion and Boost.MPL.
    //! @ingroup group-Foldable
    //!
    //! This method has the same semantics as `reverse_fold` in Boost.Fusion
    //! and Boost.MPL, with the extension that an initial state is not
    //! required. This method is equivalent to `fold_right`, except that
    //! the accumulating function must take its arguments in reverse order,
    //! to match the order used in Fusion. In other words,
    //! @code
    //!     reverse_fold(sequence, state, f) == fold_right(sequence, state, flip(f))
    //!     reverse_fold(sequence, f) == fold_right(sequence, flip(f))
    //! @endcode
    //!
    //! @note
    //! This method is a convenience alias to `fold_right`. As an alias,
    //! `reverse_fold` is not tag-dispatched on its own and `fold_right`
    //! should be customized instead.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Foldable` `F` and an optional initial state of tag `S`,
    //! the signatures for `reverse_fold` are
    //! \f[
    //!     \mathtt{reverse\_fold} : F(T) \times S \times (S \times T \to S) \to S
    //! \f]
    //!
    //! for the variant with an initial state, and
    //! \f[
    //!     \mathtt{reverse\_fold} : F(T) \times (T \times T \to T) \to T
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
    //! A binary function called as `f(state, x)`, where `state` is the
    //! result accumulated so far and `x` is an element in the structure.
    //! For reverse folds without an initial state, the function is called as
    //! `f(x1, x2)`, where `x1` and `x2` are elements of the structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/reverse_fold.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto reverse_fold = [](auto&& xs[, auto&& state], auto&& f) -> decltype(auto) {
        return fold_right(forwarded(xs), forwarded(state), flip(forwarded(f)));
    };
#else
    struct reverse_fold_t {
        template <typename Xs, typename S, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, S&& s, F&& f) const;

        template <typename Xs, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, F&& f) const;
    };

    constexpr reverse_fold_t reverse_fold{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REVERSE_FOLD_HPP

/* reverse_fold.hpp
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
*/