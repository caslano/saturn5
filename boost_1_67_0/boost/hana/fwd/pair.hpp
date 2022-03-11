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
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
*/