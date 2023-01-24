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
yQ855rGWRM2GEFHxjDMbkQ9kNyCVMBTh3ZDshHDPbr3N+Pmpi7Nwi9p5nZEiUsyWhuUZSyeyLo2dBRldALt9j921h5jHuzfXnZeSYR23CG5c4WtjfwqnDV87gVLr9wni5m68B+0CGxow8caXKJkb5b6mDRrWtkURAeOCohnsaPEwWwb/wT/nct+KRj+QNv+E763aFM4M47EHX1CcoNuDSU7QMO0o0N097Tc720qABaIrq215oaFcKn8Bt3tk4cRPnA+fRdKFG1T3w9HeKH5yjB6vLW9oKHDVsJSSokdEJb5uBX9tUTGVF/4tew9SftXIrzHUEBW4f/Y1bHF0Opqp7s0To84h/jigTXmx0Zhniurkl7m1dClw9CEhg7R9plq/wQCNyURwaZMtHbdjNSqTwuMmPDDOdMt8dfTnQru+lD3xZeGgZW63vxKH87fmP0ukZJyxQ0Xn4+64sd6mFE3km/KtRxDi4pyqOJLYHQ3+Z6Tm5clWhyG326lCbgvH0pqqmhhi6jARsoYwbw1bsXLNGiLbFXF69gKvAPvWlTMJfffK84Hm86qql/EFyhV7iuT25E/teU0E40GssU5ZonLpPzAmZtA4k/ThaJ8PG1Tu/CsifxHiDBdwou/iThfGaAX+xVhq+OkM/IVX1UUby3I5d8rWXUWQ+im6/GbyoDMOsP5xyh7ryLVoJJGvHyPeZ5TLaJFofhGV1dijTPf6
*/