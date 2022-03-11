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


BOOST_HANA_NAMESPACE_BEGIN
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
    constexpr auto make_map = make<map_tag>;

    //! Equivalent to `to<map_tag>`; provided for convenience.
    //! @relates hana::map
    constexpr auto to_map = to<map_tag>;

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

    constexpr values_t values{};
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


BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MAP_HPP

/* map.hpp
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
*/