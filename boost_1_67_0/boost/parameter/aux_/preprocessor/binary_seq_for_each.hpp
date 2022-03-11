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
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
*/