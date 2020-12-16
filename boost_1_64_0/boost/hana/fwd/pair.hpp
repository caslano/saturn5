/*!
@file
Forward declares `boost::hana::pair`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PAIR_HPP
#define BOOST_HANA_FWD_PAIR_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/core/make.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-datatypes
    //! Generic container for two elements.
    //!
    //! `hana::pair` is conceptually the same as `std::pair`. However,
    //! `hana::pair` automatically compresses the storage of empty types,
    //! and as a result it does not have the `.first` and `.second` members.
    //! Instead, one must use the `hana::first` and `hana::second` free
    //! functions to access the elements of a pair.
    //!
    //! @note
    //! When you use a container, remember not to make assumptions about its
    //! representation, unless the documentation gives you those guarantees.
    //! More details [in the tutorial](@ref tutorial-containers-types).
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! 1. `Comparable`\n
    //! Two pairs `(x, y)` and `(x', y')` are equal if and only if both
    //! `x == x'` and `y == y'`.
    //! @include example/pair/comparable.cpp
    //!
    //! 2. `Orderable`\n
    //! Pairs are ordered as-if they were 2-element tuples, using a
    //! lexicographical ordering.
    //! @include example/pair/orderable.cpp
    //!
    //! 3. `Foldable`\n
    //! Folding a pair is equivalent to folding a 2-element tuple. In other
    //! words:
    //! @code
    //!     fold_left(make_pair(x, y), s, f) == f(f(s, x), y)
    //!     fold_right(make_pair(x, y), s, f) == f(x, f(y, s))
    //! @endcode
    //! Example:
    //! @include example/pair/foldable.cpp
    //!
    //! 4. `Product`\n
    //! The model of `Product` is the simplest one possible; the first element
    //! of a pair `(x, y)` is `x`, and its second element is `y`.
    //! @include example/pair/product.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename First, typename Second>
    struct pair {
        //! Default constructs the `pair`. Only exists when both elements
        //! of the pair are default constructible.
        constexpr pair();

        //! Initialize each element of the pair with the corresponding element.
        //! Only exists when both elements of the pair are copy-constructible.
        constexpr pair(First const& first, Second const& second);

        //! Initialize both elements of the pair by perfect-forwarding the
        //! corresponding argument. Only exists when both arguments are
        //! implicitly-convertible to the corresponding element of the pair.
        template <typename T, typename U>
        constexpr pair(T&& t, U&& u);

        //! Copy-initialize a pair from another pair. Only exists when both
        //! elements of the source pair are implicitly convertible to the
        //! corresponding element of the constructed pair.
        template <typename T, typename U>
        constexpr pair(pair<T, U> const& other);

        //! Move-initialize a pair from another pair. Only exists when both
        //! elements of the source pair are implicitly convertible to the
        //! corresponding element of the constructed pair.
        template <typename T, typename U>
        constexpr pair(pair<T, U>&& other);

        //! Assign a pair to another pair. Only exists when both elements
        //! of the destination pair are assignable from the corresponding
        //! element in the source pair.
        template <typename T, typename U>
        constexpr pair& operator=(pair<T, U> const& other);

        //! Move-assign a pair to another pair. Only exists when both elements
        //! of the destination pair are move-assignable from the corresponding
        //! element in the source pair.
        template <typename T, typename U>
        constexpr pair& operator=(pair<T, U>&& other);

        //! Equivalent to `hana::equal`
        template <typename X, typename Y>
        friend constexpr auto operator==(X&& x, Y&& y);

        //! Equivalent to `hana::not_equal`
        template <typename X, typename Y>
        friend constexpr auto operator!=(X&& x, Y&& y);

        //! Equivalent to `hana::less`
        template <typename X, typename Y>
        friend constexpr auto operator<(X&& x, Y&& y);

        //! Equivalent to `hana::greater`
        template <typename X, typename Y>
        friend constexpr auto operator>(X&& x, Y&& y);

        //! Equivalent to `hana::less_equal`
        template <typename X, typename Y>
        friend constexpr auto operator<=(X&& x, Y&& y);

        //! Equivalent to `hana::greater_equal`
        template <typename X, typename Y>
        friend constexpr auto operator>=(X&& x, Y&& y);
    };
#else
    template <typename First, typename Second>
    struct pair;
#endif

    //! Tag representing `hana::pair`.
    //! @relates hana::pair
    struct pair_tag { };

#ifdef BOOST_HANA_DOXYGEN_INVOKED
    //! Creates a `hana::pair` with the given elements.
    //! @relates hana::pair
    //!
    //!
    //! Example
    //! -------
    //! @include example/pair/make.cpp
    template <>
    constexpr auto make<pair_tag> = [](auto&& first, auto&& second)
        -> hana::pair<std::decay_t<decltype(first)>, std::decay_t<decltype(second)>>
    {
        return {forwarded(first), forwarded(second)};
    };
#endif

    //! Alias to `make<pair_tag>`; provided for convenience.
    //! @relates hana::pair
    //!
    //! Example
    //! -------
    //! @include example/pair/make.cpp
    constexpr auto make_pair = make<pair_tag>;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_PAIR_HPP

/* pair.hpp
b0xbVV+h18v5qvjzzw3jXP9KtziAgdzYTeIX04KGn0BD6HvnQrf4831xkePiIt2IvCs+MseMFB9OiQtPl+GHYpc052clv0mcr92xIvH908T1BHHdamXfFne0Yd8W0yhePL62Hfsy4+Z8SpOgn2+4vh393PR/myfRKXoFPeTJdKJ2CQ1iL9Eg9ktiq0VyELvwxvilGX0GzSAdzSn6HJjnHOrcIZpRdhOVD/OMEiumftEzQLU+8LTpSxjsQ1OelVwtO4vjL6eyIfjL2zlI7nhvPGSUq/Z8Mtdsz5myPY8ltqdatmfJ6tbtSYOl0WiSM7FJdz8Ua9LNM3iTVMsmvXhdrElzZ3CT+v6AJsn11qhHOGMNyqEGndQOgZ5YpRqExfPhcRSabVCoC69ol8q127Xo+aS5Svl9hly/9d/P9aV1E2cpaWQPaKp7nk5LuIsfUKucb8Gr4nalQ51REdaw7h43FYInZ42qJOv8sJ1zJR2yktBufuiJHHze2ZU/jZ1UZWmQjtryhAu5LSCuBJ85FX9skTn6VXXnkG0scnglKxH+kT812kjQyWgl24iVMDHp7oMdp6H0w4VAUjH75frFB0tMl+zKFMNvxcrTB+Bw1p48R0bwCs1iw5RC3LparU44yOQVmMuYDExtojUBHyxnLjqMywrTGVYXyKuJ92RBntYFpfSC1xqH5QgLUlDb88BK90Al0a04YYasOOXwE14T5EacfRSUpoX5JAB6hvZ1mXsWDqjY+ngXqKlidiXXxPAPCSQh6C7mAocRVCYtcPysrUxSRL+V6D0NFO+90mBLI/2vAbcaX/pdg+9qfu54f8qhfuRWTEI97UC06V81D/cL/2KDnsYN8TxPEAuhODf3Ds0DAdLYHUtc+gS3urm7WHIZdfaeT0kG2U2LOCF5ctC82Qira0YwoawYKBv6ZBcnHJnJAUVYfw6YvfzizPn47e4Xn03Hb4pfrFU1CHb3ecXaCikgkAVMMcwnnrrJmIBQUKA8DpfTgcvNKxiXRmyeZIqFHPWUjKrgfvXbJ7o4X8D3XXytqNQG/L7+xN8Xx0rezpwlWYicVhcOC/7EYKFzgY+cp+iME5tcy8dsHmqx8eiAL6TxaIs9uigB82KwH0JCg2zBLK02KUHYLTb8v66Pl94MEOU0Pok24rsF36jx/PsnD6/d3P+vTVHbzqx6on2n9X4PlteePehm5TM7J7Gj1yVK7PGQDCyxJ9hCDdigG5PYHkhs291K2/bSfA6B4oE7jZXD0NVJSZX9IOO7iX33GrvmzsXEyCdOXaYk+Al4F1+EpB7uKRJr7lLCfE1FGXOtljE2CaafO7gg+w+U0RBsjA/aujt6homQsxgh7YzJn0UUQsoayO9dwzYFDMobaFC+0hba4Fy6i3FS1lDsB1wg5fM7FVJGU4hYfQfLWGAkVyHkL/cYCMnD5BUHMF6rEHIi3sWv5PIO8haJu+9UGHmqYoK+EZXQggMJI5G7JEYmUNmHiRHmpy0LYuOVDWYOsNRgS9qqtuyGPmmMxXBg2Ot574EcEFINDy6/V/S6xVRDeP0dPXLfb7gZ5lI7AW8PfuGC2HrAebyFPXgMQDwmxZA0eDEYqQj1EytnkSLEG2fdTEO5YPALScAfL49bMCjHikFGp9cHgOUaErVvPBSr0YV+7IQfDYnpC6eIW+abHgXQ7M5NqswWXagyqbQg11Zl7tS5Mnw0hZ5Klen4lAr1UfPnF29E4TxppoNseFYgMsrljmgxB9YizS4H3/5YxPtzRFY9HVUv5fkkMszziaqVnCFT9K6mFuawJu3ObQyOYxXdxqEF7KZjR2iuTzw7QUJGaTdEYr7iD2kFqpnSY2o2mvlMjYFzmk4=
*/