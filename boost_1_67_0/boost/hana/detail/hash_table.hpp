/*!
@file
Defines `boost::hana::detail::hash_table`.

@copyright Louis Dionne 2016
@copyright Jason Rice 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_HASH_TABLE_HPP
#define BOOST_HANA_DETAIL_HASH_TABLE_HPP

#include <boost/hana/equal.hpp>
#include <boost/hana/ext/std/integer_sequence.hpp>
#include <boost/hana/ext/std/integral_constant.hpp>
#include <boost/hana/find_if.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/hash.hpp>
#include <boost/hana/optional.hpp>
#include <boost/hana/range.hpp>
#include <boost/hana/type.hpp>
#include <boost/hana/value.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Hash, std::size_t ...i>
    struct bucket { };

    template <typename ...Buckets>
    struct hash_table
        : Buckets...
    { };

    // find_indices:
    //  Returns an `index_sequence` containing possible indices for the given
    //  `Key` in the `Map`.
    template <typename Hash, std::size_t ...i>
    std::index_sequence<i...> find_indices_impl(bucket<Hash, i...> const&);

    template <typename Hash>
    std::index_sequence<> find_indices_impl(...);

    template <typename Map, typename Key>
    struct find_indices {
        using Hash = typename decltype(hana::hash(std::declval<Key>()))::type;
        using type = decltype(detail::find_indices_impl<Hash>(std::declval<Map>()));
    };
    // end find_indices

    // find_index:
    //  Returns the actual index of a `Key` in the `Map`. The type of the key
    //  associated to any given index must be retrievable with the `KeyAtIndex`
    //  alias.
    template <template <std::size_t> class KeyAtIndex, typename Key>
    struct find_pred {
        template <typename Index>
        auto operator()(Index const&) const -> decltype(
            hana::equal(std::declval<KeyAtIndex<Index::value>>(),
                        std::declval<Key>())
        );
    };

    template <typename Indices, typename Key, template <std::size_t> class KeyAtIndex>
    struct find_index_impl {
        using type = decltype(hana::find_if(Indices{}, find_pred<KeyAtIndex, Key>{}));
    };

    // This is a peephole optimization for buckets that have a single entry.
    // It provides a nice speedup in the at_key.number_of_lookups benchmark.
    // It is perhaps possible to make this part of `find_if` itself, but we
    // should make sure that we retain that speedup.
    template <std::size_t i, typename Key, template <std::size_t> class KeyAtIndex>
    struct find_index_impl<std::index_sequence<i>, Key, KeyAtIndex> {
        using Equal = decltype(
            hana::equal(std::declval<KeyAtIndex<i>>(),
                        std::declval<Key>())
        );
        using type = typename std::conditional<Equal::value,
            hana::optional<std::integral_constant<std::size_t, i>>,
            hana::optional<>
        >::type;
    };

    template <typename Map, typename Key, template <std::size_t> class KeyAtIndex>
    struct find_index {
        using Indices = typename find_indices<Map, Key>::type;
        using type = typename find_index_impl<Indices, Key, KeyAtIndex>::type;
    };
    // end find_index

    // bucket_insert:
    //  Inserts the given `Index` into the bucket of the `Map` in which `Key` falls.
    template <typename Bucket, typename Hash, std::size_t Index>
    struct update_bucket {
        using type = Bucket;
    };

    template <std::size_t ...i, typename Hash, std::size_t Index>
    struct update_bucket<bucket<Hash, i...>, Hash, Index> {
        using type = bucket<Hash, i..., Index>;
    };

    template <typename Map, typename Key, std::size_t Index, bool =
        (find_indices<Map, Key>::type::size() > 0)
    >
    struct bucket_insert;

    template <typename ...Buckets, typename Key, std::size_t Index>
    struct bucket_insert<hash_table<Buckets...>, Key, Index, true> {
        // There is a bucket for that Hash; append the new index to it.
        using Hash = typename decltype(hana::hash(std::declval<Key>()))::type;
        using type = hash_table<typename update_bucket<Buckets, Hash, Index>::type...>;
    };

    template <typename ...Buckets, typename Key, std::size_t Index>
    struct bucket_insert<hash_table<Buckets...>, Key, Index, false> {
        // There is no bucket for that Hash; insert a new bucket.
        using Hash = typename decltype(hana::hash(std::declval<Key>()))::type;
        using type = hash_table<Buckets..., bucket<Hash, Index>>;
    };
    // end bucket_insert

    // make_hash_table:
    //  Creates a `hash_table` type able of holding the given number of
    //  elements. The type of the key associated to any given index must
    //  be retrievable using the `KeyAtIndex` alias. All the keys must
    //  be distinct and have different hashes too.
    template <template <std::size_t> class KeyAtIndex, std::size_t N,
              typename Indices = std::make_index_sequence<N>>
    struct make_hash_table;

    template <template <std::size_t> class KeyAtIndex, std::size_t N, std::size_t ...i>
    struct make_hash_table<KeyAtIndex, N, std::index_sequence<i...>> {
        using type = hash_table<
            bucket<typename decltype(hana::hash(std::declval<KeyAtIndex<i>>()))::type, i>...
        >;
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_HASH_TABLE_HPP

/* hash_table.hpp
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
*/