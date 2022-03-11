// Copyright Daniel Wallin 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FOR_EACH_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FOR_EACH_HPP

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_head_aux2(x, y) (x, y), ~
#define BOOST_PARAMETER_AUX_PP_FOR_EACH_head_aux3(x, y, z) (x, y, z), ~
#define BOOST_PARAMETER_AUX_PP_FOR_EACH_head_aux4(x, y, z, u) (x, y, z, u), ~

#define                                                                      \
BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux_BOOST_PARAMETER_AUX_PP_FOR_EACH_END_S
/**/

#include <boost/preprocessor/detail/split.hpp>

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_SPLIT_FIRST(x)                  \
    BOOST_PP_SPLIT(0, x)
/**/

#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_head(n, x)                           \
    BOOST_PP_SPLIT(                                                          \
        0                                                                    \
      , BOOST_PP_CAT(BOOST_PARAMETER_AUX_PP_FOR_EACH_head_aux, n) x          \
    )
/**/

#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/logical/not.hpp>

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux_check(x)                    \
    BOOST_PP_NOT(BOOST_PP_IS_EMPTY(                                          \
        BOOST_PP_CAT(BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux_, x)           \
    )), ~
/**/

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux2(x, y)                      \
    BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux_check(x)
/**/

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux3(x, y, z)                   \
    BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux_check(x)
/**/

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux4(x, y, z, u)                \
    BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux_check(x)
/**/

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux0(n, x)                      \
    BOOST_PP_CAT(BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux, n) x
/**/

#include <boost/preprocessor/tuple/elem.hpp>

#if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_pred(r, state)                       \
    BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_SPLIT_FIRST(                        \
        BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux0(                           \
            BOOST_PP_TUPLE_ELEM(5, 3, state)                                 \
          , BOOST_PP_TUPLE_ELEM(5, 0, state)                                 \
        )                                                                    \
    )
/**/

#else   // !(BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC())

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_pred(r, state)                       \
    BOOST_PP_SPLIT(                                                          \
        0                                                                    \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_pred_aux0(                           \
            BOOST_PP_TUPLE_ELEM(5, 3, state)                                 \
          , BOOST_PP_TUPLE_ELEM(5, 0, state)                                 \
        )                                                                    \
    )
/**/

#endif  // BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_op(r, state)                         \
    (                                                                        \
        BOOST_PP_TUPLE_EAT(BOOST_PP_TUPLE_ELEM(5, 3, state))                 \
            BOOST_PP_TUPLE_ELEM(5, 0, state)                                 \
      , BOOST_PP_TUPLE_ELEM(5, 1, state)                                     \
      , BOOST_PP_TUPLE_ELEM(5, 2, state)                                     \
      , BOOST_PP_TUPLE_ELEM(5, 3, state)                                     \
      , BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(5, 4, state))                       \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_macro(r, state)                      \
    BOOST_PP_TUPLE_ELEM(5, 2, state)(                                        \
        r                                                                    \
      , BOOST_PP_TUPLE_ELEM(5, 4, state)                                     \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_head(                                \
            BOOST_PP_TUPLE_ELEM(5, 3, state)                                 \
          , BOOST_PP_TUPLE_ELEM(5, 0, state)                                 \
        )                                                                    \
      , BOOST_PP_TUPLE_ELEM(5, 1, state)                                     \
    )
/**/

#include <boost/preprocessor/punctuation/comma_if.hpp>

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_build_end_sentinel(z, n, text)       \
    BOOST_PP_COMMA_IF(n) BOOST_PARAMETER_AUX_PP_FOR_EACH_END_S
/**/

#include <boost/preprocessor/repetition/repeat.hpp>

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_build_end_sentinel_tuple(arity)      \
    (                                                                        \
        BOOST_PP_REPEAT(                                                     \
            arity, BOOST_PARAMETER_AUX_PP_FOR_EACH_build_end_sentinel, _     \
        )                                                                    \
    )
/**/

#include <boost/preprocessor/repetition/for.hpp>

#define BOOST_PARAMETER_AUX_PP_FOR_EACH_R(r, arity, list, data, macro)       \
    BOOST_PP_CAT(BOOST_PP_FOR_, r)(                                          \
        (list                                                                \
            BOOST_PARAMETER_AUX_PP_FOR_EACH_build_end_sentinel_tuple(arity)  \
          , data                                                             \
          , macro                                                            \
          , arity                                                            \
          , 0                                                                \
        )                                                                    \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_pred                                 \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_op                                   \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_macro                                \
    )
/**/

#include <boost/preprocessor/repetition/deduce_r.hpp>

#define BOOST_PARAMETER_AUX_PP_FOR_EACH(arity, list, data, macro)            \
    BOOST_PARAMETER_AUX_PP_FOR_EACH_R(                                       \
        BOOST_PP_DEDUCE_R(), arity, list, data, macro                        \
    )
/**/

#endif  // include guard


/* for_each.hpp
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
*/