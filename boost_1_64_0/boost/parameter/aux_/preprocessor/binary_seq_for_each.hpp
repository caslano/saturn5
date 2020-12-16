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
J22Iu+JRNxM/LMY5PmMdadJKVQ1Th67mpa7cRTXtm47bepDVepKW5zkudUJSvPt+pcQMiZ0qx3+s6i9p1IW8nabOB1blQtoW51qJK5hOsPGTavxphxEvVPXXNu6neqllVbA8t5K2+37Mh3+repaUYYo7dl7qVIbzpZydr+wy07yh5mtlxCTvqqYJs273eIpF/TjXYlhGKZn/mJrmrGMeafyoV+D7yz3aaruD9kbsqm3TUFOaoaY0I4zyHsy+ySEUPzIpdULskOSBQ0fGJ6Yasf5uqvzF6G9r1VUeC5vSK2xKzx0rNYlCkHY8/kKsVGM4bTaq4s8Yd5fyd8eEVb8ijW3e+nHVdptlDMQ3VX7yGu28nFD94Xoww6qyn3TSKvGzbPZ927GqPV21F8ov5KXGflVXLTOIcqWffw1U/X76I2x/V2ks5Cq7n7rOX9O54hNeIf8Pq2nifagRaG531VjOu2rfXKY31Wi7SJbzRkZ56ZdV/U+JR6zyU1TPrKNbX81XmSUyj7GOI1zrqNbvI8b5kWJJvRRxCQoZ7RvtUfkpKfcHbFmVTiF9mLaY8iKmInk+oKY5avfnl30F1mYtbedfsu0w1UUdmDB8aKIRy7OESiOatQ6TYUTJV8PKs86F1HwL1VlnXLKxbWW7S3tQKuBvZgzxMNyk5j+m+3G22UM5HMbMtqAy8vctNV8/MMXgJMrukOHj1ZnTdC/wrZq2lJGvuirdWsxXKKNdANb37BS1LIe5TYJUlY57f9g+zTXNB7oPkagzj9Oeqsx9jG10XKWTYNSjflSNz2+0319f9W+gNEOI2XAucxvI8V2RlEJUvOfr5CljO12zV9fOs8QSDDfyNjJJTiMq9qNssxVq+sv6RK0ce9I8lmrs26PiTPv1E2r901n714wYodvVsAAV4/cgJ64tIczFCgUUSrvgiuv7CPeGrmvY2wzb59H2WQL9SaYYvx3odvLvaujq3gllPrmfLOabvZiarjqt7z7utU6rXJPknlKuBXKfab73dMfw92GY+9yrhoca1zTT+ZLhhY10vZ3zgjlnSTxeOY+RHucqGWY6hzGt2s/Z9402IWlzQG0vtWzztpQ2bA6qfYFvbAtl9JeenrWNmnHSX036j3qMLzDD3QaOar8u8zduwXvboFnHThw1y6i/bdxZm++NjPOhmq60FmT9m4V0PGPuU66meLp11fiHzG2MGMdoRzWu5AN/A1vcaxn3Ia2lPd50f/ZF/BTns+A09/rJDdaEVLa1x/MtztXse79T0x71byz3JZtU/xv+8VwFvmTNx9gqEqOhonbRUVGrS4tmL/kGaV38grRn6c74Fdce8Q/SnqazKB/yYX0PU07K95Qa38i/FkfmKNo6eI/oNRf1n+yXiMpezXnLZnlPJ2mqc6CPxGIeGxerUjbFRn5BTXfYP3Nbrlb933At3GVsgzvz5bmQ6ifNBfTzxbxNa2G3ureRZRvxmI37JonL+wcpO6t7Fua1/s0q+XOoZT/Lek0z9p/qszPaPbC4X7FILyk+fgTHmqzb52r8dWdJyraHNoB6lMHOzHSbq2VFW923kK7X52nGvdWXKl/j/H5hbwzXt9lvOQK1Vs4jenm/plpNuV6dVNMs9wsjAtB2W6DW2f6qdsJnsT7FeUpL8Q3UdtOF+ZXXEv1KeLZZYZTJX1Uavs4i3Mdl3tekq2FptOtXhGcJwazbR771/eoYx5g5zn19tZ5xxjW7sOovxt2Qw3hWUE+lV8AWo03SZRmS97zOSiyjPcsYq/V3/Orw5bhjHmP8U34ttDr6720hxFTYSZy4znolZy1trPOslsRxstm3hObwq6+192vmui9SsY0z5lvvV1ePznIPFyE=
*/