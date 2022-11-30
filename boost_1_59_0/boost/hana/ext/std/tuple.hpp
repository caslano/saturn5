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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_EXT_STD_TUPLE_HPP

/* tuple.hpp
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
*/