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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SET_HPP

/* set.hpp
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
*/