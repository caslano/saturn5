/*!
@file
Defines `boost::hana::string`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_STRING_HPP
#define BOOST_HANA_STRING_HPP

#include <boost/hana/fwd/string.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/algorithm.hpp>
#include <boost/hana/detail/operators/adl.hpp>
#include <boost/hana/detail/operators/comparable.hpp>
#include <boost/hana/detail/operators/iterable.hpp>
#include <boost/hana/detail/operators/orderable.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/contains.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/core/to.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/find.hpp>
#include <boost/hana/fwd/front.hpp>
#include <boost/hana/fwd/hash.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/length.hpp>
#include <boost/hana/fwd/less.hpp>
#include <boost/hana/fwd/plus.hpp>
#include <boost/hana/fwd/unpack.hpp>
#include <boost/hana/fwd/zero.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/optional.hpp>
#include <boost/hana/type.hpp>

#include <utility>
#include <cstddef>
#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //////////////////////////////////////////////////////////////////////////
    // string<>
    //////////////////////////////////////////////////////////////////////////
    //! @cond
    namespace detail {
        template <char ...s>
        constexpr char const string_storage[sizeof...(s) + 1] = {s..., '\0'};
    }

    template <char ...s>
    struct string
        : detail::operators::adl<string<s...>>
        , detail::iterable_operators<string<s...>>
    {
        static constexpr char const* c_str() {
            return &detail::string_storage<s...>[0];
        }
    };
    //! @endcond

    template <char ...s>
    struct tag_of<string<s...>> {
        using type = string_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // make<string_tag>
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct make_impl<string_tag> {
        template <typename ...Chars>
        static constexpr auto apply(Chars const& ...) {
            return hana::string<hana::value<Chars>()...>{};
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // BOOST_HANA_STRING
    //////////////////////////////////////////////////////////////////////////
    namespace string_detail {
        template <typename S, std::size_t ...N>
        constexpr string<S::get()[N]...>
        prepare_impl(S, std::index_sequence<N...>)
        { return {}; }

        template <typename S>
        constexpr decltype(auto) prepare(S s) {
            return prepare_impl(s,
                std::make_index_sequence<sizeof(S::get()) - 1>{});
        }
    }

#define BOOST_HANA_STRING(s)                                                \
    (::boost::hana::string_detail::prepare([]{                              \
        struct tmp {                                                        \
            static constexpr decltype(auto) get() { return s; }             \
        };                                                                  \
        return tmp{};                                                       \
    }()))                                                                   \
/**/

#ifdef BOOST_HANA_CONFIG_ENABLE_STRING_UDL
    //////////////////////////////////////////////////////////////////////////
    // _s user-defined literal
    //////////////////////////////////////////////////////////////////////////
    namespace literals {
        template <typename CharT, CharT ...s>
        constexpr auto operator"" _s() {
            static_assert(std::is_same<CharT, char>::value,
            "hana::string: Only narrow string literals are supported with "
            "the _s string literal right now. See https://goo.gl/fBbKD7 "
            "if you need support for fancier types of compile-time strings.");
            return hana::string_c<s...>;
        }
    }
