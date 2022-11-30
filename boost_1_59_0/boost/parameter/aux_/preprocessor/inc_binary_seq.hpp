// Copyright Cromwell D. Enage 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_INC_BINARY_SEQ_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_INC_BINARY_SEQ_HPP

#include <boost/preprocessor/seq/push_back.hpp>

// This macro keeps the rest of the sequence if carry == 0.
#define BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_0(seq, element) \
    (BOOST_PP_SEQ_PUSH_BACK(seq, element), 0)
/**/

#include <boost/preprocessor/control/iif.hpp>

// This macro updates the rest of the sequence if carry == 1.
#define BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_1(seq, element) \
    (BOOST_PP_SEQ_PUSH_BACK(seq, BOOST_PP_IIF(element, 0, 1)), element)
/**/

#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/cat.hpp>

// This macro maintains a tuple (seq, carry), where seq is the intermediate
// result and carry is a flag that will unset upon finding an element == 0.
#define BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_OP(s, result_tuple, element) \
    BOOST_PP_CAT( \
        BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_ \
      , BOOST_PP_TUPLE_ELEM(2, 1, result_tuple) \
    )(BOOST_PP_TUPLE_ELEM(2, 0, result_tuple), element)
/**/

// This macro keeps the sequence at its original length if carry == 0.
#define BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_IMPL_0(seq) seq
/**/

// This macro appends a zero to seq if carry == 1.
#define BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_IMPL_1(seq) \
    BOOST_PP_SEQ_PUSH_BACK(seq, 0)
/**/

// This macro takes in the tuple (seq, carry), with carry indicating whether
// or not seq originally contained all 1s.  If so, then seq now contains all
// 0s, and this macro pushes an extra 0 before expanding to the new sequence.
// Otherwise, this macro expands to seq as is.
#define BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_IMPL(seq_and_carry) \
    BOOST_PP_CAT( \
        BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_IMPL_ \
      , BOOST_PP_TUPLE_ELEM(2, 1, seq_and_carry) \
    )(BOOST_PP_TUPLE_ELEM(2, 0, seq_and_carry))
/**/

#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>

// This macro treats the specified sequence of 1s and 0s like a binary number
// in reverse and expands to a sequence representing the next value up.
// However, if the input sequence contains all 1s, then the output sequence
// will contain one more element but all 0s.
//
// Examples:
// seq = (1)(0)(1)(0) --> return (0)(1)(1)(0)
// seq = (1)(1)(1)(0) --> return (0)(0)(0)(1)
// seq = (1)(1)(1)(1) --> return (0)(0)(0)(0)(0)
#define BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ(seq) \
    BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_IMPL( \
        BOOST_PP_SEQ_FOLD_LEFT( \
            BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_OP \
          , (BOOST_PP_SEQ_NIL, 1) \
          , seq \
        ) \
    )
/**/

#endif  // include guard


/* inc_binary_seq.hpp
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
*/