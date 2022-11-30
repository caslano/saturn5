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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_MAP_HPP

/* map.hpp
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
*/