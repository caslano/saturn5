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
iqqlSorzxxoCBSx3jdK4H0JcqDgZ9cwP/YvRoPsmIlO/G8Jmn4koW5Q+q0UprcAlmyt1Gdcjx9nkhC1lJn6KtzQcx45/VrGjaU8p6aRPqn3Gb48kJq1fFkk8ocLxZ0/Tj6X00OpRwyeWrWDM7RZcM2rD7jSYt6LTyowFOPMUwAiQ0pRaSj7VhmstjTft7sangiz9qWd79bxqA+VuY5rUvCUTmoE1qqq+KRQnjHFq9jG9x8t5zG35FhLszm28aNxPMsttfTwqt4PnL450vblsOiU+YFIxH9MK4S5ZWDrWTqWz37N8yRpBDhSxS8jfFXDo72tw/tUbDhobAPjr0TOF79ryqXrt78biII1OAwEewUVNvssX4w39loHN3BYdgZm8snWg9XhRhrU0k3/bO5JrbCrb6LPDFzLb8jsWbIS42taO4RCV1esJ+/vyldHozslJdGd/3zCa6pgh/6hXn8K6e8ASdciHIiCXzHgVz+TUE8z5yWmMOuSjKqfV3zL8D1BLAwQKAAAACAAtZ0pS5tOQg9YDAABhCgAAGgAJAGN1cmwtbWFzdGVyL2xpYi93YXJubGVzcy5oVVQFAAG2SCRgrVbxb+I2FP6dv+LpkE4BZc2u98tuq05jQNfoGFQE1HWqZIXEabwGG8V2S1H/
*/