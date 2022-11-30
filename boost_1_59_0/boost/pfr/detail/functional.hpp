// Copyright (c) 2016-2022 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PFR_DETAIL_FUNCTIONAL_HPP
#define BOOST_PFR_DETAIL_FUNCTIONAL_HPP
#pragma once

#include <boost/pfr/detail/config.hpp>

#include <functional>
#include <cstdint>

#include <boost/pfr/detail/sequence_tuple.hpp>

namespace boost { namespace pfr { namespace detail {
    template <std::size_t I, std::size_t N>
    struct equal_impl {
        template <class T, class U>
        constexpr static bool cmp(const T& v1, const U& v2) noexcept {
            return ::boost::pfr::detail::sequence_tuple::get<I>(v1) == ::boost::pfr::detail::sequence_tuple::get<I>(v2)
                && equal_impl<I + 1, N>::cmp(v1, v2);
        }
    };

    template <std::size_t N>
    struct equal_impl<N, N> {
        template <class T, class U>
        constexpr static bool cmp(const T&, const U&) noexcept {
            return T::size_v == U::size_v;
        }
    };

    template <std::size_t I, std::size_t N>
    struct not_equal_impl {
        template <class T, class U>
        constexpr static bool cmp(const T& v1, const U& v2) noexcept {
            return ::boost::pfr::detail::sequence_tuple::get<I>(v1) != ::boost::pfr::detail::sequence_tuple::get<I>(v2)
                || not_equal_impl<I + 1, N>::cmp(v1, v2);
        }
    };

    template <std::size_t N>
    struct not_equal_impl<N, N> {
        template <class T, class U>
        constexpr static bool cmp(const T&, const U&) noexcept {
            return T::size_v != U::size_v;
        }
    };

    template <std::size_t I, std::size_t N>
    struct less_impl {
        template <class T, class U>
        constexpr static bool cmp(const T& v1, const U& v2) noexcept {
            return sequence_tuple::get<I>(v1) < sequence_tuple::get<I>(v2)
                || (sequence_tuple::get<I>(v1) == sequence_tuple::get<I>(v2) && less_impl<I + 1, N>::cmp(v1, v2));
        }
    };

    template <std::size_t N>
    struct less_impl<N, N> {
        template <class T, class U>
        constexpr static bool cmp(const T&, const U&) noexcept {
            return T::size_v < U::size_v;
        }
    };

    template <std::size_t I, std::size_t N>
    struct less_equal_impl {
        template <class T, class U>
        constexpr static bool cmp(const T& v1, const U& v2) noexcept {
            return sequence_tuple::get<I>(v1) < sequence_tuple::get<I>(v2)
                || (sequence_tuple::get<I>(v1) == sequence_tuple::get<I>(v2) && less_equal_impl<I + 1, N>::cmp(v1, v2));
        }
    };

    template <std::size_t N>
    struct less_equal_impl<N, N> {
        template <class T, class U>
        constexpr static bool cmp(const T&, const U&) noexcept {
            return T::size_v <= U::size_v;
        }
    };

    template <std::size_t I, std::size_t N>
    struct greater_impl {
        template <class T, class U>
        constexpr static bool cmp(const T& v1, const U& v2) noexcept {
            return sequence_tuple::get<I>(v1) > sequence_tuple::get<I>(v2)
                || (sequence_tuple::get<I>(v1) == sequence_tuple::get<I>(v2) && greater_impl<I + 1, N>::cmp(v1, v2));
        }
    };

    template <std::size_t N>
    struct greater_impl<N, N> {
        template <class T, class U>
        constexpr static bool cmp(const T&, const U&) noexcept {
            return T::size_v > U::size_v;
        }
    };

    template <std::size_t I, std::size_t N>
    struct greater_equal_impl {
        template <class T, class U>
        constexpr static bool cmp(const T& v1, const U& v2) noexcept {
            return sequence_tuple::get<I>(v1) > sequence_tuple::get<I>(v2)
                || (sequence_tuple::get<I>(v1) == sequence_tuple::get<I>(v2) && greater_equal_impl<I + 1, N>::cmp(v1, v2));
        }
    };

    template <std::size_t N>
    struct greater_equal_impl<N, N> {
        template <class T, class U>
        constexpr static bool cmp(const T&, const U&) noexcept {
            return T::size_v >= U::size_v;
        }
    };