#endif

    //////////////////////////////////////////////////////////////////////////
    // Operators
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <>
        struct comparable_operators<string_tag> {
            static constexpr bool value = true;
        };
        template <>
        struct orderable_operators<string_tag> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // to<char const*>
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct to_impl<char const*, string_tag> {
        template <char ...c>
        static constexpr char const* apply(string<c...> const&)
        { return string<c...>::c_str(); }
    };

    //////////////////////////////////////////////////////////////////////////
    // to<string_tag>
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        constexpr std::size_t cx_strlen(char const* s) {
          std::size_t n = 0u;
          while (*s != '\0')
            ++s, ++n;
          return n;
        }

        template <typename S, std::size_t ...I>
        constexpr hana::string<hana::value<S>()[I]...> expand(std::index_sequence<I...>)
        { return {}; }
    }

    template <typename IC>
    struct to_impl<hana::string_tag, IC, hana::when<
        hana::Constant<IC>::value &&
        std::is_convertible<typename IC::value_type, char const*>::value
    >> {
        template <typename S>
        static constexpr auto apply(S const&) {
            constexpr char const* s = hana::value<S>();
            constexpr std::size_t len = detail::cx_strlen(s);
            return detail::expand<S>(std::make_index_sequence<len>{});
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Comparable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct equal_impl<string_tag, string_tag> {
        template <typename S>
        static constexpr auto apply(S const&, S const&)
        { return hana::true_c; }

        template <typename S1, typename S2>
        static constexpr auto apply(S1 const&, S2 const&)
        { return hana::false_c; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Orderable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct less_impl<string_tag, string_tag> {
        template <char ...s1, char ...s2>
        static constexpr auto
        apply(string<s1...> const&, string<s2...> const&) {
            // We put a '\0' at the end only to avoid empty arrays.
            constexpr char const c_str1[] = {s1..., '\0'};
            constexpr char const c_str2[] = {s2..., '\0'};
            return hana::bool_c<detail::lexicographical_compare(
                c_str1, c_str1 + sizeof...(s1),
                c_str2, c_str2 + sizeof...(s2)
            )>;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Monoid
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct plus_impl<string_tag, string_tag> {
        template <char ...s1, char ...s2>
        static constexpr auto
        apply(string<s1...> const&, string<s2...> const&) {
            return string<s1..., s2...>{};
        }
    };

    template <>
    struct zero_impl<string_tag> {
        static constexpr auto apply() {
            return string<>{};
        }
    };

    template <char ...s1, char ...s2>
    constexpr auto operator+(string<s1...> const&, string<s2...> const&) {
        return hana::string<s1..., s2...>{};
    }

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct unpack_impl<string_tag> {
        template <char ...s, typename F>
        static constexpr decltype(auto) apply(string<s...> const&, F&& f)
        { return static_cast<F&&>(f)(char_<s>{}...); }
    };

    template <>
    struct length_impl<string_tag> {
        template <char ...s>
        static constexpr auto apply(string<s...> const&)
        { return hana::size_c<sizeof...(s)>; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Iterable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct front_impl<string_tag> {
        template <char x, char ...xs>
        static constexpr auto apply(string<x, xs...> const&)
        { return hana::char_c<x>; }
    };

    template <>
    struct drop_front_impl<string_tag> {
        template <std::size_t N, char ...xs, std::size_t ...i>
        static constexpr auto helper(string<xs...> const&, std::index_sequence<i...>) {
            constexpr char s[] = {xs...};
            return hana::string_c<s[i + N]...>;
        }

        template <char ...xs, typename N>
        static constexpr auto apply(string<xs...> const& s, N const&) {
            return helper<N::value>(s, std::make_index_sequence<
                (N::value < sizeof...(xs)) ? sizeof...(xs) - N::value : 0
            >{});
        }

        template <typename N>
        static constexpr auto apply(string<> const& s, N const&)
        { return s; }
    };

    template <>
    struct is_empty_impl<string_tag> {
        template <char ...s>
        static constexpr auto apply(string<s...> const&)
        { return hana::bool_c<sizeof...(s) == 0>; }
    };

    template <>
    struct at_impl<string_tag> {
        template <char ...s, typename N>
        static constexpr auto apply(string<s...> const&, N const&) {
            // We put a '\0' at the end to avoid an empty array.
            constexpr char characters[] = {s..., '\0'};
            constexpr auto n = N::value;
            return hana::char_c<characters[n]>;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Searchable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct contains_impl<string_tag> {
        template <char ...s, typename C>
        static constexpr auto
        helper(string<s...> const&, C const&, hana::true_) {
            constexpr char const characters[] = {s..., '\0'};
            constexpr char c = hana::value<C>();
            return hana::bool_c<
                detail::find(characters, characters + sizeof...(s), c)
                    != characters + sizeof...(s)
            >;
        }

        template <typename S, typename C>
        static constexpr auto helper(S const&, C const&, hana::false_)
        { return hana::false_c; }

        template <typename S, typename C>
        static constexpr auto apply(S const& s, C const& c)
        { return helper(s, c, hana::bool_c<hana::Constant<C>::value>); }
    };

    template <>
    struct find_impl<string_tag> {
        template <char ...s, typename Char>
        static constexpr auto apply(string<s...> const& str, Char const& c) {
            return hana::if_(contains_impl<string_tag>::apply(str, c),
                hana::just(c),
                hana::nothing
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Hashable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct hash_impl<string_tag> {
        template <typename String>
        static constexpr auto apply(String const&) {
            return hana::type_c<String>;
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_STRING_HPP

/* string.hpp
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
*/