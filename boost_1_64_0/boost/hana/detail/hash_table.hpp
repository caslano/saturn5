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
mmBUzDZjWBPDdgejYh0Eo+w8hpE7D6yMag9g5VSdZ3R+zLBfmfxKdqDlNmNYI1gpVXd3YOouI3cCI7cETP//MO5uYdeB6XPGQQu7nWEPMOwJhr3IsLfBSgj2I1iR5sMeFpa/41h7iFhYGVg+wapMLGphtWB5hFyDSW5/a3tg8ms36YxZWI9Jzsr2YfIbMum0sohJbtTCDgQrIOSOMbGwhZ1m0mllixl2OROXpSY2YmF3MnIPMmX0hIktsLDnTTqt7E1G54eMzs+ZmP3MxCW7kWaFYKWELdWMXB0j126Ss7LeRtr3fUxs2MIGGFsiDDvQxKzxPMrErHXiZMbOs0xyIQtbYmLWNnYVWAGh81YmZssY9hhj57MMe5Vh7zJsBWPLtwz7ndGZ46LjUgRG6SwDKyX6l5lgFQTbHayMYDGGLQIrJNiFJjut7EqwIoLdCeYg2GNgxcS5403GP6mJ7ncLwCgfSsHyCFZhkotYWC2jcweGtYNRMesFqyHYUWD6OES2sPPAHFT7M7GItRyYmC0Hc2rjgj0t7EMT28tar5tRRhrrs7BqMF1ubwubDValsX0sLGTS6bawRSa5fS3sVpOcx8JeNrF+C/vZZKfXWl9axuR8JpYlZcS/s+OsdlkGUvsH775dZVK8DJZmKKxrWXxs9dl9AZ0hsfRytsqU/am+l6eqTJaW4Gbql5LKsqWIdHlB/td6fotyJakrX2VTkN/aXzz/gq7z7TVwjshUGVRIm9540AY66ypGnppOqJC2vW9Ro2HntDE5pV3c8PUnfpWFFxy+liSdo/mwijTi23m3Q6pUNr3GufaYf/lSSN5oSehM3c6n0WE5NbYq7Kz2XL6Gnt+X62Dcp+Wn1MXIbe//pLPacshpbDXsP/j+UwcZPqCAlmhMaWsnLLn+Y0NnBbiW3+rYX+9GV4POGislaV/Nd4fUF27a75TfdLYE7GWNKQZuFWn7XGeHbwg7NZ1F2N9zesYnOltWNVZGSsFdl3fFVTpbupEkLdRYsRLr3x5pM/yrxvg7V2UIu7TouB+8BquFztVVprT7+38pb9eZsxF6NZ1r4ft153mDOnsaTI91Cfbv3aqj14iLC/5lqQzFJXV+/+j2hlyrJOVpcqXY733b96TO3p4FOzWG4pKe8915uMFmIzYaK8P+gsU1t+hs351xHtDsXBffH1yzd77OHLuM1bNy7LctWHe2Ees5Y+WwHr5vu+Kh0wydHWPMie9rb3Qu0Flj55h/ShutuS3yoxGzuWM+KA3hp/b3PjDYPNij2VKJ/Teav/tZZ7W7IU+tjFAFpENuertMZ4v2gQ+FKlMawhf13vt0Jg2jPmlsI6X9Hf/4ZzpbctBYzDZWkv5YtqlhyyFjdWkTpe7mbTLViNmhqIOaLYrAZR0tV+is62jYuYfKNsP+3Lp9XtLZ0jfH6u7m2P/9nnsP1NmXb0nSkMZqsL/21OHvjVi/gz47R2VbYN99QvPWhu8fQWe2ymqV/JZLMZ09/emYD9PxffJtp+yks2VKFDSd9fg5clrOKgZDz/aIJjcD3xvfUFavsn2kRd/A/zhrXLYd9rec8+z7OlsCpve7O2D/wzveuV5nl5rYjth/z3nXmzq70qTThf0nVty0QGe3m+RmYd/cly8zsQF8m9nTYHn4PhxMspwfXgZzxlmjcn4wMdRNMIfGsixyed8iP03nFIucA+zwOFP7QTNbBNag6VzTwh4B21dja1lY9XeStLXGSixsCKxEY+tb2OFgjmyFof1ZbfkJ8dLkNrSwp8F211iV1Ra0xCs1tpFVDuxmB5hS5y3sqFUzjHKotdoCpvtQZ2Yo56VgkSmqzu2xb2bONTIklya3o4X5wPQyclk=
*/