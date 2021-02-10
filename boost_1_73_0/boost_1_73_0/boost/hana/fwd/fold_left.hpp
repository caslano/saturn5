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
udz8HTV97E18LyGrJt4MrexUMVKHAbZoRrD/LY/LzLH8dFjkSDIqs/9TVGSTkx0UOe1KMQlNbCwknN4RUz1ViJDIhpbN56aul/jXKCp3gnHWCPWCu0cQDjfZdL8ddc332Gx/hefnzyLXFkdK/MCbWYJwiYQL6fLacgNSkAJ3UQpodpprK2Eq+DG1zVB1p1Cz5OHC/X01EuqlA/V0HuA1mQD0USVA7WDIXTwZCpxdcQy0wjeoulSlp5dCtd7FnAduDc5zKN8w42ud5DGkNutmjZioIwhyHNrOWCPVWlgUpchEDV7qRikqh+RAMkZ16uL7x0g+EnhIiHQV5EeorIwmpWVUJT4rh4nchYq7aqFScvyxHhsUMDh5BfuS2bxY6ZN/WnP1kMDLDyCjnACquPHo8JGj9dDFL+8MWFBSMoLBzwjWLsHcUJYX4INCWdJmcd1m/UDhfHi8yhux/GBtvP9aO91xPaJCFn5PnvLufuxTXrjDJckPJ1l82FvqbahOEj1UqloS3Cep5wzL5C7RHgBnj5R+BSwuliXLIcn69k6q1Vl/BLQ5onmF9oWH7Usoyh9rZitgpdtK9iFumdS8vAnKOQwsy+PbN0MyNnUe1tH0wzqpHtBHGkUFLL1FSH5r7RAQWtmpYGRDhbQWkryl
*/