    // Hash combine functions copied from Boost.ContainerHash
    // https://github.com/boostorg/container_hash/blob/171c012d4723c5e93cc7cffe42919afdf8b27dfa/include/boost/container_hash/hash.hpp#L311
    // that is based on Peter Dimov's proposal
    // http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2005/n1756.pdf
    // issue 6.18.
    //
    // This also contains public domain code from MurmurHash. From the
    // MurmurHash header:
    //
    // MurmurHash3 was written by Austin Appleby, and is placed in the public
    // domain. The author hereby disclaims copyright to this source code.
    template <typename SizeT>
    constexpr void hash_combine(SizeT& seed, SizeT value) noexcept {
        seed ^= value + 0x9e3779b9 + (seed<<6) + (seed>>2);
    }

    constexpr auto rotl(std::uint32_t x, std::uint32_t r) noexcept {
        return (x << r) | (x >> (32 - r));
    }

    constexpr void hash_combine(std::uint32_t& h1, std::uint32_t k1) noexcept {
          const std::uint32_t c1 = 0xcc9e2d51;
          const std::uint32_t c2 = 0x1b873593;

          k1 *= c1;
          k1 = detail::rotl(k1,15);
          k1 *= c2;

          h1 ^= k1;
          h1 = detail::rotl(h1,13);
          h1 = h1*5+0xe6546b64;
    }

#if defined(INT64_MIN) && defined(UINT64_MAX)
    constexpr void hash_combine(std::uint64_t& h, std::uint64_t k) noexcept {
        const std::uint64_t m = 0xc6a4a7935bd1e995ULL;
        const int r = 47;

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;

        // Completely arbitrary number, to prevent 0's
        // from hashing to 0.
        h += 0xe6546b64;
    }
#endif

    template <typename T>
    auto compute_hash(const T& value, long /*priority*/)
        -> decltype(std::hash<T>()(value))
    {
        return std::hash<T>()(value);
    }

    template <typename T>
    std::size_t compute_hash(const T& /*value*/, int /*priority*/) {
        static_assert(sizeof(T) && false, "====================> Boost.PFR: std::hash not specialized for type T");
        return 0;
    }

    template <std::size_t I, std::size_t N>
    struct hash_impl {
        template <class T>
        constexpr static std::size_t compute(const T& val) noexcept {
            std::size_t h = detail::compute_hash( ::boost::pfr::detail::sequence_tuple::get<I>(val), 1L );
            detail::hash_combine(h, hash_impl<I + 1, N>::compute(val) );
            return h;
        }
    };

    template <std::size_t N>
    struct hash_impl<N, N> {
        template <class T>
        constexpr static std::size_t compute(const T&) noexcept {
            return 0;
        }
    };

///////////////////// Define min_element and to avoid inclusion of <algorithm>
    constexpr std::size_t min_size(std::size_t x, std::size_t y) noexcept {
        return x < y ? x : y;
    }

    template <template <std::size_t, std::size_t> class Visitor, class T, class U>
    constexpr bool binary_visit(const T& x, const U& y) {
        constexpr std::size_t fields_count_lhs = detail::fields_count<std::remove_reference_t<T>>();
        constexpr std::size_t fields_count_rhs = detail::fields_count<std::remove_reference_t<U>>();
        constexpr std::size_t fields_count_min = detail::min_size(fields_count_lhs, fields_count_rhs);
        typedef Visitor<0, fields_count_min> visitor_t;

#if BOOST_PFR_USE_CPP17 || BOOST_PFR_USE_LOOPHOLE
        return visitor_t::cmp(detail::tie_as_tuple(x), detail::tie_as_tuple(y));
#else
        bool result = true;
        ::boost::pfr::detail::for_each_field_dispatcher(
            x,
            [&result, &y](const auto& lhs) {
                constexpr std::size_t fields_count_rhs_ = detail::fields_count<std::remove_reference_t<U>>();
                ::boost::pfr::detail::for_each_field_dispatcher(
                    y,
                    [&result, &lhs](const auto& rhs) {
                        result = visitor_t::cmp(lhs, rhs);
                    },
                    detail::make_index_sequence<fields_count_rhs_>{}
                );
            },
            detail::make_index_sequence<fields_count_lhs>{}
        );

        return result;
#endif
    }

}}} // namespace boost::pfr::detail

#endif // BOOST_PFR_DETAIL_FUNCTIONAL_HPP

/* functional.hpp
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
*/