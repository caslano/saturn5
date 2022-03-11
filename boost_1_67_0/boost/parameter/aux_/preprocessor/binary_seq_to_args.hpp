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