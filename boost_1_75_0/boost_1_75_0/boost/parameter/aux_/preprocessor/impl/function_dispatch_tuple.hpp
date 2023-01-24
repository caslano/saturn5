// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_DISPATCH_TUPLE_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_DISPATCH_TUPLE_HPP

#include <boost/preprocessor/tuple/elem.hpp>

// Accessor macros for the input tuple to the dispatch macros.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_BASE_NAME(x)                       \
    BOOST_PP_TUPLE_ELEM(5, 0, x)
/**/

#define BOOST_PARAMETER_FUNCTION_DISPATCH_SPLIT_ARGS(x)                      \
    BOOST_PP_TUPLE_ELEM(5, 1, x)
/**/

#define BOOST_PARAMETER_FUNCTION_DISPATCH_IS_MEMBER(x)                       \
    BOOST_PP_TUPLE_ELEM(5, 2, x)
/**/

#define BOOST_PARAMETER_FUNCTION_DISPATCH_IS_CONST(x)                        \
    BOOST_PP_TUPLE_ELEM(5, 3, x)
/**/

#define BOOST_PARAMETER_FUNCTION_DISPATCH_TAG_NAMESPACE(x)                   \
    BOOST_PP_TUPLE_ELEM(5, 4, x)
/**/

#endif  // include guard


/* function_dispatch_tuple.hpp
lgZ9PZkZ6FvoU8ewOYIjLM7p8aH/xSd2da+cYl0GvvVi7khoMvbUe2dlLIfRMf6xkh/LVx7K1aruu4VeQHv80VvxDKNoGcDLgqTn7mG3NjBcfLxfYQYa/snq/qH+t+IIxvRoutLsDXeR0tnv6Qu52Uk3GyMK4NzWQNH4+C0rq2UZ2QN2xUCbzm/hKuwXJYT7FuTH6w2AVdhwLZ5jOmsAy9Boc1L10Goz2a1eCaExUVVfpNoZoHJwtAGbeclU2CEX2ysqwQHDvR9vFV1kWY3VvoDUSrAzxR0JVIgkEoeDv8PvK8qbzx1ncD9nK+sjjnLMa43qhznihiqoglPICWZTpEBG83F61i4Hgvra5iUK8MP9eGLywpHb8TR3VJ0DP8O5MaJRnjDIZsxOt87cUyR158TOdx3X4HIxPx4aMUpr2I3SQY7A512g6AbJgpfjKkhHUjGoQMYnSFE8FTSs04B0ngG2vxrJTMJ5wPYhyi7G7NLbpyh+mPEF+1uJStL7C1UfvOQdUEpMi+ZJ5eoQ+b83x4J88kmiIGrDfmYTZrR5a7zaDA4QQd58w6Rfn4dgQpGEf38UsRF7Rix9q2dz2VqpHCx9JYByNyYv2al4A/4Erx84gi+LV4/mo4rD3+Ae4yAkPthZsPQ3JPOa4sCiI5VnnV2Ra+DsERj0j910nGelBchM4A8ur/Hl7Ypgw/f12QWss6m9e0L+v94yu2WN
*/