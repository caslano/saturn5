/*==============================================================================
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !BOOST_PP_IS_ITERATING

#include <boost/preprocessor/tuple/elem.hpp>

#ifndef BOOST_PHOENIX_ITERATION_PARAMS
#error "BOOST_PHOENIX_ITERATION_PARAMS not defined"
#endif

#define BOOST_PHOENIX_ITERATION_PARAMS_SIZE                                     \
    BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PHOENIX_ITERATION_PARAMS)                   \
/**/

#define BOOST_PHOENIX_ITERATION_TUPLE                                           \
    BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PHOENIX_ITERATION_PARAMS)                   \
/**/

#define BOOST_PHOENIX_ITERATION_START                                           \
    BOOST_PP_TUPLE_ELEM(                                                        \
        BOOST_PHOENIX_ITERATION_PARAMS_SIZE, 0, BOOST_PHOENIX_ITERATION_TUPLE)  \
/**/

#define BOOST_PHOENIX_ITERATION_END                                             \
    BOOST_PP_TUPLE_ELEM(                                                        \
        BOOST_PHOENIX_ITERATION_PARAMS_SIZE, 1, BOOST_PHOENIX_ITERATION_TUPLE)  \
/**/


#define BOOST_PHOENIX_ITERATION_FILE()                                          \
    BOOST_PP_TUPLE_ELEM(                                                        \
        BOOST_PHOENIX_ITERATION_PARAMS_SIZE, 2, BOOST_PHOENIX_ITERATION_TUPLE)  \
/**/

#if BOOST_PHOENIX_ITERATION_PARAMS_SIZE == 3

#define BOOST_PP_ITERATION_PARAMS_1                                             \
    (3, (BOOST_PHOENIX_ITERATION_START, BOOST_PHOENIX_ITERATION_END,            \
    <boost/phoenix/support/detail/iterate.hpp>))                                \
/**/

#else

#define BOOST_PHOENIX_ITERATION_FLAG                                            \
    BOOST_PP_TUPLE_ELEM(                                                        \
        BOOST_PHOENIX_ITERATION_PARAMS_SIZE, 3, BOOST_PHOENIX_ITERATION_TUPLE)  \
/**/

#define BOOST_PP_ITERATION_PARAMS_1                                             \
    (4, (BOOST_PHOENIX_ITERATION_START, BOOST_PHOENIX_ITERATION_END,            \
    <boost/phoenix/support/detail/iterate.hpp>,                                 \
    BOOST_PHOENIX_ITERATION_FLAG))                                              \
/**/

#endif

#include BOOST_PP_ITERATE()

#undef BOOST_PHOENIX_ITERATION_PARAMS_SIZE
#undef BOOST_PHOENIX_ITERATION_TUPLE
#undef BOOST_PHOENIX_ITERATION_START
#undef BOOST_PHOENIX_ITERATION_END
#undef BOOST_PHOENIX_ITERATION_PARAMS

#else

#undef BOOST_PHOENIX_IS_ITERATING
#define BOOST_PHOENIX_IS_ITERATING 1

#include <boost/phoenix/support/detail/iterate_undef.hpp>
#include <boost/phoenix/support/detail/iterate_define.hpp>


#include BOOST_PHOENIX_ITERATION_FILE()

#undef BOOST_PHOENIX_ITERATION

#undef BOOST_PHOENIX_IS_ITERATING
#define BOOST_PHOENIX_IS_ITERATING 0

#include <boost/phoenix/support/detail/iterate_undef.hpp>
#include <boost/phoenix/support/detail/iterate_define.hpp>

#endif

/* iterate.hpp
WabluSGPJjTi9UMXSOZ863ePCQrdhgjyImPr2VcpBEBzY1+l6BKZj3lEJ2htp8IIWY41XO+zKL2uGCGfkmkLQJVSECpNRHh5qS3yNKO2d2eTHqmYYZNcppcamiY7+jJ5QkjD0xw+kgtXtdzFP88NbEIuPpnqUeQ08qAhadp2MG9ns7mnqxEzpAvSd5XkcTqVYv4cQlVYR0xq6IgMy7uAtgWaRyOuXKaF9wvTxHic8Cgw1R+1M+OyIFSFYbami1dVGCDQnk/7uA4CUtKSiqMojdimlfkj70vKnYZGMB36fljnrNCeBSkSrw4H3x0gGO2qIEqqcS6T+ES42XsddOTqnNvn8cp1+6nvzbgYdWWO31GbItulxxp8ZwgIsjmQyDNe+F0QTQxq76BoKI+bLsrl09/dEF6h0n+mK/i9UtkEWuSH5iqTxnQFqqapIoNX+wbny8tTykRBbV/9JHjf5FpzIn4CMKHEpZ7mZ3/jD/eXcSjOH2MFG+VxlYZmjzTKL/FiY4ZgjhVJxPB04bL//OF7SS9qcGWZ5eOtGui3n2sTUG2vJ9M31HAvFgi3dQ==
*/