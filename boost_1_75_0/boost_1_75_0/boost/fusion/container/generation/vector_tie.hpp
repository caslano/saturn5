/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR_TIE_11112014_2302
#define FUSION_VECTOR_TIE_11112014_2302

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/container/generation/detail/pp_vector_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct vector_tie
        {
            typedef vector<T&...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T&...>
    vector_tie(T&... arg)
    {
        return vector<T&...>(arg...);
    }
 }}


#endif
#endif


/* vector_tie.hpp
ozPbKm63t6qEyXMIJsuRtlmVnZuqFXikeZb/IyJRmXZpoMpsW0RnVyD3S1L2pg8Gk0cn7hSoKmdZauwYV1Em1OwIBf+8SiLUBjwEDFgOWxFJ2K3oSULLzXfwOu5DsG5VXJvk17VG5r28A70ruj4z4CrsK+xmJlZ4aYpgy7u35qV9FWpfFTfY6A3hZzwXVqrGfzJ+CN2y/gqVIRnw1bzyPzeDP3ZcCnDmPm+fqcJf/pR3l2zQuYJb38M3vao5EauK84lcgtqznUMKK/HpU+8AP/0lPkue833MBOGzgCbUZQlqw6jhHH/RGNWLO50msITPAIOWds4Se+2qk3Fm1DPAbO7FTpXfk+3NPK5/CHwP4YvgJdgV27lSVy3+k5QZdDtkCcBz7gGo5IvlW2i5s4HbS3CveDjk+UB7GtbxaIKAs38HP6A6dO5MxYY3THTtuM+E/6N3JTFWHbfcPIUu04mdz5/ayeuDQpMv1qoc7bZfaX2FM/qNy/nerMC/uXocFy0YFVZNQIO94UF393bWTK78gQpCxiemWPvHsYqTcXNUM9Cm8ovbc5WEPwpTWDxIA555UYfLxGpb6cGcU7ErhVNx3/rfwaH8hwFXNwbemF65blcSrEO84Q9k94D3hXNKNOcfhaa6br7HG72TkkBt5Jp6oCOWAiCc23JmVeFqe7DL3ItpVzPoGMeSKcd1HIfgiSsF0rVIHuB/5xzzXJ5A
*/