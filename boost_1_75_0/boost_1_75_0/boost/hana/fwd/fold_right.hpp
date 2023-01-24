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
GPJSEKvvhrQ/4GZ688ErQbfUK59Y39o4370RpPj+jVv3X/Fm0E35p3TQ27eu17916/qXblP/023qe31xa/qPFd+6/tLhW+Pf9HVz+W29of6p728zftWt65f+GHRLO6m61Ly+/Ib6mZeDGnVZf7lJTw7cKMfrzfHcWL+jm/SWdMzrIb0lH6E9b12/+R5erzTwdHIEt8XUCFmzey1+G6GLr/Q8xoi51rQW50fcfF0NnKdA/pZnSBUvZ3Bc7mt8/MXXmtbqA7fASX0GX28aX+h787bRAdcTYqTNfJXWIW1cs9f15T4ip2/r62Fg3GVFG1ofm62Rffl6+P01aQtaqPzXa5zXs9f4ekh/soD6jdd5v39db5JB5S34oj7vBMyB7K5bt/UGyEt5i7aB8okdz9fywHsOk+/ifE4T6Z19veleuz/138PNv4vrU+Zdrcfid/qaaCq/BU3+mOY0+qwrlN52fam7q2l9EfqJ+59+N49/yS5eeEzaIr6O79c8xnH7WsbXmSL+5FvgJ//13ZO3p3tTvya6i0S8FbfAWwM88atuj1eIbMKriOR4IyJvjpfsteyp2+NNDsCbLuJdcAu8NH8zlt0e75YAvMUi3spb4C0CnutL+PxRWXuxPqQ/x0P3KxL7czzh/W+9L3zXx/X5Qx/X/R0+HseW+Ljd7vPxfeFBH98XnvTxfaFXvD7qa7k/pPWh+glpizh/U/+mfXqd
*/