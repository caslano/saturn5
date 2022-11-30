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


namespace boost { namespace hana {
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
            "the _s string literal right now. See https://github.com/boostorg/hana/issues/80 "
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_STRING_HPP

/* string.hpp
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
*/