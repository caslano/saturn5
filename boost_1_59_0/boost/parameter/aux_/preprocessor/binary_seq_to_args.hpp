// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_BINARY_SEQ_TO_ARGS_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_BINARY_SEQ_TO_ARGS_HPP

#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_0_1(n, prefix_seq)          \
    BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(0, prefix_seq), n) const&
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_1_1(n, prefix_seq)          \
    BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(0, prefix_seq), n)&
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_0_2(n, prefix_seq)          \
    BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_0_1(n, prefix_seq)              \
    BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(1, prefix_seq), n)
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_1_2(n, prefix_seq)          \
    BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_1_1(n, prefix_seq)              \
    BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(1, prefix_seq), n)
/**/

#include <boost/preprocessor/seq/size.hpp>

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_0(prefix_seq)               \
    BOOST_PP_CAT(                                                            \
        BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_0_                          \
      , BOOST_PP_SEQ_SIZE(prefix_seq)                                        \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_1(prefix_seq)               \
    BOOST_PP_CAT(                                                            \
        BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_1_                          \
      , BOOST_PP_SEQ_SIZE(prefix_seq)                                        \
    )
/**/

#include <boost/parameter/aux_/preprocessor/convert_binary_seq.hpp>

// This macro converts the specified Boost.Preprocessor sequence of 1s and 0s
// into a formal function parameter list.
//
// Example:
// BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARGS((1)(0)(1)(0), (P)(p))
// expands to
// P0 & p0, P1 const& p1, P2 & p2, P3 const& p3
#define BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARGS(binary_seq, prefix_seq)    \
    BOOST_PARAMETER_AUX_PP_CONVERT_BINARY_SEQ(                               \
        binary_seq                                                           \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_0(prefix_seq)               \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARG_1(prefix_seq)               \
      , prefix_seq                                                           \
    )
/**/

#endif  // include guard


/* binary_seq_to_args.hpp
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
*/