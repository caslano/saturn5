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
a3sRiAR5zujzNA/dY4eoWG3W9b15HfreIiOERHhOt9BZrbpkyCQ9LnpwgK78Leqk/M2A16oLn1gduN7OnHcGxkKeJjPFjHtY8UubfZOK33NQ+1J1Ikdg0zYVXLU2p+ex4pfXEZhTSFm4zmbeCms++GhfI/BwzEbIWVxJAzcm4tyHaCK+DVPkSx2TptAnTe0tGeChLPRkfTre7fo7PalFCUlKk3KInsRDN8DxO/S2fjFtySkxQBU5ayyQHiOqfW6T2Cs2IhJDfpUpGuSZoNgivypOIXly0KqrG0kvgPvod9LtGJjO806vIdAIy9yZ0jI0SsvooLRIcxsTQfRvRGHFnfTLec0gZdYvS/qai+dnk/S1uzt9IYDpi19SWA8NIJPU1daJutqIuvx8jM/z3ycGjPFKbHdSzZwR7ddVAQ+USBX8FiCWo3Q9M0+WAd2sgHogMuI61U3mw7iYAXK1WricBKhtV899hh5d+s3JfYZ7TAnVCYXk4FsbhoEcxiaVCIxS1dJa/DGAItq/x2pob8NMu0qE3GxT2FDdxbzGs0zcCdviySDqWSDqm1jfTCnx5kq+2bW3qPHUKmlmYtVdRF2glqidWY2OJTHS8aI4WsYENlkjsMlMYGVWSV1DDSO+bnVdBtcfLgXuxIPYMw53CO4g3NFvWl0Cbj/cbrhdcFvg4nCPf/MD3uBC/fj8NFrWYIcsN51Ficu5fCPN5du4mZV1NDtuo7l8I6UxIQ3PoEhjkmnsmFR5nkUqO6XaLpCIp3KhtMS3XtaQblD2xrdcxlek0W5nZ+1sGxkwW9Sxyq74ZovyhrqZMk+N7J8UbxkQOTBJdTTsf9jtUhx1+7/ndnHBFHdoMIV8ByGYzAcghLzfl95Uzftd9sr0r3L6b1NGD+z/IT0e3f8DxAcdyh51MeYqKvx1rXCUjG/eg8LdSou62NW55lxnzuWkwlGszO88FZ5ONfdoNX+v0e6lmmf0qs17VzKQdcrCs6jmmRep5jlU82yt5u81weVRzXOVncrrKP69rnkh1Ty/V21+/gqfRjUv6dTmKBZZoOTI/rMjOMByroWXU839F6nmc6jmsy4otXcpGUXOZ2i4fKr5PBhCvnERCG4B1TzUqzY/f4VXU80X9jS2ayXj6wtV+OIlanBpSwBTK57wXSTKqyb8L7xIc+sCwn/oIs2t86nm8y5onztdh0fNZ/WqzXtX8unm1nKquf8i1Xwa1bzkIs2thVTz/Is0t+ZRzXN71ebnr/Acqnl2r8bZ8ze3ZlHNMy9Szb1U84wLSu3d59b0rnOr5yLNrW6quatXbX7+CndQze0XZ24di9WqsifZzeNbzCgcpeh1r7qwlUfNoX6LbzWr67G6bpKS7t2QdAsW+inr5Qpc0Ap8t7oemSERr9N3Y50uU+H6R6zlKY0LabaSpHtLJ0l3pbJVaZobM8WmWM7Tgbsf/D74ffD7n/mxcsrBWkCPOtegfsoCmR7EeyzW6yTSu6DzYm9mh/eQC+wyL77Xy4505gj+e3ih3pV8aPD7lAuU/O9FWudKzv8icYFyzdOrNj9/hXdZ7Z0dC3r+lh0XdZ17Div83hZ+GpEeyzYu0jpXSnV61ebnr/Au8qz3eNnRXaR3kShPSjUv0twq5bkXaW6dz5LsC9rnzqsMv3clHxr8PtVeSL3NRZpbpcbqIs2tUlfXqzY/f4VLLWWvxtnzN7deVP3sOWime1v4aUR6rJO/SHOrtEboVZufv8KlHcbFmVtZpNeS7Obxre+tSA+mN2j3SkgSY5lzY7M+ELp98Pvg97/8k/bzbMrufg/t5/dM1WzmvbgoBe8MQE5QxKf+t9vP8302v/x8F/v5AOzmKzW7+ZBR3UU=
*/