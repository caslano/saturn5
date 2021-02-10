/*=============================================================================
    Copyright (c) 2015 Agustin K-ballo Berge
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_SUPPORT_DETAIL_INDEX_SEQUENCE_06232015_1038
#define BOOST_FUSION_SUPPORT_DETAIL_INDEX_SEQUENCE_06232015_1038

#include <boost/fusion/support/config.hpp>
#include <cstddef>

// GCC5 has O(logN) implementation, see https://gcc.gnu.org/PR66059 .
#if (defined(__cpp_lib_integer_sequence) && __cpp_lib_integer_sequence >= 201304) \
 || (defined(BOOST_LIBSTDCXX_VERSION) \
     && BOOST_LIBSTDCXX_VERSION >= 500000 && __cplusplus >= 201402)
#include <utility>
#define BOOST_FUSION_STDLIB_HAS_INTEGER_SEQUENCE
#endif

namespace boost { namespace fusion { namespace detail
{
#ifdef BOOST_FUSION_STDLIB_HAS_INTEGER_SEQUENCE
    // Use aliasing templates without checking availability, the compiler should work.
    template <std::size_t ...Ints>
    using index_sequence = std::index_sequence<Ints...>;

    template <std::size_t N>
    struct make_index_sequence
    {
        using type = std::make_index_sequence<N>;
    };
#else
    template <std::size_t ...Ints>
    struct index_sequence
    {
        typedef std::size_t value_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static std::size_t size() BOOST_NOEXCEPT
        { return sizeof...(Ints); }

        // non standard extension
        typedef index_sequence type;
    };

    template <typename Left, typename Right>
    struct _make_index_sequence_join;

    template <std::size_t... Left, std::size_t... Right>
    struct _make_index_sequence_join<
        index_sequence<Left...>, index_sequence<Right...>
    > : index_sequence<Left..., (sizeof...(Left) + Right)...>
    {};

    template <std::size_t N>
    struct make_index_sequence
      : _make_index_sequence_join<
            typename make_index_sequence<N / 2>::type
          , typename make_index_sequence<N - N / 2>::type
        >
    {};

    template <>
    struct make_index_sequence<1>
      : index_sequence<0>
    {};

    template <>
    struct make_index_sequence<0>
      : index_sequence<>
    {};
#endif
}}}

#endif


/* index_sequence.hpp
EA5ydJmVKS2kBl8iFFIhjBef72fz32LYljIrWcnONOBK06gcSvGIYDFD+djqqIX1YAoSJ+W5dJ4UNl4a3SduBI+2cqyD6YVyBsSjkEqkRCQ8lN7X7ufBIGusIusHucncINu73y99dfDknoyoxA5M7cEbaBzGwMgYKpPLgmcKCG3WTaqkK+OjNUSl84Gx4FAp1kVyEl1rNsKqC0/MMKjJYul5ckY7ptqWpvoXkOLIWorGaiKiOBAoNxTmGBoqJxvAwfM9RRfTEOA3U3O0NwejyRg4G61gtjqDVDjpYvgyW18v7tbwZbRcjubre1hcwWh+z8p+n80nlHpJZBbwqbboiNyCrGolMe84v98YRNG51JlqcoQzzl7i0Dd1vzzjg7aphHYxma1Gn26mye3sdhpRx+DE5ZDu4MrYapTnUJCVHqvaWGF34DzNGwQioGA0VNmMm+nCwF8RQFYKCz0tKhzSysmvmHjgpUK98eXwAHkUqgmYYJspCsJlRlPZePca2+37XR0klNEbKJTYuCMkbYoC7bDrEj2ojSQZy4nHJ0qbJJEW0/rHToViamplRM7uHMxtca+NoPraskTwjSnW+3rkHSZiRB9mBWjj6Sb7ONwskflG0KV+axxVbKVSkGJrYDCoZaa1rYeHFnh0LmSm
*/