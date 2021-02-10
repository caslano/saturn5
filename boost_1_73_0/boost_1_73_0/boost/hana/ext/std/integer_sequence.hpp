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
NWXqTq+9GewaIn/fY+Hdgr7wWOihPl22eJsJD9ufqcMldjFE3Kh3jEsR+9F4g1HIxHEHLyvzZTS96aiUUGzbU8WuvFSVNGIldKR36SMDWp3p7FGhY3rYBcN4Abi6ohRJorgD0AllfvrQfoUGT2SODiykY3axiJzsdksRPbAOcwhay09V9G1dF9WqS/roHB6y2z0migucBXRenaxRf/UDFvTsir0tZjkSt0cH5gmNdDknInZ84jPkda7dASEvSXjorJYPOV3XtZuI05EZPqcTDjkovHmES415FGYzD2fJNYBQRjfDkzbnWS7HbMyN5krrkjf8vLPxTbL/zYz+gy/BzDhPLRJndpjcKwm4S8eP+hEasomutTtISXj0zCeNxqv8VYivRa8VhNiQlP9gipXmWHVdQPbSnc3sjKYVe3FKpsUW26X5Wi9eUTBwpl2tSyNYLRiPWsC0RN6w+furo3udOo5OD1fh1CaBjSlw9rnnzuT3nzGM5DpSkWzk67h88A6ITsPskOneOhzkG70hI+kH6QTuHdroZXb3nzMfQkYgljs8IFu9Svouj4TUAfSlN3VXifAMFXcB+IiUHaU4vTQdnC7vxE0lrrvtHGE4zbk4VHBlBmBb8HHKHgybbXhF9+DQaze6lbfSjJlRQcz5
*/