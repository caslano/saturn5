/*!
@file
Adapts `std::integer_sequence` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_STD_INTEGER_SEQUENCE_HPP
#define BOOST_HANA_EXT_STD_INTEGER_SEQUENCE_HPP

#include <boost/hana/bool.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/ext/std/integral_constant.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/unpack.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace std {
    //! @ingroup group-ext-std
    //! Adaptation of `std::integer_sequence` for Hana.
    //!
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! 1. `Comparable`\n
    //! Two `std::integer_sequence`s are equal if and only if they have the
    //! same number of elements, and if corresponding elements compare equal.
    //! The types of the elements held in both `integer_sequence`s may be
    //! different, as long as they can be compared.
    //! @include example/ext/std/integer_sequence/comparable.cpp
    //!
    //! 2. `Foldable`\n
    //! Folding an `integer_sequence` is equivalent to folding a sequence of
    //! `std::integral_constant`s with the corresponding types.
    //! @include example/ext/std/integer_sequence/foldable.cpp
    //!
    //! 3. `Iterable`\n
    //! Iterating over an `integer_sequence` is equivalent to iterating over
    //! a sequence of the corresponding `std::integral_constant`s.
    //! @include example/ext/std/integer_sequence/iterable.cpp
    //!
    //! 4. `Searchable`\n
    //! Searching through an `integer_sequence` is equivalent to searching
    //! through the corresponding sequence of `std::integral_constant`s.
    //! @include example/ext/std/integer_sequence/searchable.cpp
    template <typename T, T ...v>
    struct integer_sequence { };
}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace std { struct integer_sequence_tag; }}

    template <typename T, T ...v>
    struct tag_of<std::integer_sequence<T, v...>> {
        using type = ext::std::integer_sequence_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // Comparable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct equal_impl<ext::std::integer_sequence_tag, ext::std::integer_sequence_tag> {
        template <typename X, X ...xs, typename Y, Y ...ys>
        static constexpr hana::bool_<detail::fast_and<(xs == ys)...>::value>
        apply(std::integer_sequence<X, xs...> const&, std::integer_sequence<Y, ys...> const&)
        { return {}; }

        template <typename Xs, typename Ys>
        static constexpr hana::false_ apply(Xs const&, Ys const&, ...)
        { return {}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct unpack_impl<ext::std::integer_sequence_tag> {
        template <typename T, T ...v, typename F>
        static constexpr decltype(auto)
        apply(std::integer_sequence<T, v...> const&, F&& f) {
            return static_cast<F&&>(f)(std::integral_constant<T, v>{}...);
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Iterable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct at_impl<ext::std::integer_sequence_tag> {
        template <typename T, T ...v, typename N>
        static constexpr auto apply(std::integer_sequence<T, v...> const&, N const&) {
            constexpr std::size_t n = N::value;
            constexpr T values_[] = {v...};
            return std::integral_constant<T, values_[n]>{};
        }
    };

    template <>
    struct drop_front_impl<ext::std::integer_sequence_tag> {
        template <std::size_t n, typename T, T ...t, std::size_t ...i>
        static constexpr auto drop_front_helper(std::integer_sequence<T, t...>,
                                                std::index_sequence<i...>)
        {
            constexpr T ts[sizeof...(t)+1] = {t...}; // avoid 0-sized array
            return std::integer_sequence<T, ts[n + i]...>{};
        }

        template <typename T, T ...t, typename N>
        static constexpr auto apply(std::integer_sequence<T, t...> ts, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = sizeof...(t);
            return drop_front_helper<n>(ts,
                    std::make_index_sequence<(n < len ? len - n : 0)>{});
        }
    };

    template <>
    struct is_empty_impl<ext::std::integer_sequence_tag> {
        template <typename T, T ...xs>
        static constexpr auto apply(std::integer_sequence<T, xs...> const&)
        { return hana::bool_c<sizeof...(xs) == 0>; }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_STD_INTEGER_SEQUENCE_HPP

/* integer_sequence.hpp
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
*/