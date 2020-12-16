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
1hMLXsVUPXjX2Ha6FmV9IbITHM+/FfzApmvLKyHYOnwWWweI4DAVgbEH76drvuraTgktWAzUnuIlX43S1o5p03rXu6ZoK87vKIIuYwz9vXSh23XChJxLGsZ/qSp6iL6LtP5bN53rlTagiz4o7RQ0x2pLabliruemrYVnNo1H2AiBMQJVA7zO/eJh9DDulOeO52vuMZVzvur8YLSFs8dk7z7EPGWUXtRMGm9M3VRFvYk5rXkBDOv4FPNykjx5xbsZBmsq3bYMLrQfPpvqYZ8p+suZ6Z1XreyLeoFxSWdh92HzmBgq57ZccVsHLKeTsMhM95c/ZFpc443UvO+oQWN7+ZZ6Qvt5nQ8UfvJNZapK9OyExCStoq6TaFHPlbLnzmlaZ7kyoroDXZ/301M5t5F1LWy4QjwhmxnWefeizo4BaS+HrmIuEJ+5he7EpYPN7URPonJupVwtehcwcx80wW1/GqUTDdNtp5uqwdyu5BqXLlLpMDnv42eKPg61h4H1A9sDRNvcx/vXeQ2jtEFdboQwvRlYfAnCjrA8q4kXqo0niYmto2i3YMZ0TRX03+rw4dS3hjqD0sxsjMRUvyr6vtXaEdTA7Nf1kh/nMnDKiw5+4LYEPoDIi+WzzfHjmvuM/fzrlDfZyQjvBb8Ryy2AKm4+YvfkKKwpN8w+dN/GvGGNtHKt6vU9pdjQg4zGVGzfn+Z0WAiPdfaNe9uPz5KD+agx99XvvoF+dPGqZGvnAQG5VmNd8/L7PyhTQF25ze/5cS5PGZfO3RfeKDjTncJFIsmt85rY5o27gx2+zqh/cQUnPo2v+2aWdddbRYvr2DPM8fOhH5NymB2bYdKQ8s/E8rCTwks93IFVMLyEefnnl5SHNEG5/ILfxvI1eedNvnH3sQG5D19GfiyPcIggCLEQL7MoI+ZCGyf2vK/fQVmjvWF/J7YVsRJ/Pi9Pq/koJ9rwyJj9BulGk0Ui2EQfRSyPye0zP5b/dbGe8JVjn/9BytM6tznuwPN5e8GfLNLEtF8A+7y/Pff/vFhJN04YNFDN58plJnT3g4mSK800V/rJpN9Z3Sa58K6BNGF496OyFG86SO6t6yAN9h8uhOCfo1cq0t3wLLrYi3mdN0U6Wg71k1xV59F2pXJAzUEZ5y+OZ06HhbnW7og04yjH2ZEGieb8EhO6ON4wf/JaYebl69o2vVyT8M8oDLbvTUi4Nc+D5+e0dbWueSSFWUvzbN11CU38ikj/7zWnCcXOrssoJpc/5Sc5l1f+ju4Ct4bzPj0rlkPTynJ8Vy/4yVlzdjMsSvu5rS/7SfENUpoZrluEBhxJ4C3Mjg4jyZzmTZkG24Lr7AxxWCbvIcO4IEbK61agPCWJA5T7OCHIfnV8jVAeV8y8bh5hTsWv0j0HvHShDP2DP1jipfWdDrZa9V/6B4cw81tvkzz0jMqrG2Y739tOJYw0vG4Jjj5g+o0XTtkfaIZ59wsZgtnWOxWw6ffPPM/cCbHIzytjV3ureAjWXqLX79qsYxf1eaa7oQmWdjZAhbGVQQOJKg4qIFQtmebPel4xpgOTte+d1IgThx6dCK6JSjHEBkFL08UZ6tYfnNjXGtkEePOcrwqzOJSHxNssnPUm70YNQvihrdnJUn0Z3XnRvlj0SzFT1fXgBp/bcXCU2rFEHrWNXOdD5V1ap9veCTvQdkQ9eHmuaOwPK+Q0TDvby6rhVA5NOz49s9yd8nPNRHDu9EYAVvv+iJQJ7ySPKqbLTne0xG7xuEJOF/Rla5z1zO5GZ8Dp8R1NCfuzgKdWnC/eV8jiTIq6G/hQT8c46tqTEQJBaBP4TjE2ktUtF0ZDJylfObInmfcPBa9gAb/Pt1WPvIuDeoI=
*/