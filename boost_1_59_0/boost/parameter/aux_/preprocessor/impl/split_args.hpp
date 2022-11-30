// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_SPLIT_ARGS_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_SPLIT_ARGS_HPP

#include <boost/preprocessor/tuple/elem.hpp>

// Accessor macros for the split_args tuple.
#define BOOST_PARAMETER_SPLIT_ARG_REQ_COUNT(x) BOOST_PP_TUPLE_ELEM(4, 0, x)
#define BOOST_PARAMETER_SPLIT_ARG_REQ_SEQ(x) BOOST_PP_TUPLE_ELEM(4, 1, x)
#define BOOST_PARAMETER_SPLIT_ARG_OPT_COUNT(x) BOOST_PP_TUPLE_ELEM(4, 2, x)
#define BOOST_PARAMETER_SPLIT_ARG_OPT_SEQ(x) BOOST_PP_TUPLE_ELEM(4, 3, x)

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/seq/push_back.hpp>

// Helper macros for BOOST_PARAMETER_FUNCTION_SPLIT_ARGS.
#define BOOST_PARAMETER_FUNCTION_SPLIT_ARG_required(s_a, arg)                \
    (                                                                        \
        BOOST_PP_INC(BOOST_PARAMETER_SPLIT_ARG_REQ_COUNT(s_a))               \
      , BOOST_PP_SEQ_PUSH_BACK(BOOST_PARAMETER_SPLIT_ARG_REQ_SEQ(s_a), arg)  \
      , BOOST_PARAMETER_SPLIT_ARG_OPT_COUNT(s_a)                             \
      , BOOST_PARAMETER_SPLIT_ARG_OPT_SEQ(s_a)                               \
    )
/**/

#define BOOST_PARAMETER_FUNCTION_SPLIT_ARG_deduced_required(split_args, arg) \
    BOOST_PARAMETER_FUNCTION_SPLIT_ARG_required(split_args, arg)
/**/

#define BOOST_PARAMETER_FUNCTION_SPLIT_ARG_optional(s_a, arg)                \
    (                                                                        \
        BOOST_PARAMETER_SPLIT_ARG_REQ_COUNT(s_a)                             \
      , BOOST_PARAMETER_SPLIT_ARG_REQ_SEQ(s_a)                               \
      , BOOST_PP_INC(BOOST_PARAMETER_SPLIT_ARG_OPT_COUNT(s_a))               \
      , BOOST_PP_SEQ_PUSH_BACK(BOOST_PARAMETER_SPLIT_ARG_OPT_SEQ(s_a), arg)  \
    )
/**/

#define BOOST_PARAMETER_FUNCTION_SPLIT_ARG_deduced_optional(split_args, arg) \
    BOOST_PARAMETER_FUNCTION_SPLIT_ARG_optional(split_args, arg)
/**/

#include <boost/parameter/aux_/preprocessor/impl/argument_specs.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_FUNCTION_SPLIT_ARG(s, split_args, arg)               \
    BOOST_PP_CAT(                                                            \
        BOOST_PARAMETER_FUNCTION_SPLIT_ARG_                                  \
      , BOOST_PARAMETER_FN_ARG_QUALIFIER(arg)                                \
    )(split_args, arg)
/**/

#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/seq/seq.hpp>

// Expands from the flattened BOOST_PARAMETER_FUNCTION et. al. arg sequence to
// the tuple (required_count, required_args, optional_count, optional_args).
#define BOOST_PARAMETER_FUNCTION_SPLIT_ARGS(args)                            \
    BOOST_PP_SEQ_FOLD_LEFT(                                                  \
        BOOST_PARAMETER_FUNCTION_SPLIT_ARG                                   \
      , (0, BOOST_PP_SEQ_NIL, 0, BOOST_PP_SEQ_NIL)                           \
      , args                                                                 \
    )
/**/

#endif  // include guard


/* split_args.hpp
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
*/