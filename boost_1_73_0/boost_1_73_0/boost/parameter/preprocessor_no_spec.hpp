// Copyright Cromwell D. Enage 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_PREPROCESSOR_NO_SPEC_HPP
#define BOOST_PARAMETER_PREPROCESSOR_NO_SPEC_HPP

#include <boost/parameter/aux_/preprocessor/impl/function_name.hpp>
#include <boost/parameter/aux_/preprocessor/impl/no_spec_overloads.hpp>

// Exapnds to a variadic function header that is enabled if and only if all
// its arguments are tagged arguments.  All arguments are accessible via args
// and keywords only.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION(result, name)                       \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_HEAD(result, name, 0)                   \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_HEAD(name, 0);                     \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_OVERLOAD(name, name, 0, 0)              \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_HEAD(name, 0)
/**/

#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/control/if.hpp>

// Helper macro for BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION,
// BOOST_PARAMETER_NO_SPEC_CONST_MEMBER_FUNCTION,
// BOOST_PARAMETER_NO_SPEC_FUNCTION_CALL_OPERATOR, and
// and BOOST_PARAMETER_NO_SPEC_CONST_FUNCTION_CALL_OPERATOR.
#define BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION_AUX(result, name, impl, c)   \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_HEAD(result, impl, c)                   \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_OVERLOAD(                               \
        name                                                                 \
      , impl                                                                 \
      , BOOST_PP_IF(BOOST_PARAMETER_MEMBER_FUNCTION_IS_STATIC(impl), 0, 1)   \
      , c                                                                    \
    )                                                                        \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_HEAD(impl, c)                      \
    BOOST_PP_EXPR_IF(c, const)
/**/

// Exapnds to a variadic member function header that is enabled if and only if
// all its arguments are tagged arguments.  All arguments are accessible via
// args and keywords only.
#define BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION(result, name)                \
    BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION_AUX(result, name, name, 0)
/**/

// Exapnds to a const-qualified variadic member function header that is
// enabled if and only if all its arguments are tagged arguments.  All
// arguments are accessible via args and keywords only.
#define BOOST_PARAMETER_NO_SPEC_CONST_MEMBER_FUNCTION(result, name)          \
    BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION_AUX(result, name, name, 1)
/**/

// Exapnds to a variadic function call operator header that is enabled if and
// only if all its arguments are tagged arguments.  All arguments are
// accessible via args and keywords only.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_CALL_OPERATOR(result)               \
    BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION_AUX(                             \
        result, operator(), operator, 0                                      \
    )
/**/

// Exapnds to a const-qualified variadic function call operator header that is
// enabled if and only if all its arguments are tagged arguments.  All
// arguments are accessible via args and keywords only.
#define BOOST_PARAMETER_NO_SPEC_CONST_FUNCTION_CALL_OPERATOR(result)         \
    BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION_AUX(                             \
        result, operator(), operator, 1                                      \
    )
/**/

#endif  // include guard


/* preprocessor_no_spec.hpp
kByFTPkmZUpycnuyxQZlY3xWITI99dwcnv5zlMFRTXHwsel+ZFCe2l6nekqYPXNStKyUwk8dp7e+QlAIFM9nFz9CZE9nbasOvErgHB7+jjAsIHtYJCG8DqG/7bSpw7ISYnAjriu2KnMSMhiXh/Iaf0ykW24vW1Qg4kvjKwZ/skm3zN4mmOMFWbPx/5k7YDXmzRrl02d6cYZcHieXZ8f7CcJOHTSHcPZ8j5mKt7WdXV8YvvCDr+DCUB7VcYna/LQDifg/HEpnq/gPMe4wrdaA/CBhBuXzm3A3o3Z1NzqfXS/wu06w6zD4xgmGp+moxTMrvCwpyOswPHu5S3zljG/j+VG6pe5x9vgEKan8k8eMn+4jJpGgMp5IezAmh/T9RiyQDYaCPZiCJtl34huep2hwoqIYuerSASA4dqxLPPH8LJ60JlibzlI1m50dCgvxfdThyXFTZfi4bRmelLSfKrxZEV50mCKJwnb10sNhV46zlG9jmGVM3zDfpgOleLszLzn78YAmuTQuc8QhUWhd9qGANNoAHulYEN8ohV+gQW1Pfn+DPJMsT9Yek0l0IBdHDM7kIu325NA9PPLLParqeNx17YgvLHIyx5GPU5AqMHnWeE9S9/8fUEsDBAoAAAAIAC1nSlJ0ZzFB7AMAAP4I
*/