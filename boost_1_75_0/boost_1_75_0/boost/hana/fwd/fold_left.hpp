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
FOnefJWPu/Uqp3tXQDv/+JvQX1YgaeGD8sXxiaYKcfw1Nxnff/3BFS63bVf4+J9faZ3fjMckLWy0ThyP5GW8g48n3HHr8a6Le4Q24nidrnB+u1/h/Pa5wufp7it8nu69wudJ3wpd1bi2Psnp8vtotv+7o7kdnLvSfJ9L420W6V3XCr2B+8t3lrfEX3MD/t5XW+IPDef462+Bn3xohKe5P1jukTTuobeGi/4/vHV/EKh7yWKbwP14fHjr/iBR1LVkUdemi7qWfrX1PcaihqY9xoXwW8fvbzdwHB80NO35Inrcel/QWp3/L1hoHoc9v7i5vK4uljTa3KkeXF67erQur0Bfv1xsEyjDBT1al9dsUVdzRV199Mqt18WfNzSncfzrTXO6vCencXrP289pVM+Wc9q7Z+s0VjVwGqtFv1Uj+r26hpa0XhfTyhuu57/Jdf1m9baNkkZcSuT95UcC2vV4S6IwvtUcT1Vg/SaJImpT8/ojN4xz5r3m9RUB9bb3JYqU90Vf9DFP1/fiMt2EtBxAhUduWHtofZn3EW9f10rd8Y+a46zrxfc2Qm/4WxEva2tv2ffdj27O7x/Ad/XjW8u192Fef/iQRHHiUJNcN97Q7t6DvN2CSoniicrmOlaJukCbDahq1K01vWWNNrmhN/dPW3q31MPW6KzbK1Fc2HtzPl+pkCher2guQ+2d4r3gO5vkp21Ffv/4hrc/dRN9
*/