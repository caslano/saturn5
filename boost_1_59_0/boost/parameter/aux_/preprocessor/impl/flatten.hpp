// Copyright Daniel Wallin 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FLATTEN_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FLATTEN_HPP

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT_required required,
#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT_optional optional,
#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT_deduced deduced,
#define BOOST_PARAMETER_AUX_PP_FLATTEN_IDENTITY(x) x
#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC0_DUMMY_ELEM(z, n, data) ~

#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT(sub)                            \
    BOOST_PP_CAT(BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT_, sub)
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AS_DEDUCED(x)                    \
    BOOST_PP_CAT(deduced_, x)
/**/

#include <boost/preprocessor/detail/split.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(sub)                        \
    BOOST_PP_SPLIT(0, BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT(sub))
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_ARGS(sub)                             \
    BOOST_PP_SPLIT(1, BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT(sub))
/**/

#include <boost/preprocessor/tuple/elem.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_ARITY_optional(arities)               \
    BOOST_PP_TUPLE_ELEM(3, 0, arities)
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_ARITY_required(arities)               \
    BOOST_PP_TUPLE_ELEM(3, 1, arities)
/**/

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/tuple/rem.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC0(r, n, elem, data)               \
    ((                                                                       \
        BOOST_PP_TUPLE_ELEM(3, 2, data)                                      \
      , BOOST_PP_TUPLE_REM(BOOST_PP_TUPLE_ELEM(3, 0, data)) elem             \
        BOOST_PP_ENUM_TRAILING(                                              \
            BOOST_PP_SUB(                                                    \
                BOOST_PP_TUPLE_ELEM(3, 1, data)                              \
              , BOOST_PP_TUPLE_ELEM(3, 0, data)                              \
            )                                                                \
          , BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC0_DUMMY_ELEM                  \
          , ~                                                                \
        )                                                                    \
    ))
/**/

#include <boost/parameter/aux_/preprocessor/impl/for_each.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AUX(                             \
    r, arity, max_arity, spec, xform                                         \
)                                                                            \
    BOOST_PARAMETER_AUX_PP_FOR_EACH_R(                                       \
        r                                                                    \
      , arity                                                                \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_ARGS(spec)                            \
      , (                                                                    \
            arity                                                            \
          , max_arity                                                        \
          , xform(BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(spec))            \
        )                                                                    \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC0                                 \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_optional(r, arities, spec)       \
    BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AUX(                                 \
        r                                                                    \
      , BOOST_PP_CAT(                                                        \
            BOOST_PARAMETER_AUX_PP_FLATTEN_ARITY_                            \
          , BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(spec)                   \
        )(arities)                                                           \
      , BOOST_PP_TUPLE_ELEM(3, 2, arities)                                   \
      , spec                                                                 \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_IDENTITY                              \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_required(r, arities, spec)       \
    BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_optional(r, arities, spec)
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_deduced_M(r, arities, n, spec)   \
    BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AUX(                                 \
        r                                                                    \
      , BOOST_PP_CAT(                                                        \
            BOOST_PARAMETER_AUX_PP_FLATTEN_ARITY_                            \
          , BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(spec)                   \
        )(arities)                                                           \
      , BOOST_PP_TUPLE_ELEM(3, 2, arities)                                   \
      , spec                                                                 \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AS_DEDUCED                       \
    )
/**/

#include <boost/preprocessor/seq/for_each_i.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_deduced(r, arities, spec)        \
    BOOST_PP_SEQ_FOR_EACH_I_R(                                               \
        r                                                                    \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_deduced_M                        \
      , arities                                                              \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_ARGS(spec)                            \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC(r, arities, spec)                \
    BOOST_PP_CAT(                                                            \
        BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_                                 \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(spec)                       \
    )(r, arities, spec)
/**/

#include <boost/preprocessor/seq/for_each.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN(                                      \
    opt_arity, req_arity, wanted_arity, specs                                \
)                                                                            \
    BOOST_PP_SEQ_FOR_EACH(                                                   \
        BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC                                  \
      , (opt_arity, req_arity, wanted_arity)                                 \
      , specs                                                                \
    )
/**/

#endif  // include guard


/* flatten.hpp
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
*/