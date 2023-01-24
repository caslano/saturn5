/*!
@file
Adapts `std::tuple` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_STD_TUPLE_HPP
#define BOOST_HANA_EXT_STD_TUPLE_HPP

#include <boost/hana/bool.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/empty.hpp>
#include <boost/hana/fwd/flatten.hpp>
#include <boost/hana/fwd/front.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/length.hpp>
#include <boost/hana/fwd/lift.hpp>
#include <boost/hana/integral_constant.hpp>

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace std {
    //! @ingroup group-ext-std
    //! Adapter for `std::tuple`s.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! A `std::tuple` is a model of the `Sequence` concept, and all the
    //! concepts it refines. That makes it essentially the same as a Hana
    //! tuple, although the complexity of some operations might differ from
    //! that of Hana's tuple.
    //!
    //! @include example/ext/std/tuple.cpp
    template <typename ...T>
    struct tuple { };
}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace std { struct tuple_tag; }}

    template <typename ...Xs>
    struct tag_of<std::tuple<Xs...>> {
        using type = ext::std::tuple_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // make
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct make_impl<ext::std::tuple_tag> {
        template <typename ...Xs>
        static constexpr decltype(auto) apply(Xs&& ...xs) {
            return std::make_tuple(static_cast<Xs&&>(xs)...);
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Applicative
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct lift_impl<ext::std::tuple_tag> {
        template <typename X>
        static constexpr auto apply(X&& x) {
            return std::tuple<typename detail::decay<X>::type>{
                                                static_cast<X&&>(x)};
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Monad
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct flatten_impl<ext::std::tuple_tag> {
        template <typename Xs, std::size_t ...i>
        static constexpr decltype(auto)
        flatten_helper(Xs&& xs, std::index_sequence<i...>) {
            return std::tuple_cat(std::get<i>(static_cast<Xs&&>(xs))...);
        }

        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs) {
            using Raw = typename std::remove_reference<Xs>::type;
            constexpr std::size_t Length = std::tuple_size<Raw>::value;
            return flatten_helper(static_cast<Xs&&>(xs),
                                  std::make_index_sequence<Length>{});
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // MonadPlus
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct empty_impl<ext::std::tuple_tag> {
        static constexpr auto apply()
        { return std::tuple<>{}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Iterable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct front_impl<ext::std::tuple_tag> {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs) {
            return std::get<0>(static_cast<Xs&&>(xs));
        }
    };

    template <>
    struct drop_front_impl<ext::std::tuple_tag> {
        template <std::size_t n, typename Xs, std::size_t ...i>
        static constexpr auto drop_front_helper(Xs&& xs, std::index_sequence<i...>) {
            return std::make_tuple(
                hana::at_c<n + i>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            using Raw = typename std::remove_reference<Xs>::type;
            constexpr std::size_t n = N::value;
            constexpr auto len = std::tuple_size<Raw>::value;
            return drop_front_helper<n>(static_cast<Xs&&>(xs),
                    std::make_index_sequence<(n < len ? len - n : 0)>{});
        }
    };

    template <>
    struct is_empty_impl<ext::std::tuple_tag> {
        template <typename ...Xs>
        static constexpr auto apply(std::tuple<Xs...> const&)
        { return hana::bool_c<sizeof...(Xs) == 0>; }
    };

    template <>
    struct at_impl<ext::std::tuple_tag> {
        template <typename Xs, typename N>
        static constexpr decltype(auto) apply(Xs&& xs, N const&) {
            constexpr std::size_t index = N::value;
            return std::get<index>(static_cast<Xs&&>(xs));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct length_impl<ext::std::tuple_tag> {
        template <typename ...Xs>
        static constexpr auto apply(std::tuple<Xs...> const&) {
            return hana::size_c<sizeof...(Xs)>;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Sequence
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct Sequence<ext::std::tuple_tag> {
        static constexpr bool value = true;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_STD_TUPLE_HPP

/* tuple.hpp
+JACvFoxjw90jpX3TnX6lofIvSyb1EP2ZqCfo9G7zb598qJHqvCh2gZ8hlc+bhH+emseryzJ42fUbeS4RXVTOU4SehbmVSt8XrXct7FaDm1Ub8+zSMsHfGM47hG9vDj7PylrHpg7BmtL783MI9fAsZWaLuETqupNeTz5IpPjbnwCCorLAFp6df3CvI3A4ffMWvEYZ30RNTfFlS9SncXinuM9HT0n5EW7S+lru+kAS81w/oazvnkxKhinwDfLOVF790VUl5Qmy+vzYOwmzMBocU9v9+FZVgC7nbqi/x5ZAXVrF7Ose1jWXZjnzUchD8pmY3U9kzmqLvJ7qOvmllh/fjjxP+pPwfsXKKBxXwsbIHO1MDPrboAMv+3wL1QtrOmaUy1s8FcLN5kfoQmnu6qFQ3tfpAe4ZYsiaRy3vrZa+Hrvotlw0tqYVi28tyyP7wVYLdXCFZEH8t48jpfUx62+m/LSlXfl5kwIWOAf74MxmJRFnTHQ7FEMvt4LNXdXC82BpEXokHr9jEWzgSvfuAVxuA1wOCmsaE+optf8DERCbc2T6yCQBNkm30ZRfe9WPYu+yuePeo47KmiouLO7wKUwUQNlTWq7fGXvKkuys32ObsWRaWrzOY5Est5C0QBQmLIjPke7zR99fs4+LMiL0FL+B9TJHFEc7zb+/BMlk57vm5ZdNGswwIuTmpZcdEXdsTON1JzZY2z8+TeNkOTU
*/