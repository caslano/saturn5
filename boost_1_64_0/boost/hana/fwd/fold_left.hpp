/*!
@file
Forward declares `boost::hana::fold_left`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FOLD_LEFT_HPP
#define BOOST_HANA_FWD_FOLD_LEFT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Left-fold of a structure using a binary operation and an optional
    //! initial reduction state.
    //! @ingroup group-Foldable
    //!
    //! `fold_left` is a left-associative fold using a binary operation.
    //! Given a structure containing `x1, ..., xn`, a function `f` and
    //! an optional initial state, `fold_left` applies `f` as follows
    //! @code
    //!     f(... f(f(f(x1, x2), x3), x4) ..., xn) // without state
    //!     f(... f(f(f(f(state, x1), x2), x3), x4) ..., xn) // with state
    //! @endcode
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
    //! the signatures for `fold_left` are
    //! \f[
    //!     \mathtt{fold\_left} : F(T) \times S \times (S \times T \to S) \to S
    //! \f]
    //!
    //! for the variant with an initial state, and
    //! \f[
    //!     \mathtt{fold\_left} : F(T) \times (T \times T \to T) \to T
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
    //! For left folds without an initial state, the function is called as
    //! `f(x1, x2)`, where `x1` and `x2` are elements of the structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/fold_left.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto fold_left = [](auto&& xs[, auto&& state], auto&& f) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct fold_left_impl : fold_left_impl<T, when<true>> { };

    struct fold_left_t {
        template <typename Xs, typename State, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, State&& state, F&& f) const;

        template <typename Xs, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, F&& f) const;
    };

    constexpr fold_left_t fold_left{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FOLD_LEFT_HPP

/* fold_left.hpp
Vwo7XRJPrlQT/nc9wYKJgKIW/9kERTMuPkK7cMsx/O+2tY2gV0obRW1dmlPnMwJbxmyi+fXbT+m6EFqFIlL6JHkxWkCpZkq52GcgUN2bL67j0ffcG2Lfj5WJb2Xm1eo9Atx4FdqPwsHs8OqczlQLZXOeEFyPcrVTycfBPi1BVExsW2rn3vq9E/FS39I9Wj9IX8CXbxFOAb8Efo4mSBVinUhumogWpekyvmmmp9ytp7xDS7mGMftMPcqzepTbtShXJ0V5XURJvOlW3H8N/joZA/dHLYGviTO0coalWoYkOp8OtKRzBkvLt7qqo002NyapclWRkM7LDC/BPvzWqvF1Sn2Rpm7mHJ+tVnl2PCNNSGqOv0hxvOtnVHtjnbJpHLLQTKvdDc9a5VaMEOT2nDg11Crvz2LH/hxEcy0R2hnOdyve8wWSIqwHkqyhbSSXBNcZJLdYV6scOUf1CWThckVZndI7jxPp7TK2Bqu9StfVjISFXYuUorOFJTGX9GujPu56pbmN9g2ZGO065Z3zEvKCsB9Nril17Mud86pXgzJnkvPxxARkAwH0bIS01jvDEAZWNuZoe8M+n7FWmcfVqg27ypQt2Wq1KsS8S7iUsnnbeybH1L+aHHfjycDafh3vw3j2/v+X8IN8+107hP3L+SfJD5U7DIBkAx0N+afTY0nUHCqM/UMg2T2Et1BfI7IWW96ncErAhkhOqKCBA1N28L2UfrQdsNzn17H8+CxlM6iSMlW5tep1rEK5KVe9tUILZjPedD+bmBTrhbg33S2Y7LIEVvqGeJV5+bRsHMit5IDdFQHSTXoHQICJ4EbP9ANhJJXB1ww68vtabdl00WeOw+46anbZvFh013yL70BdFLT6zzIGbYhZ4nIE0lQUwfxOt/aZ/1qgjdBYzhn/ito/PPvrpB9vYjYSpGudpQrCEqWSAActcGr+d8Upi9WPAeoyBhRqtuBaAveQfwwzmcSwr2Ea08XVGjmG70F6IZDkKHk2cAbECJWx47gYNSx/T0lHrb2qgw1KHQAODh6wuQoCWo6S7Teb8rdTfx3OP1SyR56baXe9Z97lqatRxn8TMuorSEYd1yVfDdCcyZnfcHruSmr0R0817p16p9AOsSKfDq3H+dDqxotm5SjpB3qbVzNzfXKVrvwmIsQyA6OkH+mR1nKkzCqdcRSZHHSg6x5GDH1ah0oYOKlIYjjo0BBEzC6kIHmHGsUHcKkSw3oPwLdG6Uvh9cFx4YH62df7+U6XBTupD19In++yIgxYEP5rV8c4BTstOlasFfMcUxUojaYbsEaZy342vSrN1pPjjLRqcQTi002S0aoQblE7T2VuUTm1iKZVQ7jcoZYs6OVbkQIkMrDsy6xqJt8VktwiRXaDXJ2LFtVrCdV0z4h0RHYFfxiO0EoL0vrwpfVj4+bHjpkcYzGIB/B+Fc9beE4cNTkc8DPg+RK+U+Fnw3MeniI8c/EswrMcTwjPV/F8D08dnp8gvsGYST+TmdT9Z/7LflaYGLBlwKrx8DPO3Puf+huM/jTr6AfTn5ivS1grxx56RTKPlMM3aeHdl/cb/iUt/EkRLtZav0XWerzSAizfop6ig8rfFglkl9g6K9lb+f2i2MHmOgFF/Zm1blZu4VU+K/KHH6sEwDvLZxCBHmWOHljgQaU2corJuieoN+rFERB1IN+KdRG+FPxorxIAYcoDrWc34E3+ZAi0Jz7Sx2BL83mUeRZjpBMmDbqtBBCE/q/p8WwkVTdEprSZW7NupkAHHHFcKrlj0P2a8AFingVGS2/HFbcGxXWWx4qLiDMjnwXcSuZMMayD1H+UOZbhWmTYVN5v/e/g+rdX6/XXOS8frv4ZccV9DsU=
*/