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
0WDFrVhwLRQp7hQJ7l4oLoFixSW4u0OQQLAk99093D3czT2uze7s7uzsb/68f9lrd1Oq/IGBR1/JDCdzfw9gcJY9v5/wh6/5n8uMrk20bfg/cOHnBa6Ep22U4dqLpU3FhONxeqYJhDPNkbzZhceEy/dy8D7JIsAqYHSHly0DDrRdPtcCfJjpmFwh1yFpPfc9nO/FDCtBpefwI5SN5Dvcv6KBeDq0LjER7F+wIKUluzy1vsTd0PJMvpG81DnQl+VHOXj0uJymbJ84qEs53bciZkYYjf8ZtCtxm4Wl4d2H6MI/Q2Vb4CThSq8zKaGktrAWiFW3zNWgTBfdCuZ4EnWVNO84e5xbHFcqgZA9hAiwt8vsv5xL3BzB++1gLHg1VypFNPtrzXsE/JQab0he7CyI5VcgkWj5V2SA5uZjn9o9H5YpTG1zw0sgYG/1btIoODfUNBJlLP9KsgXnHBfw/Ox59fmdlutOdbEBHuIe+WeyN/PKhZEzt4oI9ak3W56qr+x3446GLj6ycQ68NJA3Ol6GITd6nzhmhTo4cUbHpQqhxLjXNuW2YjSSvyIwiIC7b+JtqmxSsBw8OWzSbBrlEwFwqjFrcUxxO/EMiFf/CnAmd9ZGOPf6c9WjtxK20i0+h6EjovfdW8mBHVGPojtHmHdEGAp/dRPcl3rSJRIPmPr55tnjxKJf17sx2Zxrwkotbd449JMFRkbijJszpdNH
*/