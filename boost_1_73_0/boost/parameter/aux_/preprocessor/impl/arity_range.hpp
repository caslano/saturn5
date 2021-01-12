// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_ARITY_RANGE_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_ARITY_RANGE_HPP

// Helper macros for BOOST_PARAMETER_ARITY_RANGE.
#define BOOST_PARAMETER_ARITY_RANGE_M_optional(state) state
#define BOOST_PARAMETER_ARITY_RANGE_M_deduced_optional(state) state

#include <boost/preprocessor/arithmetic/inc.hpp>

#define BOOST_PARAMETER_ARITY_RANGE_M_required(state) BOOST_PP_INC(state)
#define BOOST_PARAMETER_ARITY_RANGE_M_deduced_required(state)                \
    BOOST_PP_INC(state)
/**/

#include <boost/parameter/aux_/preprocessor/impl/argument_specs.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_ARITY_RANGE_M(s, state, x)                           \
    BOOST_PP_CAT(                                                            \
        BOOST_PARAMETER_ARITY_RANGE_M_                                       \
      , BOOST_PARAMETER_FN_ARG_QUALIFIER(x)                                  \
    )(state)
/**/

#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/seq/size.hpp>

// Calculates [begin, end) arity range.
#define BOOST_PARAMETER_ARITY_RANGE(args)                                    \
    (                                                                        \
        BOOST_PP_SEQ_FOLD_LEFT(BOOST_PARAMETER_ARITY_RANGE_M, 0, args)       \
      , BOOST_PP_INC(BOOST_PP_SEQ_SIZE(args))                                \
    )
/**/

#endif  // include guard


/* arity_range.hpp
D9M4NaaDkbTdgWXTOBbeXKChXOqHmlm7xXtqm1mbRVbXbNorjTU2U1uiOIuaqR0phGO4WI94eTZTPSLWBKyfmB3DxXoEhJ7nzZhHFm+putdhy5pZGXt2HJeVL+q8opmVLR9/UzI5pzFdVpaMt6AOLm8F3peHXkmFoR4rm6nvJD3afNsRa7dpqe/2MpmrMC2XHwocmkkCRpuyRcZXKzsmQAmHPwV4Yhie9Al/jPwwJRsUUeKt
*/