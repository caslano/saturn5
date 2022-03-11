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
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
*/