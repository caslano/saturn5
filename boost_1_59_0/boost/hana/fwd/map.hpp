/*!
@file
Forward declares `boost::hana::map`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MAP_HPP
#define BOOST_HANA_FWD_MAP_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/core/to.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/erase_key.hpp>
#include <boost/hana/fwd/insert.hpp>
#include <boost/hana/fwd/keys.hpp>


namespace boost { namespace hana {
    //! Tag representing `hana::map`s.
    //! @relates hana::map
    struct map_tag { };

    namespace detail {
        template <typename ...Pairs>
        struct make_map_type;
    }

    //! @ingroup group-datatypes
    //! Basic associative container requiring unique, `Comparable` and
    //! `Hashable` keys.
    //!
    //! The order of the elements of the map is unspecified. Also, all the
    //! keys must be `Hashable`, and any two keys with equal hashes must be
    //! `Comparable` with each other at compile-time.
    //!
    //! @note
    //! The actual representation of a `hana::map` is an implementation
    //! detail. As such, one should not assume anything more than what is
    //! explicitly documented as being part of the interface of a map,
    //! such as:
    //! - the presence of additional constructors
    //! - the presence of additional assignment operators
    //! - the fact that `hana::map<Pairs...>` is, or is not, a dependent type
    //! .
    //! In particular, the last point is very important; `hana::map<Pairs...>`
    //! is basically equivalent to
    //! @code
    //!     decltype(hana::make_pair(std::declval<Pairs>()...))
    //! @endcode
    //! which is not something that can be pattern-matched on during template
    //! argument deduction, for example. More details [in the tutorial]
    //! (@ref tutorial-containers-types).
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! 1. `Comparable`\n
    //! Two maps are equal iff all their keys are equal and are associated
    //! to equal values.
    //! @include example/map/comparable.cpp
    //!
    //! 2. `Searchable`\n
    //! A map can be searched by its keys with a predicate yielding a
    //! compile-time `Logical`. Also note that `operator[]` can be used
    //! instead of `at_key`.
    //! @include example/map/searchable.cpp
    //!
    //! 3. `Foldable`\n
    //! Folding a map is equivalent to folding a list of the key/value pairs
    //! it contains. In particular, since that list is not guaranteed to be
    //! in any specific order, folding a map with an operation that is not
    //! both commutative and associative will yield non-deterministic behavior.
    //! @include example/map/foldable.cpp
    //!
    //!
    //! Conversion from any `Foldable`
    //! ------------------------------
    //! Any `Foldable` of `Product`s can be converted to a `hana::map` with
    //! `hana::to<hana::map_tag>` or, equivalently, `hana::to_map`. If the
    //! `Foldable` contains duplicate keys, only the value associated to the
    //! first occurence of each key is kept.
    //! @include example/map/to.cpp
    //!
    //!
    //! Example
    //! -------
    //! @include example/map/map.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename ...Pairs>
    struct map {
        //! Default-construct a map. This constructor only exists when all the
        //! elements of the map are default-constructible.
        constexpr map() = default;

        //! Copy-construct a map from another map. This constructor only
        //! exists when all the elements of the map are copy-constructible.
        constexpr map(map const& other) = default;

        //! Move-construct a map from another map. This constructor only
        //! exists when all the elements of the map are move-constructible.
        constexpr map(map&& other) = default;

        //! Construct the map from the provided pairs. `P...` must be pairs of
        //! the same type (modulo ref and cv-qualifiers), and in the same order,
        //! as those appearing in `Pairs...`. The pairs provided to this
        //! constructor are emplaced into the map's storage using perfect
        //! forwarding.
        template <typename ...P>
        explicit constexpr map(P&& ...pairs);

        //! Assign a map to another map __with the exact same type__. Only
        //! exists when all the elements of the map are copy-assignable.
        constexpr map& operator=(map const& other);

        //! Move-assign a map to another map __with the exact same type__.
        //! Only exists when all the elements of the map are move-assignable.
        constexpr map& operator=(map&& other);

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
    template <typename ...Pairs>
    using map = typename detail::make_map_type<Pairs...>::type;
#endif

    //! Function object for creating a `hana::map`.
    //! @relates hana::map
    //!
    //! Given zero or more `Product`s representing key/value associations,
    //! `make<map_tag>` returns a `hana::map` associating these keys to these
    //! values.
    //!
    //! `make<map_tag>` requires all the keys to be unique and to have
    //! different hashes. If you need to create a map with duplicate keys
    //! or with keys whose hashes might collide, use `hana::to_map` or
    //! insert `(key, value)` pairs to an empty map successively. However,
    //! be aware that doing so will be much more compile-time intensive than
    //! using `make<map_tag>`, because the uniqueness of keys will have to be
    //! enforced.
    //!
    //!
    //! Example
    //! -------
    //! @include example/map/make.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <>
    constexpr auto make<map_tag> = [](auto&& ...pairs) {
        return map<implementation_defined>{forwarded(pairs)...};
    };
#endif

    //! Alias to `make<map_tag>`; provided for convenience.
    //! @relates hana::map
    //!
    //!
    //! Example
    //! -------
    //! @include example/map/make.cpp
    BOOST_HANA_INLINE_VARIABLE constexpr auto make_map = make<map_tag>;

    //! Equivalent to `to<map_tag>`; provided for convenience.
    //! @relates hana::map
    BOOST_HANA_INLINE_VARIABLE constexpr auto to_map = to<map_tag>;

    //! Returns a `Sequence` of the keys of the map, in unspecified order.
    //! @relates hana::map
    //!
    //!
    //! Example
    //! -------
    //! @include example/map/keys.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto keys = [](auto&& map) {
        return implementation_defined;
    };
#endif

    //! Returns a `Sequence` of the values of the map, in unspecified order.
    //! @relates hana::map
    //!
    //!
    //! Example
    //! -------
    //! @include example/map/values.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto values = [](auto&& map) -> decltype(auto) {
        return implementation_defined;
    };
#else
    struct values_t {
        template <typename Map>
        constexpr decltype(auto) operator()(Map&& map) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr values_t values{};
#endif

    //! Inserts a new key/value pair in a map.
    //! @relates hana::map
    //!
    //! Given a `(key, value)` pair, `insert` inserts this new pair into a
    //! map. If the map already contains this key, nothing is done and the
    //! map is returned as-is.
    //!
    //!
    //! @param map
    //! The map in which to insert a `(key,value)` pair.
    //!
    //! @param pair
    //! An arbitrary `Product` representing a `(key, value)` pair to insert
    //! in the map. The `key` must be compile-time `Comparable`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/map/insert.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto insert = [](auto&& map, auto&& pair) {
        return tag-dispatched;
    };
#endif

    //! Removes a key/value pair from a map.
    //! @relates hana::map
    //!
    //! Returns a new `hana::map` containing all the elements of the original,
    //! except for the `(key, value)` pair whose `key` compares `equal`
    //! to the given key. If the map does not contain such an element,
    //! a new map equal to the original is returned.
    //!
    //!
    //! @param map
    //! The map in which to erase a `key`.
    //!
    //! @param key
    //! A key to remove from the map. It must be compile-time `Comparable`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/map/erase_key.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto erase_key = [](auto&& map, auto&& key) {
        return tag-dispatched;
    };
#endif

    //! Returns the union of two maps.
    //! @relates hana::map
    //!
    //! Given two maps `xs` and `ys`, `hana::union_(xs, ys)` is a new map
    //! containing all the elements of `xs` and all the elements of `ys`,
    //! without duplicates. If both `xs` and `ys` contain an element with the
    //! same `key`, the one in `ys` is taken. Functionally,
    //! `hana::union_(xs, ys)` is equivalent to
    //! @code
    //! hana::fold_left(xs, ys, hana::insert)
    //! @endcode
    //!
    //! @param xs, ys
    //! The two maps to compute the union of.
    //!
    //!
    //! Example
    //! -------
    //! @include example/map/union.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto union_ = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
    };
#endif

    //! Returns the intersection of two maps.
    //! @relates hana::map
    //!
    //! Given two maps `xs` and `ys`, `intersection(xs, ys)` is a new map
    //! containing exactly those (key, value) pairs from xs, for which key
    //! is present in `ys`.
    //! In other words, the following holds for any object `pair(k, v)`:
    //! @code
    //!     pair(k, v) ^in^ intersection(xs, ys) if and only if (k, v) ^in^ xs && k ^in^ keys(ys)
    //! @endcode
    //!
    //!
    //! @note
    //! This function is not commutative, i.e. `intersection(xs, ys)` is not
    //! necessarily the same as `intersection(ys, xs)`. Indeed, the set of keys
    //! in `intersection(xs, ys)` is always the same as the set of keys in
    //! `intersection(ys, xs)`, but the value associated to each key may be
    //! different. `intersection(xs, ys)` contains values present in `xs`, and
    //! `intersection(ys, xs)` contains values present in `ys`.
    //!
    //!
    //! @param xs, ys
    //! Two maps to intersect.
    //!
    //!
    //! Example
    //! -------
    //! @include example/map/intersection.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto intersection = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
    };
#endif

    //! Returns the difference of two maps.
    //! @relates hana::map
    //!
    //! Given two maps `xs` and `ys`, `difference(xs, ys)` is a new map
    //! containing exactly those (key, value) pairs from xs, for which key
    //! is not present in `keys(ys)`.
    //! In other words, the following holds for any object `pair(k, v)`:
    //! @code
    //!     pair(k, v) ^in^ difference(xs, ys) if and only if (k, v) ^in^ xs && k ^not in^ keys(ys)
    //! @endcode
    //!
    //!
    //! @note
    //! This function is not commutative, i.e. `difference(xs, ys)` is not
    //! necessarily the same as `difference(ys, xs)`.
    //! Indeed, consider the case where `xs` is empty and `ys` isn't.
    //! In that case, `difference(xs, ys)` is empty, but `difference(ys, xs)`
    //! is equal to `ys`.
    //! For symmetric version of this operation, see `symmetric_difference`.
    //!
    //!
    //! @param xs, ys
    //! Two maps to compute the difference of.
    //!
    //!
    //! Example
    //! -------
    //! @include example/map/intersection.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto difference = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
    };
#endif

    //! Returns the symmetric set-theoretic difference of two maps.
    //! @relates hana::map
    //!
    //! Given two sets `xs` and `ys`, `symmetric_difference(xs, ys)` is a new
    //! map containing all the elements of `xs` whose keys are not contained in `keys(ys)`,
    //! and all the elements of `ys` whose keys are not contained in `keys(xs)`. The
    //! symmetric difference of two maps satisfies the following:
    //! @code
    //!     symmetric_difference(xs, ys) == union_(difference(xs, ys), difference(ys, xs))
    //! @endcode
    //!
    //!
    //! @param xs, ys
    //! Two maps to compute the symmetric difference of.
    //!
    //!
    //! Example
    //! -------
    //! @include example/map/symmetric_difference.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
constexpr auto symmetric_difference = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
    };
#endif


}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_MAP_HPP

/* map.hpp
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
*/