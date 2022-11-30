/*!
@file
Forward declares `boost::hana::set`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SET_HPP
#define BOOST_HANA_FWD_SET_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/core/to.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/erase_key.hpp>


namespace boost { namespace hana {
    //! @ingroup group-datatypes
    //! Basic unordered container requiring unique, `Comparable` and
    //! `Hashable` keys.
    //!
    //! A set is an unordered container that can hold heterogeneous keys.
    //! A set requires (and ensures) that no duplicates are present when
    //! inserting new keys.
    //!
    //! @note
    //! The actual representation of a `hana::set` is implementation-defined.
    //! In particular, one should not take for granted the order of the
    //! template parameters and the presence of any additional constructors
    //! or assignment operators than what is documented. The canonical way of
    //! creating a `hana::set` is through `hana::make_set`. More details
    //! [in the tutorial](@ref tutorial-containers-types).
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! 1. `Comparable`\n
    //! Two sets are equal iff they contain the same elements, regardless of
    //! the order.
    //! @include example/set/comparable.cpp
    //!
    //! 2. Foldable\n
    //! Folding a set is equivalent to folding the sequence of its values.
    //! However, note that the values are not required to be in any specific
    //! order, so using the folds provided here with an operation that is not
    //! both commutative and associative will yield non-deterministic behavior.
    //! @include example/set/foldable.cpp
    //!
    //! 3. Searchable\n
    //! The elements in a set act as both its keys and its values. Since the
    //! elements of a set are unique, searching for an element will return
    //! either the only element which is equal to the searched value, or
    //! `nothing`. Also note that `operator[]` can be used instead of the
    //! `at_key` function.
    //! @include example/set/searchable.cpp
    //!
    //!
    //! Conversion from any `Foldable`
    //! ------------------------------
    //! Any `Foldable` structure can be converted into a `hana::set` with
    //! `to<set_tag>`. The elements of the structure must all be compile-time
    //! `Comparable`. If the structure contains duplicate elements, only
    //! the first occurence will appear in the resulting set. More
    //! specifically, conversion from a `Foldable` is equivalent to
    //! @code
    //!     to<set_tag>(xs) == fold_left(xs, make_set(), insert)
    //! @endcode
    //!
    //! __Example__
    //! @include example/set/to.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename implementation_defined>
    struct set {
        //! Default-construct a set. This constructor only exists when all the
        //! elements of the set are default-constructible.
        constexpr set() = default;

        //! Copy-construct a set from another set. This constructor only
        //! exists when all the elements of the set are copy-constructible.
        constexpr set(set const& other) = default;

        //! Move-construct a set from another set. This constructor only
        //! exists when all the elements of the set are move-constructible.
        constexpr set(set&& other) = default;

        //! Equivalent to `hana::equal`
        template <typename X, typename Y>
        friend constexpr auto operator==(X&& x, Y&& y);

        //! Equivalent to `hana::not_equal`
        template <typename X, typename Y>
        friend constexpr auto operator!=(X&& x, Y&& y);

        //! Equivalent to `hana::at_key`
        template <typename Key>
        constexpr decltype(auto) operator[](Key&& key);
    };
#else
    template <typename ...Xs>
    struct set;
#endif

    //! Tag representing the `hana::set` container.
    //! @relates hana::set
    struct set_tag { };

    //! Function object for creating a `hana::set`.
    //! @relates hana::set
    //!
    //! Given zero or more values `xs...`, `make<set_tag>` returns a `set`
    //! containing those values. The values must all be compile-time
    //! `Comparable`, and no duplicate values may be provided. To create
    //! a `set` from a sequence with possible duplicates, use `to<set_tag>`
    //! instead.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/make.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <>
    constexpr auto make<set_tag> = [](auto&& ...xs) {
        return set<implementation_defined>{forwarded(xs)...};
    };
#endif

    //! Equivalent to `make<set_tag>`; provided for convenience.
    //! @relates hana::set
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/make.cpp
    BOOST_HANA_INLINE_VARIABLE constexpr auto make_set = make<set_tag>;

    //! Insert an element in a `hana::set`.
    //! @relates hana::set
    //!
    //! If the set already contains an element that compares equal, then
    //! nothing is done and the set is returned as is.
    //!
    //!
    //! @param set
    //! The set in which to insert a value.
    //!
    //! @param element
    //! The value to insert. It must be compile-time `Comparable`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/insert.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto insert = [](auto&& set, auto&& element) {
        return tag-dispatched;
    };
#endif

    //! Remove an element from a `hana::set`.
    //! @relates hana::set
    //!
    //! Returns a new set containing all the elements of the original,
    //! except the one comparing `equal` to the given element. If the set
    //! does not contain such an element, a new set equal to the original
    //! set is returned.
    //!
    //!
    //! @param set
    //! The set in which to remove a value.
    //!
    //! @param element
    //! The value to remove. It must be compile-time `Comparable`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/erase_key.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto erase_key = [](auto&& set, auto&& element) {
        return tag-dispatched;
    };
#endif

    //! Returns the union of two sets.
    //! @relates hana::set
    //!
    //! Given two sets `xs` and `ys`, `union_(xs, ys)` is a new set containing
    //! all the elements of `xs` and all the elements of `ys`, without
    //! duplicates. For any object `x`, the following holds: `x` is in
    //! `hana::union_(xs, ys)` if and only if `x` is in `xs` or `x` is in `ys`.
    //!
    //!
    //! @param xs, ys
    //! Two sets to compute the union of.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/union.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto union_ = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
    };
#endif

    //! Returns the intersection of two sets.
    //! @relates hana::set
    //!
    //! Given two sets `xs` and `ys`, `intersection(xs, ys)` is a new set
    //! containing exactly those elements that are present both in `xs` and
    //! in `ys`.
    //! In other words, the following holds for any object `x`:
    //! @code
    //!     x ^in^ intersection(xs, ys) if and only if x ^in^ xs && x ^in^ ys
    //! @endcode
    //!
    //!
    //! @param xs, ys
    //! Two sets to intersect.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/intersection.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto intersection = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
    };
#endif
    //! Equivalent to `to<set_tag>`; provided for convenience.
    //! @relates hana::set
    constexpr auto to_set = to<set_tag>;

    //! Returns the set-theoretic difference of two sets.
    //! @relates hana::set
    //!
    //! Given two sets `xs` and `ys`, `difference(xs, ys)` is a new set
    //! containing all the elements of `xs` that are _not_ contained in `ys`.
    //! For any object `x`, the following holds:
    //! @code
    //!     x ^in^ difference(xs, ys) if and only if x ^in^ xs && !(x ^in^ ys)
    //! @endcode
    //!
    //!
    //! This operation is not commutative, i.e. `difference(xs, ys)` is not
    //! necessarily the same as `difference(ys, xs)`. Indeed, consider the
    //! case where `xs` is empty and `ys` isn't. Then, `difference(xs, ys)`
    //! is empty but `difference(ys, xs)` is equal to `ys`. For the symmetric
    //! version of this operation, see `symmetric_difference`.
    //!
    //!
    //! @param xs
    //! A set param to remove values from.
    //!
    //! @param ys
    //! The set whose values are removed from `xs`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/difference.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto difference = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
};
#endif

    //! Returns the symmetric set-theoretic difference of two sets.
    //! @relates hana::set
    //!
    //! Given two sets `xs` and `ys`, `symmetric_difference(xs, ys)` is a new
    //! set containing all the elements of `xs` that are not contained in `ys`,
    //! and all the elements of `ys` that are not contained in `xs`. The
    //! symmetric difference of two sets satisfies the following:
    //! @code
    //!     symmetric_difference(xs, ys) == union_(difference(xs, ys), difference(ys, xs))
    //! @endcode
    //!
    //!
    //! @param xs, ys
    //! Two sets to compute the symmetric difference of.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/symmetric_difference.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
constexpr auto symmetric_difference = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
    };
#endif


}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_SET_HPP

/* set.hpp
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
*/