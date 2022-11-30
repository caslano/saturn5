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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr reverse_fold_t reverse_fold{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_REVERSE_FOLD_HPP

/* reverse_fold.hpp
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
*/