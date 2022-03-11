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