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
1qXWBxB5T9Sq0NwPY4CC5FVGuCce104NbXtMddDawwL84VuWfIh8gM51jD2YthnNUY2tRZZVpudiIr/++APScmPxKuwbWwx8cvvjxeuKB3S7lSgOVaP2ImsbF2s4lh5PHg6xs0ZgvL3o62eXdGZ8aCfk35tvYWwor3Pyr9DP/qeYUKSEgGJzajcmjtB4lWKjSYQZ/Voerpr5U9V8P6ZiN+4rGJ76FevTDQr//r8aZqzrH1Pw90DBgGiabEnNrXSFUNAQ6WdNxQ2LrTV+/uKh3LvsLFzC1RPxHP9Gkl5CaG1ONyLzJz3PucZT+YKEIEwUdn4HWUzp46QZh0T5WM5yDI+loect1cV9FLXijOeQe1tymp+NwVONqPccH+qT0z0qMWVaRcLrIihK2MsgGwN5g4K0GPhBVd8VQu5aVMHkNLLLBCBKX4qRC9c9g09RTujxAXlH4yzf/dgC5n3EI8Iw9Hf+huUSYRPWzxP6jAXK1AfNMR5TEGe24yyzKTs6YXFungFt3p8MfJ19vG6100vooojKWy/6Ovlo8n6WeboqVSvQzDZTexNGhlVrLQ==
*/