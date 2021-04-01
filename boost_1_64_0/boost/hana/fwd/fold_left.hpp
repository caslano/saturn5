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
xWY75CxEboNamhZN+uXL8JiAOs8nwv0hhtr6RIyh9sdNdnnxTjD3nKuSrbsY4IDE3NjycpNtc3Qe640Mgt4ECY9BJM3k0HG4LiN7chPF/1deICvyl0BTVDWB0ofIipxEOba3ELZHNhD8F4yypnKFzMNoAqz6j/DgVmQAJapRVzu+8DsU6xwlyNtdxzy5RrHeu6JSr4o2xgLQ39U9ipQly3+ACfHEP6lzaFAdrtrdl0nYPYMj1kNy8zN5bfl7TiTACHMC380XJvdTsy1VMvIYWSSFtNkD3jfH4G2A4stCJmiTHE1WPeCUo/S9hYxisl6ajOds5PSTBjJuTmBkW0g1PCucccdut/hN4EX9jBCP5x12cydFxYdY+6s9GYk4zPggfA9+1JqESMfyvrpIN1ScSWR74ojNxzQw9v4aLflw2pkeF3xhkBk8nJTx+2OjJ9QX6N6wZ7f/XwUvV08FskpnpLPt9YoBzwUxS1ekq7+kaYd+Re/l5KfM+FYzcXBwycH6gCPCytx+jZ2XEoAIk6Y0hFpmDOw3B0i7odzNFvaqO1WTKFdcoWX4w89Mmg==
*/