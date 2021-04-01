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
PlG59KKJ2qPT/b66QZSAitArSSZRGNQ6zEqWG9oJITruHXQESs1qdjAl7kedatp8jYq6PoUbBBccR7igLZ60zPYG/qWQlsAbH4rY6tkMLzIQ1HAJMoMqOyDL644in2ZgYKE3SuubcCFsJf6rUTIf1pn77TlFvufOIVOdFca2QKrbMIis57Hvc81K0xAPMLF2n8szYipOAIIUl7q80+WHN0uTkzmyvPpiINdEyhA5kjKzadhSR4eVVjn54qShaFMS/wMAl3T1vXZ3p6ntqUd9vEIpABwkQvl1db+M/CBIvwhlaFa7fO+vDrrp0o06g4UL1x5Nhi9Q2jLz09+l6seDxeyzVVsHJm2x3wUK8RHIDsl+4o0kEX/EpUwgh5D4tu+GyhdaOgI5hnbryAUnoOU/FsjzW3F0D2MuYZtfp4FcVT/jRTHRdJorPdFmP55lIMOVEaSDeesWTrHjBOMViK6jXY1eT6cafK7VYLBXNo4YCrUA2L6k8ww9b7GA4eTli/5jo7xj1XxLjxa6oN8qP2kiZTn72Wzk7jekszOpMlVOTGo6vIfJkoVmbvHb6w==
*/