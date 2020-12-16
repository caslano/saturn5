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
hlKM6zypybcPbjDjGZvQEe5GHmtMlsAZNTiHZn6tpfqY/zyhbU4QtwmNxuvWF319KDKm+HcTcG8B/86ow9cLT78O2JcAW0+wbwH2iPnwieYBVtN8ymeTdvLyOH+Jl/lsPC/2x2aNgM4slJlHP1Uy1pmWLE5nS98MuFKFwJGoY74k8CRlnt75RWL+mpaY5lee3nQNYl5Vo+FGaVxulW+JrAnkd2PcXFu3W7wx7UrFAzp5l/vzuziNsjr0MQqm+UOcBoFaTRLLHfiTpRGBpXl9h8WZdci37+4UPRPibaNPw+NDOQJ/9WVc1bZj0K6Y7FNC6JnWZzD3i+l4sLQtNR/1HH0c9s9Be7LI+THLjew/ah5gNdlX+WzYvmpZVG0vW0ok9u0WoG30UK2X6kJu3OyD+7mw7VyhuNNCQ7NtaOeuQWVtIHJhiFQAL3B2u1LU6U6cC47yURHsCis0ydwiqt+TKJufvcSnmS5BYpR8SnKMkVJ3x8tymg+BoY36ttyrF788920l8LGiolxZjldTHUZa3bevYZyc3imNu36eZvDylBaGAf5ZfjKnd2t4nM7gekAm3NzWQ/chrfNomiPtW3LxqDM9mjAfXf/P0vT2ejrQIueW9Mk5fn0I+/N+pI9HS+OZrOoRxeYMjXhzru0Ny1mHiKqi+X2ew/MyY9enFm5baW6ZbxsBbznOrN+nCKwdsEsAe/09HKxD6E5TdLWtP8VsYk72uzlJumcz6k7rW9om9TFn2RUYxzE2uTuO8j0U7YFxIZisY5sQLSbmdCfosaZQ7kMyHtAFGjSFHsTP+PcBjjksKXelNFx7nfqcp/k8IPVHySu+Xt8Zx8d0wf0Ep+fl9MEoLciuy8PAq8HeRzl8u5abe6uhd2Y45rxH6tqqwCMl1sN+HwoHxB1AP6vRQHTIZ/DjI8JJlr9LovIaI3EA0psPiNXvUm8Qn4t98wNBZwbXfduDAEO7ckqBzzD6OL3UYG/J8XgMeMp1yOIW91a2B3sVj/eVDtrEGLHLcoA/6zgTm1wgc+AgYFcDVq9gta1N+nBy0g6bWBTyax6N+jPTqCaH9Qffz7JtajLiHfH0caCn80ed/sHBaGyfEKZTWzqW5ikeTei809OCNLLjRbJ0WZAubi8+YzmfqYaiL8f3hZ/JeDlKGD6PbRZeK6MoNztTmMR8VWdyY3PxefE6kWzsZOyFcVwX417i4fhOvVd4dWJqurtU4ziRMCebr7R4CldSjOAKxkt6g1o26R5L/H/y/mcVNbOxjYgfB6D5vHPIrxecaC3zthNgv4aML1K2Tm0yXi5DcSVl/NKYjK+rqusr2UzRqfqob2/Ver5ikJPeXNAtmrkQ6Y13gt5QO/6+l+a+jr2i66yzrgIevDNcE+2bLho+XA3c8uOxzwi6U2viA5ZdOKRJPjx5UbUYhikh34E2r1H9Od7onEW1tqmkIrHOPj3Y5odRv5SI5bt9BHCOMWtpQ/06QYHW6Y8G6CRerYOsXkzStuXHaT6OejAetqyKwjP+Or8drBTosNV71wfw3N/GUFxdm/xoDXhbT8I/Cfs7n/H9HYqUgM6Lk+Sq3ud2A/VbJmwU85uTxlTn6vkC0Yh/gF1mCDDdhfulgO5QpFqBKFLi01d8fqoVBIbKWis3AT6ard9bgzRoLKLgdeEB/h1nAR/kpkBfojX568A99HjzvsbiWudHOTQnXx2fHxRnMiUgbf5cBTyaq/bMAvqDRYQu0HJ2zDcdrs47HwlpNecj7TldoWXDne9U+b7gKT4ZOKeJXB+S7R8mZBY1kNjqdzRA8zLwc4HyKaO3+AB78zzY+PMAq4nHOM3w0FAs78qqek+VUJzkufiL5XQ+qrNbP3E=
*/