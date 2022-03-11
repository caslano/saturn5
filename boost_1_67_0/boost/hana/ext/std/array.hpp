/*!
@file
Adapts `std::array` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_STD_ARRAY_HPP
#define BOOST_HANA_EXT_STD_ARRAY_HPP

#include <boost/hana/bool.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/algorithm.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/length.hpp>
#include <boost/hana/fwd/less.hpp>
#include <boost/hana/integral_constant.hpp>

#include <array>
#include <cstddef>
#include <type_traits>
#include <utility>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace std {
    //! @ingroup group-ext-std
    //! Adaptation of `std::array` for Hana.
    //!
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! 1. `Comparable`\n
    //! `std::array`s are compared as per `std::equal`, except that two arrays
    //! with different sizes compare unequal instead of triggering an error
    //! and the result of the comparison is `constexpr` if both arrays are
    //! `constexpr`.
    //! @include example/ext/std/array/comparable.cpp
    //!
    //! 2. `Orderable`\n
    //! `std::array`s are ordered with the usual lexicographical ordering,
    //! except that two arrays with different size can be ordered instead
    //! of triggering an error and the result of the comparison is `constexpr`
    //! if both arrays are `constexpr`.
    //! @include example/ext/std/array/orderable.cpp
    //!
    //! 3. `Foldable`\n
    //! Folding an array from the left is equivalent to calling
    //! `std::accumulate` on it, except it can be `constexpr`.
    //! @include example/ext/std/array/foldable.cpp
    //!
    //! 4. `Iterable`\n
    //! Iterating over a `std::array` is equivalent to iterating over it with
    //! a normal `for` loop.
    //! @include example/ext/std/array/iterable.cpp
    template <typename T, std::size_t N>
    struct array { };
}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace std { struct array_tag; }}

    template <typename T, std::size_t N>
    struct tag_of<std::array<T, N>> {
        using type = ext::std::array_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct length_impl<ext::std::array_tag> {
        template <typename Xs>
        static constexpr auto apply(Xs const&) {
            return hana::size_c<std::tuple_size<Xs>::type::value>;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Iterable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct at_impl<ext::std::array_tag> {
        template <typename Xs, typename N>
        static constexpr decltype(auto) apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            return std::get<n>(static_cast<Xs&&>(xs));
        }
    };

    template <>
    struct drop_front_impl<ext::std::array_tag> {
        template <std::size_t n, typename Xs, std::size_t ...i>
        static constexpr auto drop_front_helper(Xs&& xs, std::index_sequence<i...>) {
            using T = typename std::remove_reference<Xs>::type::value_type;
            return std::array<T, sizeof...(i)>{{static_cast<Xs&&>(xs)[n + i]...}};
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = std::tuple_size<
                typename std::remove_cv<
                    typename std::remove_reference<Xs>::type
                >::type
            >::value;
            return drop_front_helper<n>(static_cast<Xs&&>(xs),
                    std::make_index_sequence<(n < len ? len - n : 0)>{});
        }
    };

    template <>
    struct is_empty_impl<ext::std::array_tag> {
        template <typename T, std::size_t N>
        static constexpr auto apply(std::array<T, N> const&) {
            return hana::bool_c<N == 0>;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Comparable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct equal_impl<ext::std::array_tag, ext::std::array_tag> {
        template <typename T, std::size_t n, typename U>
        static constexpr bool apply(std::array<T, n> const& xs, std::array<U, n> const& ys)
        { return detail::equal(&xs[0], &xs[0] + n, &ys[0], &ys[0] + n); }

        template <typename T, typename U>
        static constexpr auto apply(std::array<T, 0> const&, std::array<U, 0> const&)
        { return hana::true_c; }

        template <typename T, std::size_t n, typename U, std::size_t m>
        static constexpr auto apply(std::array<T, n> const&, std::array<U, m> const&)
        { return hana::false_c; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Orderable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct less_impl<ext::std::array_tag, ext::std::array_tag> {
        template <typename T, std::size_t n, typename U, std::size_t m>
        static constexpr auto apply(std::array<T, n> const& xs, std::array<U, m> const& ys) {
            // This logic is more complex than it needs to be because we can't
            // use `.begin()` and `.end()`, which are not constexpr in C++14,
            // and because `&arr[0]` is UB when the array is empty.
            if (xs.empty()) {
                return !ys.empty();
            } else {
                if (ys.empty()) {
                    return false;
                } else {
                    return detail::lexicographical_compare(&xs[0], &xs[0] + n,
                                                           &ys[0], &ys[0] + m);
                }
            }
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_STD_ARRAY_HPP

/* array.hpp
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
*/