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
timZ5DMZgYJqfHw16lzFYaLUQecGVNWwZBok1boK4JQdbBb7tWBOPf8blEeuOMhmymMM2dfA79dW/UoaQcUeAycZSKWOzuY7frkpcE7QlaHJnx7ZCc9iKo6UcIHHQ7Zll5Zlcuj195D69SRl9+A8OnTYGT3KXGJZSupE3JM0wrnPraFJTtcMJ1uD85jTHqAkECBgqR9MtANEuZzBg2OCXlQjUQstPU5ZwvVN4t7+UPNLEfqaF4p5FSyjYPH55BAELfW9WhW8IBFF8UB/d//K+8IrrCygyH+smlbll6KyBmgHdq2dTp1IE1VbmfLELH5SDDNyoMw4+fU13WN9vElQfR/dBPJ1hHg8v8+tvaR/05lIY/LqEBnKLRlRQMhnx68fI77b54MvCwYRO451nClBQe3x5YjD7t28ZXSp+bNYtTpkn0pGKgk8tpbuDC9uvPAVxvB+Ez+BXsscZPPqC7N2y10JGd8xeScDFkiCGPm80s7iCUvyHBMtzBc4CS/wC/nVy+Qdu6xDsfkzNG1sEOVwvcsmJWA1nA5Ok5frjNwiXbeUt0IDPnNd5paalA==
*/