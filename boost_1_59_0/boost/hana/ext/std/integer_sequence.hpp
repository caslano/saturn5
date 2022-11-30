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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_EXT_STD_INTEGER_SEQUENCE_HPP

/* integer_sequence.hpp
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
*/