/*!
@file
Defines `boost::hana::map`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MAP_HPP
#define BOOST_HANA_MAP_HPP

#include <boost/hana/fwd/map.hpp>

#include <boost/hana/all_of.hpp>
#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/concept/comparable.hpp>
#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/product.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/contains.hpp>
#include <boost/hana/core/is_a.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/detail/has_duplicates.hpp>
#include <boost/hana/detail/hash_table.hpp>
#include <boost/hana/detail/intrinsics.hpp>
#include <boost/hana/detail/operators/adl.hpp>
#include <boost/hana/detail/operators/comparable.hpp>
#include <boost/hana/detail/operators/searchable.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/find.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/functional/demux.hpp>
#include <boost/hana/functional/on.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/fwd/any_of.hpp>
#include <boost/hana/fwd/at_key.hpp>
#include <boost/hana/fwd/difference.hpp>
#include <boost/hana/fwd/erase_key.hpp>
#include <boost/hana/fwd/intersection.hpp>
#include <boost/hana/fwd/is_subset.hpp>
#include <boost/hana/fwd/keys.hpp>
#include <boost/hana/fwd/union.hpp>
#include <boost/hana/insert.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/keys.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/optional.hpp>
#include <boost/hana/remove_if.hpp>
#include <boost/hana/second.hpp>
#include <boost/hana/unpack.hpp>
#include <boost/hana/value.hpp>


#include <cstddef>
#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //////////////////////////////////////////////////////////////////////////
    // operators
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <>
        struct comparable_operators<map_tag> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // map
    //////////////////////////////////////////////////////////////////////////
    //! @cond
    namespace detail {
        template <typename ...>
        struct storage_is_default_constructible;
        template <typename ...T>
        struct storage_is_default_constructible<hana::basic_tuple<T...>> {
            static constexpr bool value = detail::fast_and<
                BOOST_HANA_TT_IS_CONSTRUCTIBLE(T)...
            >::value;
        };

        template <typename ...>
        struct storage_is_copy_constructible;
        template <typename ...T>
        struct storage_is_copy_constructible<hana::basic_tuple<T...>> {
            static constexpr bool value = detail::fast_and<
                BOOST_HANA_TT_IS_CONSTRUCTIBLE(T, T const&)...
            >::value;
        };

        template <typename ...>
        struct storage_is_move_constructible;
        template <typename ...T>
        struct storage_is_move_constructible<hana::basic_tuple<T...>> {
            static constexpr bool value = detail::fast_and<
                BOOST_HANA_TT_IS_CONSTRUCTIBLE(T, T&&)...
            >::value;
        };

        template <typename ...>
        struct storage_is_copy_assignable;
        template <typename ...T>
        struct storage_is_copy_assignable<hana::basic_tuple<T...>> {
            static constexpr bool value = detail::fast_and<
                BOOST_HANA_TT_IS_ASSIGNABLE(T, T const&)...
            >::value;
        };

        template <typename ...>
        struct storage_is_move_assignable;
        template <typename ...T>
        struct storage_is_move_assignable<hana::basic_tuple<T...>> {
            static constexpr bool value = detail::fast_and<
                BOOST_HANA_TT_IS_ASSIGNABLE(T, T&&)...
            >::value;
        };

        template <typename HashTable, typename Storage>
        struct map_impl final
            : detail::searchable_operators<map_impl<HashTable, Storage>>
            , detail::operators::adl<map_impl<HashTable, Storage>>
        {
            using hash_table_type = HashTable;
            using storage_type = Storage;

            Storage storage;

            using hana_tag = map_tag;

            template <typename ...P, typename = typename std::enable_if<
                std::is_same<
                    Storage,
                    hana::basic_tuple<typename detail::decay<P>::type...>
                >::value
            >::type>
            explicit constexpr map_impl(P&& ...pairs)
                : storage{static_cast<P&&>(pairs)...}
            { }

            explicit constexpr map_impl(Storage&& xs)
                : storage(static_cast<Storage&&>(xs))
            { }

            template <typename ...Dummy, typename = typename std::enable_if<
                detail::storage_is_default_constructible<Storage, Dummy...>::value
            >::type>
            constexpr map_impl()
                : storage()
            { }

            template <typename ...Dummy, typename = typename std::enable_if<
                detail::storage_is_copy_constructible<Storage, Dummy...>::value
            >::type>
            constexpr map_impl(map_impl const& other)
                : storage(other.storage)
            { }

            template <typename ...Dummy, typename = typename std::enable_if<
                detail::storage_is_move_constructible<Storage, Dummy...>::value
            >::type>
            constexpr map_impl(map_impl&& other)
                : storage(static_cast<Storage&&>(other.storage))
            { }

            template <typename ...Dummy, typename = typename std::enable_if<
                detail::storage_is_move_assignable<Storage, Dummy...>::value
            >::type>
            constexpr map_impl& operator=(map_impl&& other) {
                storage = static_cast<Storage&&>(other.storage);
                return *this;
            }

            template <typename ...Dummy, typename = typename std::enable_if<
                detail::storage_is_copy_assignable<Storage, Dummy...>::value
            >::type>
            constexpr map_impl& operator=(map_impl const& other) {
                storage = other.storage;
                return *this;
            }

            // Prevent the compiler from defining the default copy and move
            // constructors, which interfere with the SFINAE above.
            ~map_impl() = default;
        };
        //! @endcond

        template <typename Storage>
        struct KeyAtIndex {
            template <std::size_t i>
            using apply = decltype(hana::first(hana::at_c<i>(std::declval<Storage>())));
        };

        template <typename ...Pairs>
        struct make_map_type {
            using Storage = hana::basic_tuple<Pairs...>;
            using HashTable = typename detail::make_hash_table<
                detail::KeyAtIndex<Storage>::template apply, sizeof...(Pairs)
            >::type;
            using type = detail::map_impl<HashTable, Storage>;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // make<map_tag>
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct make_impl<map_tag> {
        template <typename ...Pairs>
        static constexpr auto apply(Pairs&& ...pairs) {
#if defined(BOOST_HANA_CONFIG_ENABLE_DEBUG_MODE)
            static_assert(detail::fast_and<hana::Product<Pairs>::value...>::value,
            "hana::make_map(pairs...) requires all the 'pairs' to be Products");

            static_assert(detail::fast_and<
                hana::Comparable<decltype(hana::first(pairs))>::value...
            >::value,
            "hana::make_map(pairs...) requires all the keys to be Comparable");

            static_assert(detail::fast_and<
                hana::Constant<
                    decltype(hana::equal(hana::first(pairs), hana::first(pairs)))
                >::value...
            >::value,
            "hana::make_map(pairs...) requires all the keys to be "
            "Comparable at compile-time");

            //! @todo
            //! This can be implemented more efficiently by doing the check
            //! inside each bucket instead.
            static_assert(!detail::has_duplicates<decltype(hana::first(pairs))...>::value,
            "hana::make_map({keys, values}...) requires all the keys to be unique");

            static_assert(!detail::has_duplicates<decltype(hana::hash(hana::first(pairs)))...>::value,
            "hana::make_map({keys, values}...) requires all the keys to have different hashes");
#endif

            using Map = typename detail::make_map_type<typename detail::decay<Pairs>::type...>::type;
            return Map{hana::make_basic_tuple(static_cast<Pairs&&>(pairs)...)};
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // keys
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct keys_impl<map_tag> {
        template <typename Map>
        static constexpr decltype(auto) apply(Map&& map) {
            return hana::transform(static_cast<Map&&>(map).storage, hana::first);
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // values
    //////////////////////////////////////////////////////////////////////////
    //! @cond
    template <typename Map>
    constexpr decltype(auto) values_t::operator()(Map&& map) const {
        return hana::transform(static_cast<Map&&>(map).storage, hana::second);
    }
    //! @endcond

    //////////////////////////////////////////////////////////////////////////
    // insert
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct insert_impl<map_tag> {
        template <typename Map, typename Pair>
        static constexpr auto helper(Map&& map, Pair&& pair, ...) {
            using RawMap = typename std::remove_reference<Map>::type;
            using HashTable = typename RawMap::hash_table_type;
            using NewHashTable = typename detail::bucket_insert<
                HashTable,
                decltype(hana::first(pair)),
                decltype(hana::length(map.storage))::value
            >::type;

            using NewStorage = decltype(
                hana::append(static_cast<Map&&>(map).storage, static_cast<Pair&&>(pair))
            );
            return detail::map_impl<NewHashTable, NewStorage>(
                hana::append(static_cast<Map&&>(map).storage, static_cast<Pair&&>(pair))
            );
        }

        template <typename Map, typename Pair, std::size_t i>
        static constexpr auto
        helper(Map&& map, Pair&&,
               hana::optional<std::integral_constant<std::size_t, i>>)
        {
            return static_cast<Map&&>(map);
        }

        //! @todo
        //! Here, we insert only if the key is not already in the map.
        //! This should be handled by `bucket_insert`, and that would also
        //! be more efficient.
        template <typename Map, typename Pair>
        static constexpr auto apply(Map&& map, Pair&& pair) {
            using RawMap = typename std::remove_reference<Map>::type;
            using Storage = typename RawMap::storage_type;
            using HashTable = typename RawMap::hash_table_type;
            using Key = decltype(hana::first(pair));
            using MaybeIndex = typename detail::find_index<
              HashTable, Key, detail::KeyAtIndex<Storage>::template apply
            >::type;
            return helper(static_cast<Map&&>(map), static_cast<Pair&&>(pair), MaybeIndex{});
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // erase_key
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct erase_key_impl<map_tag> {
        //! @todo
        //! We could implement some kind of `bucket_erase` metafunction
        //! that would be much more efficient than this.
        template <typename Map, typename Key>
        static constexpr auto
        erase_key_helper(Map&& map, Key const&, hana::false_) {
            return static_cast<Map&&>(map);
        }

        template <typename Map, typename Key>
        static constexpr auto
        erase_key_helper(Map&& map, Key const& key, hana::true_) {
            return hana::unpack(
                hana::remove_if(static_cast<Map&&>(map).storage,
                                hana::on(hana::equal.to(key), hana::first)),
                hana::make_map
            );
        }

        template <typename Map, typename Key>
        static constexpr auto apply_impl(Map&& map, Key const& key, hana::false_) {
            return erase_key_helper(static_cast<Map&&>(map), key,
                                    hana::contains(map, key));
        }

        template <typename Map, typename Key>
        static constexpr auto apply_impl(Map&& map, Key const&, hana::true_) {
            return static_cast<Map&&>(map);
        }

        template <typename Map, typename Key>
        static constexpr auto apply(Map&& map, Key const& key) {
            constexpr bool is_empty = decltype(hana::length(map))::value == 0;
            return apply_impl(static_cast<Map&&>(map), key, hana::bool_<is_empty>{});
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Comparable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct equal_impl<map_tag, map_tag> {
        template <typename M1, typename M2>
        static constexpr auto equal_helper(M1 const&, M2 const&, hana::false_) {
            return hana::false_c;
        }

        template <typename M1, typename M2>
        static constexpr auto equal_helper(M1 const& m1, M2 const& m2, hana::true_) {
            return hana::all_of(hana::keys(m1), hana::demux(equal)(
                hana::partial(hana::find, m1),
                hana::partial(hana::find, m2)
            ));
        }

        template <typename M1, typename M2>
        static constexpr auto apply(M1 const& m1, M2 const& m2) {
            return equal_impl::equal_helper(m1, m2, hana::bool_c<
                decltype(hana::length(m1.storage))::value ==
                decltype(hana::length(m2.storage))::value
            >);
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Searchable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct find_impl<map_tag> {
        template <typename Map>
        static constexpr auto find_helper(Map&&, ...) {
            return hana::nothing;
        }

        template <typename Map, std::size_t i>
        static constexpr auto
        find_helper(Map&& map, hana::optional<std::integral_constant<std::size_t, i>>) {
            return hana::just(hana::second(hana::at_c<i>(static_cast<Map&&>(map).storage)));
        }

        template <typename Map, typename Key>
        static constexpr auto apply(Map&& map, Key const&) {
            using RawMap = typename std::remove_reference<Map>::type;
            using Storage = typename RawMap::storage_type;
            using HashTable = typename RawMap::hash_table_type;
            using MaybeIndex = typename detail::find_index<
              HashTable, Key, detail::KeyAtIndex<Storage>::template apply
            >::type;
            return find_helper(static_cast<Map&&>(map), MaybeIndex{});
        }
    };

    template <>
    struct find_if_impl<map_tag> {
        template <typename M, typename Pred>
        static constexpr auto apply(M&& map, Pred&& pred) {
            return hana::transform(
                hana::find_if(static_cast<M&&>(map).storage,
                    hana::compose(static_cast<Pred&&>(pred), hana::first)),
                hana::second
            );
        }
    };

    template <>
    struct contains_impl<map_tag> {
        template <typename Map, typename Key>
        static constexpr auto apply(Map const&, Key const&) {
            using RawMap = typename std::remove_reference<Map>::type;
            using HashTable = typename RawMap::hash_table_type;
            using Storage = typename RawMap::storage_type;
            using MaybeIndex = typename detail::find_index<
                HashTable, Key, detail::KeyAtIndex<Storage>::template apply
            >::type;
            return hana::bool_<!decltype(hana::is_nothing(MaybeIndex{}))::value>{};
        }
    };

    template <>
    struct any_of_impl<map_tag> {
        template <typename M, typename Pred>
        static constexpr auto apply(M const& map, Pred const& pred)
        { return hana::any_of(hana::keys(map), pred); }
    };

    template <>
    struct is_subset_impl<map_tag, map_tag> {
        template <typename Ys>
        struct all_contained {
            Ys const& ys;
            template <typename ...X>
            constexpr auto operator()(X const& ...x) const {
                return hana::bool_c<detail::fast_and<
                    hana::value<decltype(hana::contains(ys, x))>()...
                >::value>;
            }
        };

        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs const& xs, Ys const& ys) {
            auto ys_keys = hana::keys(ys);
            return hana::unpack(hana::keys(xs), all_contained<decltype(ys_keys)>{ys_keys});
        }
    };

    template <>
    struct at_key_impl<map_tag> {
        template <typename Map, typename Key>
        static constexpr decltype(auto) apply(Map&& map, Key const&) {
            using RawMap = typename std::remove_reference<Map>::type;
            using HashTable = typename RawMap::hash_table_type;
            using Storage = typename RawMap::storage_type;
            using MaybeIndex = typename detail::find_index<
                HashTable, Key, detail::KeyAtIndex<Storage>::template apply
            >::type;
            static_assert(!decltype(hana::is_nothing(MaybeIndex{}))::value,
                "hana::at_key(map, key) requires the 'key' to be present in the 'map'");
            constexpr std::size_t index = decltype(*MaybeIndex{}){}();
            return hana::second(hana::at_c<index>(static_cast<Map&&>(map).storage));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // union_
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct union_impl<map_tag> {
        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs&& xs, Ys&& ys) {
            return hana::fold_left(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys),
                                   hana::insert);
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // intersection_
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename Ys>
        struct map_insert_if_contains {
            Ys const& ys;

            // Second template param will be pair
            // Get its key and check if it exists, if it does, insert key, value pair.
            template <typename Result, typename Pair>
            static constexpr auto helper(Result&& result, Pair&& pair, hana::true_) {
                return hana::insert(static_cast<Result&&>(result), static_cast<Pair&&>(pair));
            }

            template <typename Result, typename Pair>
            static constexpr auto helper(Result&& result, Pair&&, hana::false_) {
                return static_cast<Result&&>(result);
            }

            template <typename Result, typename Pair>
            constexpr auto operator()(Result&& result, Pair&& pair) const {
                constexpr bool keep = hana::value<decltype(hana::contains(ys, hana::first(pair)))>();
                return map_insert_if_contains::helper(static_cast<Result&&>(result),
                                                      static_cast<Pair&&>(pair),
                                                      hana::bool_c<keep>);
            }
        };
    }

    template <>
    struct intersection_impl<map_tag> {
        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs&& xs, Ys const& ys) {
            return hana::fold_left(static_cast<Xs&&>(xs), hana::make_map(),
                                   detail::map_insert_if_contains<Ys>{ys});
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // difference
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct difference_impl<map_tag> {
        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs&& xs, Ys&& ys) {
            return hana::fold_left(
                    hana::keys(static_cast<Ys&&>(ys)),
                    static_cast<Xs&&>(xs),
                    hana::erase_key);
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct unpack_impl<map_tag> {
        template <typename M, typename F>
        static constexpr decltype(auto) apply(M&& map, F&& f) {
            return hana::unpack(static_cast<M&&>(map).storage,
                                static_cast<F&&>(f));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Construction from a Foldable
    //////////////////////////////////////////////////////////////////////////
    template <typename F>
    struct to_impl<map_tag, F, when<hana::Foldable<F>::value>> {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs) {
            return hana::fold_left(
                static_cast<Xs&&>(xs), hana::make_map(), hana::insert
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MAP_HPP

/* map.hpp
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
*/