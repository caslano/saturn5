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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_EXT_STD_ARRAY_HPP

/* array.hpp
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
*/