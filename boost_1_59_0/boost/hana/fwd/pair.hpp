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


namespace boost { namespace hana {
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
    BOOST_HANA_INLINE_VARIABLE constexpr auto make_pair = make<pair_tag>;
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_PAIR_HPP

/* pair.hpp
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
*/