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
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
*/