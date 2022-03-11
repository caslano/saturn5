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
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
*/