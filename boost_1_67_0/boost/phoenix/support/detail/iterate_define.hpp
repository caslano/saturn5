/*==============================================================================
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !BOOST_PHOENIX_IS_ITERATING

#define BOOST_PHOENIX_typename_A(N)                                             \
    BOOST_PP_ENUM_PARAMS(N, typename A)                                         \
/**/

#define BOOST_PHOENIX_typename_A_void(N)                                        \
    BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(N, typename A, void)                    \
/**/

#define BOOST_PHOENIX_A(N)                                                      \
    BOOST_PP_ENUM_PARAMS(N, A)                                                  \
/**/

#define BOOST_PHOENIX_A_ref(N)                                                  \
    BOOST_PP_ENUM_BINARY_PARAMS(N, A, & BOOST_PP_INTERCEPT)                     \
/**/

#define BOOST_PHOENIX_A_const_ref(N)                                            \
    BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& BOOST_PP_INTERCEPT)                \
/**/

#define BOOST_PHOENIX_A_a(N)                                                    \
    BOOST_PP_ENUM_BINARY_PARAMS(N, A, a)                                        \
/**/

#define BOOST_PHOENIX_A_ref_a(N)                                                \
    BOOST_PP_ENUM_BINARY_PARAMS(N, A, & a)                                      \
/**/

#define BOOST_PHOENIX_A_const_ref_a(N)                                          \
    BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& a)                                 \
/**/

#define BOOST_PHOENIX_a(N)                                                      \
    BOOST_PP_ENUM_PARAMS(N, a)                                                  \
/**/

#else

#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

#define BOOST_PHOENIX_ITERATION                                                 \
    BOOST_PP_ITERATION()                                                        \
/**/

#define BOOST_PHOENIX_typename_A                                                \
    BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, typename A)                   \
/**/

#define BOOST_PHOENIX_typename_A_void                                           \
    BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PHOENIX_ITERATION, typename A, void)
/**/

#define BOOST_PHOENIX_A                                                          \
    BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, A)                             \
/**/

#define BOOST_PHOENIX_A_ref                                                      \
    BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PHOENIX_ITERATION, A, & BOOST_PP_INTERCEPT)\
/**/

#define BOOST_PHOENIX_A_const_ref                                                \
    BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PHOENIX_ITERATION, A, const& BOOST_PP_INTERCEPT)\
/**/

#define BOOST_PHOENIX_A_a                                                        \
    BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PHOENIX_ITERATION, A, a)                   \
/**/

#define BOOST_PHOENIX_A_ref_a                                                    \
    BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PHOENIX_ITERATION, A, & a)                 \
/**/

#define BOOST_PHOENIX_A_const_ref_a                                              \
    BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PHOENIX_ITERATION, A, const& a)            \
/**/

#define BOOST_PHOENIX_a                                                          \
    BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, a)                             \
/**/

    /////////////////////////////////////////////////////////////////////////////
    // Begin Perfect Forward argument permutation calculation
    /////////////////////////////////////////////////////////////////////////////
#define BOOST_PHOENIX_M0_R(_, N, __)                                            \
    (((A ## N)(&))((A ## N)(const&)))                                           \
/**/

#define BOOST_PHOENIX_M0                                                        \
    BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_M0_R, _)             \
/**/

#define BOOST_PHOENIX_M1_R_R(_, N, SEQ)                                         \
    BOOST_PP_SEQ_ELEM(N, SEQ)                                                   \
/**/

#define BOOST_PHOENIX_M1_R(R, __, ___, ELEM)                                    \
    (BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(ELEM), BOOST_PHOENIX_M1_R_R, ELEM))      \
/**/

#define BOOST_PHOENIX_M1(R, PRODUCT)                                            \
    ((BOOST_PP_SEQ_ENUM                                                         \
        (BOOST_PP_SEQ_FOR_EACH_I_R                                              \
            (R, BOOST_PHOENIX_M1_R, _, PRODUCT))))                              \
/**/

#define BOOST_PHOENIX_PERM_SEQ                                                  \
    BOOST_PP_SEQ_FOR_EACH_PRODUCT(BOOST_PHOENIX_M1, BOOST_PHOENIX_M0)           \
/**/
    ////////////////////////////////////////////////////////////////////////////
    // End
    ////////////////////////////////////////////////////////////////////////////

#define BOOST_PHOENIX_PERM_SIZE                                                 \
    BOOST_PP_SEQ_SIZE(BOOST_PHOENIX_PERM_SEQ)                                   \
/**/

#define BOOST_PHOENIX_M2(_, N, TUPLE)                                           \
    BOOST_PP_COMMA_IF(N) BOOST_PP_TUPLE_ELEM(BOOST_PHOENIX_ITERATION, N, TUPLE) \
/**/
    
#define BOOST_PHOENIX_M3(_, N, TUPLE)                                           \
    BOOST_PP_COMMA_IF(N) BOOST_PP_TUPLE_ELEM(BOOST_PHOENIX_ITERATION, N, TUPLE) a ## N\
/**/

#define BOOST_PHOENIX_PERM_ELEM(N)                                              \
    BOOST_PP_SEQ_ELEM(N, BOOST_PHOENIX_PERM_SEQ)                                \
/**/

#define BOOST_PHOENIX_PERM_A(N)                                                 \
    BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_M2, BOOST_PHOENIX_PERM_ELEM(N))\
/**/

#define BOOST_PHOENIX_PERM_A_a(N)                                               \
    BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_M3, BOOST_PHOENIX_PERM_ELEM(N))\
/**/

#endif

/* iterate_define.hpp
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
*/