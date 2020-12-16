/*!
@file
Forward declares `boost::hana::monadic_fold_right`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MONADIC_FOLD_RIGHT_HPP
#define BOOST_HANA_FWD_MONADIC_FOLD_RIGHT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Monadic right-fold of a structure with a binary operation and an
    //! optional initial reduction state.
    //! @ingroup group-Foldable
    //!
    //! @note
    //! This assumes the reader to be accustomed to non-monadic right-folds as
    //! explained by `hana::fold_right`, and to have read the [primer]
    //! (@ref monadic-folds) on monadic folds.
    //!
    //! `monadic_fold_right<M>` is a right-associative monadic fold. Given a
    //! structure containing `x1, ..., xn`, a function `f` and an optional
    //! initial state, `monadic_fold_right<M>` applies `f` as follows
    //! @code
    //!     // with state
    //!     (f(x1, -) | (f(x2, -) | (f(x3, -) | (... | f(xn, state)))))
    //!
    //!     // without state
    //!     (f(x1, -) | (f(x2, -) | (f(x3, -) | (... | f(xn-1, xn)))))
    //! @endcode
    //!
    //! where `f(xk, -)` denotes the partial application of `f` to `xk`,
    //! and `|` is just the operator version of the monadic `chain`.
    //! It is worth noting that the order in which the binary function should
    //! expect its arguments is reversed from `monadic_fold_left<M>`.
    //!
    //! When the structure is empty, one of two things may happen. If an
    //! initial state was provided, it is lifted to the given Monad and
    //! returned as-is. Otherwise, if the no-state version of the function
    //! was used, an error is triggered. When the stucture contains a single
    //! element and the no-state version of the function was used, that
    //! single element is lifted into the given Monad and returned as is.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Monad` `M`, a `Foldable` `F`, an initial state of tag `S`,
    //! and a function @f$ f : T \times S \to M(S) @f$, the signatures of
    //! `monadic_fold_right<M>` are
    //! \f[
    //!     \mathtt{monadic\_fold\_right}_M :
    //!         F(T) \times S \times (T \times S \to M(S)) \to M(S)
    //! \f]
    //!
    //! for the version with an initial state, and
    //! \f[
    //!     \mathtt{monadic\_fold\_right}_M :
    //!         F(T) \times (T \times T \to M(T)) \to M(T)
    //! \f]
    //!
    //! for the version without an initial state.
    //!
    //! @tparam M
    //! The Monad representing the monadic context in which the fold happens.
    //! The return type of `f` must be in that Monad.
    //!
    //! @param xs
    //! The structure to fold.
    //!
    //! @param state
    //! The initial value used for folding. If the structure is empty, this
    //! value is lifted in to the `M` Monad and then returned as-is.
    //!
    //! @param f
    //! A binary function called as `f(x, state)`, where `state` is the result
    //! accumulated so far and `x` is an element in the structure. The
    //! function must return its result inside the `M` Monad.
    //!
    //!
    //! Example
    //! -------
    //! @include example/monadic_fold_right.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename M>
    constexpr auto monadic_fold_right = [](auto&& xs[, auto&& state], auto&& f) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct monadic_fold_right_impl : monadic_fold_right_impl<T, when<true>> { };

    template <typename M>
    struct monadic_fold_right_t {
        template <typename Xs, typename State, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, State&& state, F&& f) const;

        template <typename Xs, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, F&& f) const;
    };

    template <typename M>
    constexpr monadic_fold_right_t<M> monadic_fold_right{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MONADIC_FOLD_RIGHT_HPP

/* monadic_fold_right.hpp
OKQgtSCkT1Unprm3qS+H2pFzA/1C++8lNWu5J83ldGcFPRkuJ4Um0XOKC4nIpGEKvaUi5uh8ZCPbtZwyuV1GiiR6TpN5J6bghQqC/cJ3ktxbQrus7p3mNvdb7jUkiXJ/rBalutsUPFIDv7R2fXabko5tUxfatA1twrbUvUEtSnavUfD4FbbJeWSb3DvRKgkn0kGhNrmoTV8pnKzHhZMyD+WtcW8bhFkFlS91HkC2TsHLqbYq+bRalXRcQNG9KTTqLR1YFgmsr65ZALLRMPcWNI2g9bq5DY3ar5CHw3yQg8VvgrtVZ3ZS5v7qFmjaDNwzcEPQfrs272buVos+tRWjC+0KQoDAtSLPtkbd4n6N0u5V2F0rPmuRf+AGxmXkHoQcalGGu/grnbHH6e/OI2ds6glmrNYgVPFlt+noydGFVv3nYHYUTv9hmM1wimK2Diu7ASvnqbbLeVrtSjo+qAxAWQhMBLmvrknbToDVwDmJ03UZ8hwkmUnQXCy5neyncgLePLt5kZv5qdoQEkn1Jvpx1g/jX2v9sNj6ErO6RW2oL4mn6GEWLb4Hx6uv1g+LUxs5xopfiumJX8p5BlJQuJ1zEH0prx/WS21QsJsuQ4op9dfb6of1ri9xnIxk8uu/r/+O/ZP3b/6YK+/fSOlJKpjcsx1PFZhCO6zu9XiI1R/M/KAkOJ4qs+C1B3GgW8mCNl7i+AUP8TL0eqRYYMV7T+KGO0mNEy9n8AsebDK0GiluteO9V+g9q1vgobf+4OAHsOtspV252Q75aQzdkPZRdQl6m87UHxJl40pS0DoX3s/SG3S2/nAOP1CJq6nE61Oreqldarjj1Y7NSnVaeBganIRk5+pt7KM/9OUHpEFjk/F+nt7GfvpDf35wJ7ivt7irrcrNGe6b7QQY6nbNJwunP/Szmj3qsldyCJXR/Fb6RddXqyBXTM/qiDwxwuNZ0rMGPDG1atTyNGp57EGmZXYjNgnPkpY14okpGfy+Jrnb3PuJ5jerr7pDNZ9MFHc85RbcAvUtlFez5/FZjxafVEvItf3ptIYost6iWHebOt5CejrukHsrN5Abp1CaBneICeomd2vNJ5df9VGz+ppC7w01e164a1z7KQDtdJuqN3O4FWALqePt7s5ubST+t0GC8RFvZMKRYEy+bdPHIMtQtzu59jm/QPvQuA1qMxqFpmFgcSIBaO7WscRRdyhWSujVBiz7IiHUnqB4ncosV2iHw7ZGuTNJfVX5dnLofUdoZ4Jti3JdprpX8WaFPgCyOWwitCvB1qF8O1eZlQ3ECHGP3nGob4c+SrDtD32YQAppyGvbhdJIzIoKEG9rDYUTbK8rY4uVBXnqZqUsn53yJmGV/YDqCb3rsG1Sbi0ioSTaY1uHutQDim8aFXtIGTtV3YmC1A4USkm3Uis+odpCyE/1b6LGtiON7VUkULuQ5KN+pJ2PLrb3UzxzlYnzlJmVSsVMzZqBrVPdo6mrhnb1s+2GUEhtkh6c2ei/bUNI9FPXoZx2B4ApHMrzP6O0HyTYWpQnf0nEoW41pW1EXOj9BFuz8uBvOPRFCm1Qlj9Gyd9NQDQK2ZFg26A82EpRUyzQtgfklr+CNzT8HQb0Bmr2GKv6MXVtD3V2il09gEjuL0NXKU1R1yhVqWjOjn4hEWtbH2qPVVtC7/dT5qcpUzIQhH580E9tVEo99NIZeref7TWlagKaM38iDUgbAXcNxkd9FVXwAAOA6h5lymQeWK5MqapQu5QpMwDcjwBc1Izm01RxABaUOwFGyJ+nuRTa6bBtQR+RZ3m99LRM8+pjQCm0y4F58uASCu0KhR0oAuMfJI0NQj8UGxIcuB6VoG8IU5azgv06dYvyJCk=
*/