/*!
@file
Defines `boost::hana::set`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SET_HPP
#define BOOST_HANA_SET_HPP

#include <boost/hana/fwd/set.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/concept/comparable.hpp>
#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/hashable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/contains.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/detail/has_duplicates.hpp>
#include <boost/hana/detail/operators/adl.hpp>
#include <boost/hana/detail/operators/comparable.hpp>
#include <boost/hana/detail/operators/searchable.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/erase_key.hpp>
#include <boost/hana/find_if.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/fwd/any_of.hpp>
#include <boost/hana/fwd/core/to.hpp>
#include <boost/hana/fwd/difference.hpp>
#include <boost/hana/fwd/intersection.hpp>
#include <boost/hana/fwd/union.hpp>
#include <boost/hana/insert.hpp>
#include <boost/hana/is_subset.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/or.hpp>
#include <boost/hana/remove.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/unpack.hpp>
#include <boost/hana/value.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


namespace boost { namespace hana {
    //////////////////////////////////////////////////////////////////////////
    // set
    //////////////////////////////////////////////////////////////////////////
    //! @cond
    template <typename ...Xs>
    struct set final
        : detail::operators::adl<set<Xs...>>
        , detail::searchable_operators<set<Xs...>>
    {
        tuple<Xs...> storage;
        using hana_tag = set_tag;
        static constexpr std::size_t size = sizeof...(Xs);

        explicit constexpr set(tuple<Xs...> const& xs)
            : storage(xs)
        { }

        explicit constexpr set(tuple<Xs...>&& xs)
            : storage(static_cast<tuple<Xs...>&&>(xs))
        { }

        constexpr set() = default;
        constexpr set(set const& other) = default;
        constexpr set(set&& other) = default;
    };
    //! @endcond

    //////////////////////////////////////////////////////////////////////////
    // Operators
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <>
        struct comparable_operators<set_tag> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // make<set_tag>
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct make_impl<set_tag> {
        template <typename ...Xs>
        static constexpr auto apply(Xs&& ...xs) {
#if defined(BOOST_HANA_CONFIG_ENABLE_DEBUG_MODE)
            static_assert(detail::fast_and<hana::Comparable<Xs>::value...>::value,
            "hana::make_set(xs...) requires all the 'xs' to be Comparable");

            static_assert(detail::fast_and<hana::Hashable<Xs>::value...>::value,
            "hana::make_set(xs...) requires all the 'xs' to be Hashable");

            static_assert(detail::fast_and<
                Constant<decltype(hana::equal(xs, xs))>::value...
            >::value,
            "hana::make_set(xs...) requires all the 'xs' to be "
            "Comparable at compile-time");

            static_assert(!detail::has_duplicates<Xs&&...>::value,
            "hana::make_set(xs...) requires all the 'xs' to be unique");
#endif

            return set<typename detail::decay<Xs>::type...>{
                hana::make_tuple(static_cast<Xs&&>(xs)...)
            };
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Comparable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct equal_impl<set_tag, set_tag> {
        template <typename S1, typename S2>
        static constexpr auto equal_helper(S1 const& s1, S2 const& s2, hana::true_)
        { return hana::is_subset(s1, s2); }

        template <typename S1, typename S2>
        static constexpr auto equal_helper(S1 const&, S2 const&, hana::false_)
        { return hana::false_c; }

        template <typename S1, typename S2>
        static constexpr decltype(auto) apply(S1&& s1, S2&& s2) {
            return equal_impl::equal_helper(s1, s2, hana::bool_c<
                decltype(hana::length(s1.storage))::value ==
                decltype(hana::length(s2.storage))::value
            >);
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct unpack_impl<set_tag> {
        template <typename Set, typename F>
        static constexpr decltype(auto) apply(Set&& set, F&& f) {
            return hana::unpack(static_cast<Set&&>(set).storage,
                                static_cast<F&&>(f));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Searchable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct find_if_impl<set_tag> {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return hana::find_if(static_cast<Xs&&>(xs).storage, static_cast<Pred&&>(pred));
        }
    };

    template <>
    struct any_of_impl<set_tag> {
        template <typename Pred>
        struct any_of_helper {
            Pred const& pred;
            template <typename ...X>
            constexpr auto operator()(X const& ...x) const {
                return hana::or_(pred(x)...);
            }
            constexpr auto operator()() const {
                return hana::false_c;
            }
        };

        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs const& xs, Pred const& pred) {
            return hana::unpack(xs.storage, any_of_helper<Pred>{pred});
        }
    };

    template <>
    struct is_subset_impl<set_tag, set_tag> {
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
            return hana::unpack(xs, all_contained<Ys>{ys});
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Conversions
    //////////////////////////////////////////////////////////////////////////
    template <typename F>
    struct to_impl<set_tag, F, when<hana::Foldable<F>::value>> {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs) {
            return hana::fold_left(static_cast<Xs&&>(xs),
                                   hana::make_set(),
                                   hana::insert);
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // insert
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct insert_impl<set_tag> {
        template <typename Xs, typename X, typename Indices>
        static constexpr auto
        insert_helper(Xs&& xs, X&&, hana::true_, Indices) {
            return static_cast<Xs&&>(xs);
        }

        template <typename Xs, typename X, std::size_t ...n>
        static constexpr auto
        insert_helper(Xs&& xs, X&& x, hana::false_, std::index_sequence<n...>) {
            return hana::make_set(
                hana::at_c<n>(static_cast<Xs&&>(xs).storage)..., static_cast<X&&>(x)
            );
        }

        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            constexpr bool c = hana::value<decltype(hana::contains(xs, x))>();
            constexpr std::size_t size = std::remove_reference<Xs>::type::size;
            return insert_helper(static_cast<Xs&&>(xs), static_cast<X&&>(x),
                                 hana::bool_c<c>, std::make_index_sequence<size>{});
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // erase_key
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct erase_key_impl<set_tag> {
        template <typename Xs, typename X>
        static constexpr decltype(auto) apply(Xs&& xs, X&& x) {
            return hana::unpack(
                hana::remove(static_cast<Xs&&>(xs).storage,
                             static_cast<X&&>(x)),
                hana::make_set
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // intersection
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename Ys>
        struct set_insert_if_contains {
            Ys const& ys;

            template <typename Result, typename Key>
            static constexpr auto helper(Result&& result, Key&& key, hana::true_) {
                return hana::insert(static_cast<Result&&>(result), static_cast<Key&&>(key));
            }

            template <typename Result, typename Key>
            static constexpr auto helper(Result&& result, Key&&, hana::false_) {
                return static_cast<Result&&>(result);
            }

            template <typename Result, typename Key>
            constexpr auto operator()(Result&& result, Key&& key) const {
                constexpr bool keep = hana::value<decltype(hana::contains(ys, key))>();
                return set_insert_if_contains::helper(static_cast<Result&&>(result),
                                                      static_cast<Key&&>(key),
                                                      hana::bool_c<keep>);
            }
        };
    }

    template <>
    struct intersection_impl<set_tag> {
        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs&& xs, Ys const& ys) {
            return hana::fold_left(static_cast<Xs&&>(xs), hana::make_set(),
                                   detail::set_insert_if_contains<Ys>{ys});
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // union_
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct union_impl<set_tag> {
        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs&& xs, Ys&& ys) {
            return hana::fold_left(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys),
                                   hana::insert);
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // difference
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct difference_impl<set_tag> {
        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs&& xs, Ys&& ys) {
            return hana::fold_left(static_cast<Ys&&>(ys), static_cast<Xs&&>(xs),
                                   hana::erase_key);
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_SET_HPP

/* set.hpp
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
*/