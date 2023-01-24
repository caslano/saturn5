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
bqGa5JEVinl8NLKLONaaw6DmB+d8eQFsay03Szd9N/ZAGoQmyFM6Vcdx4o3pzrwZXlXCzzSS8SJnQ8RMyW95gMoYSH+5ls19R6QJ33EQpbgAulJfb2b+XM1Jw/bdoU2YW+mC/Mxnz/dfM4OdeXGTAl80h1A2QVpg2CEcPkKSjjTYkNhSx9WFIlQ7AVCxBYy+8IVCVJsd1Cv0hm/hzzfiCaXMvHyb/JD1u1z5oAOprBGttsEK4OjU4HeITD6H6FhRh8kAfF1LFHFmlBPCXahmcmLG2zKYw49tica3G6sGRRGfzcrAZjVXZqavt0EIvgtuGHRXrZ1S0e1jbV3UY2WB22pX5sEHNbmYJz3837FfGH9/kD/WMlGfSAxFBmw5DGcvwq0G81tra/ue2McIQ3bZwY6upwu27XUHfo7Xy9u+bSQ8J8vYyOSzrYWbZlT9tEKGyDlqlXonf4F52LpdAIqIfTvaOHtyeCDQv0sgvmOIUj3KQOjZIct83JirQv6EJ5ApdbcOdp5lQU4zMgoMNttttHt2ohVAmhoc6RDSrvuyKNNuD9m8WdN8FYolKuEg3KGwFqyn64WBO+uP/PVxB1Dex6Kk/bwYiae5UJoKi1xoxu5Tjwn9uS8T5d6BXQ/TlMelM0S9S4DOAZE/WGaYcPJXs68YU69TSEQpdd8OHw0sX2PmV/GtYUYeiX7ugLMP/PVQPObpPR5O1RPsK/gG
*/