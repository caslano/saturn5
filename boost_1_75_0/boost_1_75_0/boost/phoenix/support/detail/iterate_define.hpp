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
HT/cQZs4ZDHdm7wzVeQ+2JUr4DR9OdnZXInrjSKqnvagZu3nJ3GQpvfKgZmA9g9/ywbeWHPSEqxqlQTTuButNGxpjkt7NUFcX3SdA7imTEpkhCMMcoL8u8jaiKKfAqRh1ToX37Nk/x32CucHNQ04vkPIvRlJU73OhyK2HxPf2QZ2wnehkOAN07x+BgKZu0wtrHIYuVKg7Oh5SM6uh+RbwVgVCNAJhTwNQITN74NzHiezzUcEzgPk/EodU2YThKwnNfdRYU54R3QL4OaAf/gb1oSH/zWxH6ws6SUulsH83dBv9SmgkmAHWv+ZfIZCORhIukW8nJSyTXHceR/emRNin5OKJVxPnSI9HnWMJnbe/zRXN061QVVe4uBFoY5Wg0QlGTozdsoEbnTEBmrmj07QhEuF/LSR0EOA2yiwSSl/42hYiI00ehohEmKT47EvbWfa1ID4nlOWXRhR+wAVcl77QguRX1DZ8jeoFJ2i4x2JRAYbYQj12k6UN8aczktDJ6J7puYkW6n6Bc0kZu5tfw41DGL/Bre6iqzn7RqCIEYg6+TAwhNr5Y998mmYVL7Aoo32+fWwFZ8igy7ukORPfv2GqpMMmpm7MJz3C8rqooCQvBC088Cn+kppddyr4Pg50wAh3MUjWq21PQjW9ORAfZdz9RW0BuC32yuvw6mTksLWOwB7uesJf7wUHxkQKEQQlnSeRBrrKBAUJpGJ5Bqu
*/