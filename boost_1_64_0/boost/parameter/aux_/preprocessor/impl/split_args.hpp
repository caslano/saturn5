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
ZtV45Uaf+NkQi0kMUqCu9qrA9rKnoYfqKqL84pCRL8ZKzh0TeKBerCG/J4n6gP/HYRPN2xbzTK4pQe8rAltkW+wjELMZOWzRNLxsT6TN3OwJ33ajXlhdPDVbiiwTjLtt3Q6KQ20WJkR7j/opKifFIajJxvqEKIioG/dqRAqYCAECqA8/nXFpYRK5GBw/Sf+PLSdGJYA8rRqEl/MEyQX1QDu/ooMKUyTy5vFNd9LW9AWdR5QE5pK2CvkKnM68nw6kRPp5FR05ArkCii4NwYV/b0nXm8ZQujES6No4CHLNnYijBPQrQY6u98K/slHdMHnxQ+AdiHhjTX1rbrQJi/6HmB25/fweK/KwNJHhKb4J0SA0KPA0GkswMHMdnzWlYy+jKZ6uncOhzdznPjpd4bFb84G/qBCB1Ma3nQRH0d3KnMu0+4vdMQoyIq5IF3Wl5kKfMr2MrBUAMV9VWETdzX6NFzHMVnxWcFvzMwULFCVEJAtgJ2gWox4xWbjg8aZHMayLuQHiWk+cIrFIJOiZU3UPFnOG7S21SRlNAX8Ouk6tPfIXlmhiOlANq5E/Fw==
*/