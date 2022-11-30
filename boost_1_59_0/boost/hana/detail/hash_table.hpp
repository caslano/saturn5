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


namespace boost { namespace hana { namespace detail {
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
} }} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_HASH_TABLE_HPP

/* hash_table.hpp
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
*/