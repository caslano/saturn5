// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_BINARY_SEQ_FOR_EACH_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_BINARY_SEQ_FOR_EACH_HPP

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_0(macro, data)
/**/

#include <boost/parameter/aux_/preprocessor/for_each_pred.hpp>
#include <boost/parameter/aux_/preprocessor/binary_seq_for_each_inc.hpp>
#include <boost/preprocessor/repetition/for.hpp>

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_1(macro, data) \
    BOOST_PP_FOR( \
        (data)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_2 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_1_N \
      , macro \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_2(macro, data) \
    BOOST_PP_FOR( \
        (data)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_3 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_1_N \
      , macro \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_3(macro, data) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_4 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_1_N \
      , macro \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_4(macro, data) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_5 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_1_N \
      , macro \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_5(macro, data) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_6 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_1_N \
      , macro \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_6(macro, data) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_7 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_1_N \
      , macro \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_7(macro, data) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_8 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_1_N \
      , macro \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_8(macro, data) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_9 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_2_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_9 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_2_N \
      , macro \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_9(macro, data) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_10 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_3_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_10 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_3_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_10 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_3_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_10 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_3_N \
      , macro \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_10(macro, data) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_11 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_4_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_11 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_4_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_11 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_4_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_11 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_4_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_11 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_4_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_11 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_4_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_11 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_4_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_11 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_4_N \
      , macro \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_11(macro, data) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_12 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_5_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_12 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_5_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_12 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_5_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_12 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_5_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_12 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_5_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_12 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_5_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_12 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_5_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_12 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_5_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_12 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_5_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_12 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_5_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_12 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_5_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_12 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_5_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_12 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_5_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_12 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_5_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_12 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_5_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_12 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_5_N \
      , macro \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_12(macro, data) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_13 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_6_N \
      , macro \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_13(macro, data) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_14 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_7_N \
      , macro \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_14(macro, data) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(0)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(1)(0)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(0)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(1)(1)(0)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(0)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(1)(0)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(0)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(0)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(0)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(0)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(0)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(0)(1)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(0)(1)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(0)(1)(1)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    ) \
    BOOST_PP_FOR( \
        (data)(1)(1)(1)(1)(1)(1)(1)(0)(0)(0)(0)(0)(0)(0) \
      , BOOST_PARAMETER_AUX_PP_FOR_EACH_PRED_15 \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_INC_8_N \
      , macro \
    )
/**/

#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH(n, seq) \
    BOOST_PP_CAT(BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_, n)( \
        BOOST_PP_SEQ_ELEM(0, seq), BOOST_PP_SEQ_ELEM(1, seq) \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_Z(z, n, seq) \
    BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH(n, seq)
/**/

#endif  // include guard


/* binary_seq_for_each.hpp
OT6mZMGZ3+gw7BHtddoQpYOQ4nKN178B7Zzz2aw3sPFhT6fyOPub2U64mSNS+5cPV24b/OdS2G30HOCf+ILMs/3p4HyWAyG1ElbE7z1/+pT9AqzKo+QjlL5LotewjVRsgP58mvxl27PbIESKNxfaXbsWiK4007/ZbgN7QnJ5YH0cKV/eQQVC2oZgK+cMSZvS+5VRUKsmCJ1I7Hu8IFOkrDRUJdw+v5bUfz/aW8IuGEiTTyhkz41EmU9JmqIvNox0GRvvvHkqQBcIyQc+9piVlrkmX2ixIqZ3THJfbt4wvfiC2QPeZT6SX6bef/IkUpxqYQyndSCfnSt8+fdM9E5d1rkqZ8CR/pBYjmjtWs/qqdXfdQlmaL3atDEidWi8jLqSOTBpfkRpck+SL9gk7zKXOQ/z/fxmQvPuxt2d6sA3OQ7ccA74F6qzq0O84vx0bBzbMvRSyxSWUr/t7bS7IbM25752uMGssamYkyrDlsbvZuz5yODUJ1du1AUDWPIECxIT7uGs8SlhcgDFf65gOqdfZrFuZF1hL9VIOtqDl5cxTqatx5sdO89Runw1qBxmzS1z61fAwO1EakWsFaaR3JPch5r58Tn+MtlyVmejtT8dOD1SInFT0pN96mQp0YdG7mG+msTHxvxfKS9fRhXVX99n9yp61lETFlXNatyAzW+1w3uOs5N0hXHR5H/jTVVrOBkphGpq8cbJDzlvdhRngSP13B5oOfHH/W+Txw7VF5hmfgnKgI/BEWtVBq3fT9hp4iivh1UwZvNfS8rntd6rXyamDl95EVUx8kXodZoJ/bHh6jvHNldQz2XPuc+LmUc1T7Hv2b2NUgWmWU2xMDp5OROr6WBFCnl6JgH0cuVEC8q481yzf4qINHnOSBgUcxG6qbarR9TMFN9dj6hfZX1Qt/hCiN/hIMRwDAvqel/MB9hl3JYzlrzORvBNjoNVAWGf2aB63YG6hQeuFRzRt5bQ+8s2fgB+KYKWvh7ZO22proorshDFlvHlsCdVG/q8I23Xpg4ijs+Fzz2ymzlPd+CcLmINZuM9mhzTkHH3Ly8hiE2VT8GaQnLqmqQaSSHW5DfEanrpcQlTrc/dzxTz4cb7NbXfOpo6oWTJiV33DtHLQgcuwQldg743USM7dPrOq/a1BZSm4U2llI/PkyU3bPBlrk/MN9JJmytIriyl3cyDGjDTuFIi4WI3oNCDzrfyQW2ft+vYHaGbzFdotoWufR0niw+Oc+keEI/LyTX/+Zq1jcRK92+v61tBe3qxMpFonWV8ThrKo9ZVRguEiKfYpEI62jTGrsdabVLCe8URXBNyMopwtdOe/x3apSdC2dxhhxPcfXo+frstB58Z37bVJC0j39AbuR0YYzqMTlCerKaquDjFi+XJKdcDvztiQ/o13FuKUwZXw87yysYcn4zqRm3Kw1LAPtOfN8yvriThyd+oJ+w97KjIgVMObskUr/tBXGGIrRaBLuQyX70zeUP4dv0ZIO91F+Uab9Qpb2bthDBkfJrWeVwxzNYAbnflnUwrKZxhQqAkVVm8qDmDt0YQNmzwxuAd0wV+tVtNmFm6W5+ozyyUMRjWaXeXNzkpeMTjmOuO4/kIFcEBLPbPlNV0ze/ru2R8IvnYM3VhIo8mpRaU7PFvCQHXC6FIIsjY4mQUJdGfQKhDRaUwvbAQSEV6KPD9q/6nCvsK8dbEA76TdQvHKKXTmweKBojHE1udv4YnyFtFXW/xINs8fC3hqcBi/8Uyc0++GXNQmFM/vthxBs9anYKEv/HfeXn0HBkJ23Uv5oeAE9ny4UNGwkyxUs/A9YNV1n1BJ0INVDMORBSHEPnWdp7oPG567yhklKaYeAWatoDubpr9aqttJ0MXXnEdXT39vcn976UDaoY/oYvw+JOXLLJIv62NS3kniyRpmSKECvzNYNm5xbWHloftvVvwgQWnp1NBSt+7ZMGeVAcaI118W/9xlEVvyehfuNIn6qG0l/NoK2P75vGP5R7XPLa8in/Af4HbzSDzC8YxyQfC9c7o29T+bY3AhM8Oz3tfS5tRSU9DFMfpPWtYsuIbFET4m5MgXV4mQuXcw0WU/GKhymVaCVl0WRQjTw7QMgtYp2aFsN6WPxdrMJkSWNYL/Y4FkIc0T1daejC6TZd7qPHFeaiws31BEXkzIvy2wG7IfV2oNGqqhdKKRCH+1mi7nH1iJ893+5PQioDU1cKd6dFs9OTg2Xe+Y33L52nujclnUt2Nv80OchZdUihELT6jIcVVK4bhJMJi+KcYu2Iw6Wzmqt+/lj4Z3wL0Me0NpL2tSDWQrMN6XtaiZTcRPQCZ69xwB+z6/Lpc3IS6K2x7dxNhvtJWltUU/BM53XYyakYjusozZcGT9+dK7/b7XPGddMHJhJw9aUneLLeVBNGZDl+I/MJTlK4lfz2jnd7owUFBbih+C/W6Ctv7u3MRGVkSct0I+kr+xBliU0JU8BTJGLCK/oSpR0ze6qpQQh2bdLXT2GpXP1m7htzo1C5TSlPV8yX+OOwB2UraT/Ovme05LRbFfHtiRVUVUJaM6k5+DUK44+oTSFIZAIMXtf2keeCK2RKFd6f5O6PELRKYqwvuG5mL2NXhagfBiakzjy7By25YHxWWEGFF6TnosMsuOjuRr2khJyKIUJW8JJcJIu4d1F64PVBDOUp9X+6Ft5iRHJBIaDzBuNT3F4NhPPPR77jedJyZGUklg73BQxOQX4q+jrVyVkgwPQrmdSlj5THQtttpb1SzoHjF9vzrYw5DruuXQkCC4GOeOAOrOp4OeRZPwpTEfv2AXXWxuhZbTpPiWdnlAvGZsnN0uxwwwsxasilhvLHxJnuw5xv8IfxN0pv9pfs3/ajl3ZMXl95w7N34B6EDd3Q8Ol9DowIe1+8aDZgY38LVDS7bpqBYHttjlzMu8Oy4ExqmjtTN/2pK2HEY25epj5eh14bg3ubXQdqpR7EkXC0cziQpmzMJ/nEm7Y3pe/SrKlZBYbcJAINbpfOq5hNOrR9Yb3paHpY9yLuCbI8JzNAWzUk7VjFPuOZ5jHWZ9QSAY/9tGGSTGBFI8y4y9//jtXNSEF/AjhZ1nNVsHK45j/kvS5o52Sa8hQR00fmvkCrtLZvCcezGl+J3HH2e/PrsR/t3QCmLIVuCx+tfY0h1xyVCQicCqbyiYDLjGziFs/8ytJYx0rv/06qyFuDpCvKVyDcVV24OjN2u0FvMne8cyNL2FweMWAbSGrH/0TAmWv7PkOPGwjl6d4ipn0ktnbISV9XCw3F5OEe0xcb0kr67NMnjocuxvWHZ/cqLOAYGfJiyoDEOvVU1PHsv4YXCp7c/RDhb62GtoW0dks6Ta0VdVjzsuhjKgUr3n0fVxgTeSXSIQfeJ9z3a2+iHk4/sGYSKvwlZ5bPrG/ZuQLeiqDLHgue/36aOGU9czOqYF4h04xMU+DhrUk02gxq0Iuu/2bJo9c9XKV2SeX+azdAeJWWy3aAaFTUwGXZM2rjJIefBk8RjU0PqUog+1qRifEHmjO6xzEPHWxJ9od4yQhXsZQEXzheWBVCZh3Rq/qDdM1/ggQkkZOrq2NLLLb/2V+uo4ofkDnZDy4kxDQyoGsETEo/O05w+odqqXHAlHjPTbyzMWYU3U9zR2C+5jfIY/8vwzeDcABQs69PAIvOdgE4FlVY4kXzEObDiykyWpcsGiBs8bVLwBlSxbmj+I6iXDZzV06i7OHBh87BemCQ0n25KBTVuXoeudeS/WLBT+JsXZckZncU2k8mbvbvTmjildAzNIulCLAffER5vQLUxAGvQYUsSnUnwTm4JxyXoiuSKPev+zvyciDc8fgDZvX3xVJhDQw6ktku87mz1gdK7hX9H9QHvjt6ezkXc4j7VK5asqBcUbq3W7R3RF6tlWYGZdqdsxe6MqQaU4ePgigH1EompaVWTPwdxG/is/jysMh2cqDzBc9Gy4qvDnjnPg+MzCWuUVSo2U3Ykk46JHgITgraEW0JLiZCiOOHEvCp9FJUsNJo+MqqiQSTpF9jMxcsz98Rp2R+qS9nn1s+9HxTePC62JA5GhD8bcsLGU8tpX6RbV3xfkA6G4ffGNUdiKIfQ5lRVJnG7XU0p5U9QnsRdYj5tyGoTtBCrppbcLP9uvNhcyGBpNY3Hs10JoZeUrNxfPrJc3oZ8DvjYDrvOJbwl1MyqcYbGKYTHybDm8Ri1HPnm/SMSdE+ys2yV2RS84rno/fsM3ph6EXjq7utedTr5wGNWS7Al2Lp1vuV9Dakta8CfWdP/vvSs9Tv2oHF49ovEF/KXcUsujXyAgWC2vjYDtTphJTIS9PKOnwT2ciyC8xdv4KncWesNtmWgVcbwUh80v8lo3rbVjczf4vQ5sdMI7QT23NxkHqpSV0FfwdiRK2fqvP+eKlIXv3ei9cqqVRUsYz5woEM7RbjLsherzW13PoQ8eDKOGJT1kJY2qvRmvsH3u0NyEPd3H7DKwK/7Q+84e8oXvUhjIbMU/ZRFo+BGcumGBAxD6rZW/D84ZQi8u+cAKquCUn7LJBNQD1hGMW2EHy6IuC9VlKUNyS0WGrS72kf6sUgKqdstS/TUXdloIzowWWpgSFWwznBERnINal9dDR5RNHCuTkbT0qbMWWvOx6zarTyj5rJjBtAM9Cl4RybO92DzeMKkSHbibRHYkNGMg5mHxiAVqyx6B8G5oBRLLCdolUNj20hCl6Tlptf/NQdbq7r0RDopsVe8Nt15sJ+8J6gHs+1ccXrhTIbKgXkD8Ajdattnl06gHuLIfSgnFPVvy48wmauS16k+v7+/wYpBQcB/QPyA/AH1A/oHzA/YH3A/4H8g/ED8gfQD+QfKD9QfaD/Qf2D8wPyB9QP7x68fOD9wf+D9wP9B8IPwB9GP3z+If5D8IP3x58ffH2Q/yH9Q/KD8QfWD+gfND9ofdD/ofzD8YPzB9IP5B8sP1h9sP9h/cPzg/MH1g/sHzw/eH3w/+H8I/BD8IfRD+IfID9EfYj/Ef/z3Q+KH5A+pH9I/ZH7I/pD7If9D4YfiD6Ufyj9Ufqj+UPuh/kPjh+YPrR/aP3R+6P7Q+6H/498Pgx+GP4x+GP8w+WH6w+yH+Q+LH5Y/rH5Y/7D5YfvD7of9D4cfjj+cfjj/cPnh+sPth/sPjx+eP7x+eP/w+eH34/97b6lSZ6F0vbenvFgXeDUpTtJ+EBVrKytG3LEjXRSDagyUHNl/0/XVv7GiD8ntm5atubT87Ri7u8wXpEkLIsMCs9HFok7a4fwUWeRYsVeJZinagNFc+72CnYL1Vg3nrJagE2Ic/c+LVfoSapm+wzqon1LtyPmFgi82t/QrbrvVHINtDO+ztxS8KniJUaqBetV3tSb7ySB85Y9NpKldNJ1zcjWcCgseo4/4VCYRtsSzUH/5/hT1xyZ/skNP4KkknJGrtDdLanJ7fUkRIomI6tw2k9fF97d7w2up94INYvI2Dk3zFOeFtoMuRy7+6qXYUuAX9VXk9EgrgkD3x5WZa5dnXzIVf15Dcd0WiS3AFcbmuOt5DnDB/jT8EvuJ7INf1pjwLV44GfmHHnsKoexlUz3zmCYfrWREcgmmOH8OGdenw0HDHWRCssIkIIHeP0sjKGu1zEYNuWLYX3t54XgmRaKRRZNPZlm77NVb/j7WvOCfKhAlrbSTL6OAFG2tFR5/RqE9+3MwEWd1xweh8oKO4n3PBO+k6Kvo+iDqnS3s/Uv5Ed2YvX55FtZLkhxdBoLjIsu1LzhEJVb8HhIP7Jm/bVff/FSO9HTjuVpTHS+CJ6dIZt7E/D6PDcnClUUDOzHrWDDo6tDhaInrjNBl2M1wgGFe8O8kg3HLUfJIPAica1Mmfhb9+7Os/94WpJ7Tki0EG/JldJGjHmfhciFsnPMqi0tCk7yR+PKC7J8Pc4JSPuJDB1OAI9TFYzrXP0zUZHOkTSf7/5wguyuRZCGwC95/54QXvY0N0BDNn3xYcGSCLHpFbZYyA7Mk85JUz+Y2R4WMAQ6InnfCEhKf818LYxY6jbheuPT/WFjocG2jyXrekU0kqTfmqkpcTD0Ra//xZ5+xBTleSdJTJAghHgrQIKJ1mCeoOonKueb5P+BrdPLkwC3zwP7nPdhxTulDeXNgV9nvo5cD9wduDkLD+PDt8r922xsNejYUTVt/kulZ9AzzSSsTPk0FjX5n2C3xJZvR0Rz7LIqyCe69aHXx+9/7buGdUbo+bk0OC8L1gOV5PLjqnBAezRjptavLW9m4c/PDZ0GM6dtlPxzZ8Y6Y5XgWPUpJ86istUqCpafz+nVXaimXJQsp5lllBfyRZYSMf/iq3pws/Zj22L7cB2Qu86S2+C2oBaXsKHZkk9dxOAckkd93a+7UnVdfbgyzPt9cXeoeGRZFw5mU98nnklhNrZpqlxUxwWjrpS6LUMRXhwTNgotqlo+Rb2q81LE78QJAWzHJxEzjycEjXI9zp00vg6HaBI30Sp6F8LyMRcQ3Zwb8ZWXPGm8EipzR0XMnuyHh9BrHJ05TVEG97AMS1ieaxBEyaS+FpOUNLSisyQPsu8KPEB8t378YJ9DfpbkMZbgL8Fy/6/NGEtUK088dVKdyw5a4wioZb8LY1X2M/esloqv+hhJeQ2KrKtuW0x9AvyDnrIxYjMzbrFaVdC7GlyAbt0SuqOQtGxHN8t+sF2QdhV2lT9kcw3ZKG8RjUuuIb6B8bkqoD1te4bE3lf7DzPS8BIIqvwP7uY90hP6MSpZY+dh0/168Y3kWf8n1eZYYJQrLc0DBWQDZX0Ze8nekg8i3WhSic+viwRNgJ2FfZTYzej1ybWQSfxVvk3QOqXeQZnoVZEXyshGr4pvMXMu7XJRVSD1U9yDjzcxBv7IO45OJnZ6/0faCyZ34Lr5fw5VvvVucEDIstIeheRwJszYhvlwYsTJ3YX/PmJ8MPsK6p3o8jbD+/IfZ8NX8pGF/2eii0pG/OUuoL1eL3e/5n6/ruM+/0CwMWZfSvH2O4uy1kVZddYDGlGZt3QU5necUG4rOgJ3dMOcthlXWyuQ+liv172esfsBWnkfgH10PM/LQ+gLOjW7twb8slI9ZqQNy1x1fHEb7UGVL71+u/H/rZwtkKbwDjRegIWGmKz67nk1nROvBx6xTtEcLMVQ1QcXJqEqTtXZuflnAsXZoilTVyAr/sQ0mBBbwKXWXS7BCibT4nQabty+qXxKdzC7PCI3WpUgTFZFDJaQcHuazh/p3GC0XkplQN5A7i2mYXzEQpYv2XMtUVc/QO1SkeYFqI1oY/8H4pvKsAqKW/eEe921B59bI9muv8nEyiMQgaTkRTIR56s3nRSMSkWaPz9xI5pPZwh/BUavP7FFk2PI2A38dow6gCn92zy6TSu0EqRJzFclOFmQ5dcNRwRxt321dWPYi77pvy4CwZ8K8uFFVevyvrIP5oUTtxqETtkB46rRr8h5FPFbQKot9Li19gqfE8Il5WEFnw5Q5vljz7659hkZ2ZdcShGXh49SbGbkdwsWHniz3xYedKdyHKZZX4gWpRjCGI/msXhRopC0q9CAlR1raS3uUDfvJ0e0Vmis200nw+7jMdTBpKNy81wPxyiewp3d6xLXcXbXPtms4tURwaySnXWaH+R0aPTC4F+puL39sscynkRpvAo3yFEPUPDQZZh7K
*/