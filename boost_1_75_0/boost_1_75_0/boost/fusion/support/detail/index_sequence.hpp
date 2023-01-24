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
A2ZvfAroi5HuwzKoHCj2hVSM3m1j/VpeWtMgOfKhLejcz33gFjpScgDFVJ9pXyBcqMw0bTwda7vsOVFcwKDE9SXVKPuQ235nt2vvmhDsXEoK9cWweaLrTr1WLnw6z7QyPuotuYKsBr9r9fjTdsB6Lff19vHI5c0h8D8sgXrXL8z5tK9ZkcOnXkpoIpV64W4RSPInHY2u5+/U8TZMBpXX75luXOu98S/tgksBzEeKwSe2DL6HBwUpzUIS/FLcrkVZT01v/nWBtHaqYI2bkTtrHrJBLUx8kfV8wnsW7S99T+7eGnF2Ul7a/FrlHUx+j6c/C3GocK+fPBT/1ctzoM1lLW4S1GJufLM7nHnDYV0H1FecfRfHiEioN8O8TO+xspIun9LLtc62KNx5NBWWN/Vnuiyi5R8rra5G6rOvetLfvuAZt6KS5nM0TQPpep2vr253dlnULx+4sd4GV1mZmPoiB7I8HkvyuiJ8X9jeerU5UJGS8LP+eMtFJma9b2C5aV5qZtp4/aKXRr60g619Ovlaaaebz0yHIJVLhcLJ7vw7JnV3/emXCi9tP/DIMZTfqX2u/s5pzUFq5rbvAzx/95veX6O+3aZ/T104PFSzEy099GtfPatu53vJRYuQe8L69Y9s42Hvgq5NSLpl2WaCu/ptNp9J6X3AjARLwxn8fYOj49e8zj+hv/3sNcCK94nv7bloSfYPS3T6vuLVEpUv
*/