// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_PREPROCESSOR_060206_HPP
#define BOOST_PARAMETER_PREPROCESSOR_060206_HPP

#include <boost/parameter/aux_/preprocessor/impl/forwarding_overloads.hpp>
#include <boost/parameter/aux_/preprocessor/impl/specification.hpp>
#include <boost/preprocessor/cat.hpp>

// Helper macro for BOOST_PARAMETER_CONSTRUCTOR.
#define BOOST_PARAMETER_CONSTRUCTOR_AUX(class_, base, tag_namespace, args)   \
    BOOST_PARAMETER_SPECIFICATION(tag_namespace, ctor, args, 0)              \
        BOOST_PP_CAT(constructor_parameters, __LINE__);                      \
    BOOST_PARAMETER_CONSTRUCTOR_OVERLOADS(class_, base, args)
/**/

#include <boost/parameter/aux_/preprocessor/impl/function_name.hpp>

// Defines the implementation function header.
#define BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name, is_const)                   \
    template <typename Args>                                                 \
    typename BOOST_PARAMETER_FUNCTION_RESULT_NAME(name, is_const)<           \
        Args                                                                 \
    >::type BOOST_PARAMETER_FUNCTION_IMPL_NAME(name, is_const)(              \
        Args const& args                                                     \
    )
/**/

#include <boost/parameter/aux_/preprocessor/impl/parenthesized_return_type.hpp>
#include <boost/parameter/config.hpp>

// Expands to the result metafunction and the parameters specialization.
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_FUNCTION_HEAD(result, name, tag_ns, args, is_const)  \
    template <typename Args>                                                 \
    using BOOST_PARAMETER_FUNCTION_RESULT_NAME(name, is_const)               \
    = typename BOOST_PARAMETER_PARENTHESIZED_RETURN_TYPE(result);            \
    BOOST_PARAMETER_SPECIFICATION(tag_ns, name, args, is_const)              \
        BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(name, is_const);
/**/
#else
#define BOOST_PARAMETER_FUNCTION_HEAD(result, name, tag_ns, args, is_const)  \
    template <typename Args>                                                 \
    struct BOOST_PARAMETER_FUNCTION_RESULT_NAME(name, is_const)              \
      : BOOST_PARAMETER_PARENTHESIZED_RETURN_TYPE(result)                    \
    {                                                                        \
    };                                                                       \
    BOOST_PARAMETER_SPECIFICATION(tag_ns, name, args, is_const)              \
        BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(name, is_const);
/**/
#endif  // BOOST_PARAMETER_CAN_USE_MP11

// Helper macro for BOOST_PARAMETER_BASIC_FUNCTION.
#define BOOST_PARAMETER_BASIC_FUNCTION_AUX(result, name, tag_ns, args)       \
    BOOST_PARAMETER_FUNCTION_HEAD(result, name, tag_ns, args, 0)             \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name, 0);                             \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(name, name, args, 0, 0)       \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name, 0)
/**/

#include <boost/preprocessor/control/expr_if.hpp>

// Helper macro for BOOST_PARAMETER_BASIC_MEMBER_FUNCTION,
// BOOST_PARAMETER_BASIC_CONST_MEMBER_FUNCTION,
// BOOST_PARAMETER_BASIC_FUNCTION_CALL_OPERATOR, and
// BOOST_PARAMETER_BASIC_CONST_FUNCTION_CALL_OPERATOR.
#define BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(r, n, i, tag_ns, args, c)  \
    BOOST_PARAMETER_FUNCTION_HEAD(r, i, tag_ns, args, c)                     \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(n, i, args, 1, c)             \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(i, c) BOOST_PP_EXPR_IF(c, const)
/**/

#include <boost/parameter/aux_/preprocessor/impl/flatten.hpp>

// Expands to a Boost.Parameter-enabled constructor header.  All arguments are
// accessible via args and keywords only.
#define BOOST_PARAMETER_CONSTRUCTOR(class_, base, tag_namespace, args)       \
    BOOST_PARAMETER_CONSTRUCTOR_AUX(                                         \
        class_, base, tag_namespace                                          \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled function header.  All arguments are
// accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_FUNCTION(result, name, tag_namespace, args)    \
    BOOST_PARAMETER_BASIC_FUNCTION_AUX(                                      \
        result, name, tag_namespace                                          \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled member function header.  All arguments
// are accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_MEMBER_FUNCTION(result, name, tag_ns, args)    \
    BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(                               \
        result, name, name, tag_ns                                           \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args), 0                     \
    )
/**/

// Expands to a Boost.Parameter-enabled const-qualified member function
// header.  All arguments are accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_CONST_MEMBER_FUNCTION(r, name, tag_ns, args)   \
    BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(                               \
        r, name, name, tag_ns                                                \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args), 1                     \
    )
/**/

// Expands to a Boost.Parameter-enabled function call operator header.  All
// arguments are accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_FUNCTION_CALL_OPERATOR(result, tag_ns, args)   \
    BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(                               \
        result, operator(), operator, tag_ns                                 \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args), 0                     \
    )
/**/

// Expands to a Boost.Parameter-enabled const-qualified function call
// operator header.  All arguments are accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_CONST_FUNCTION_CALL_OPERATOR(r, tag_ns, args)  \
    BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(                               \
        r, operator(), operator, tag_ns                                      \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args), 1                     \
    )
/**/

#include <boost/parameter/aux_/preprocessor/impl/function_dispatch_layer.hpp>

// Helper macro for BOOST_PARAMETER_FUNCTION.
#define BOOST_PARAMETER_FUNCTION_AUX(result, name, tag_ns, args)             \
    BOOST_PARAMETER_FUNCTION_HEAD(result, name, tag_ns, args, 0)             \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name, 0);                             \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(name, name, args, 0, 0)       \
    BOOST_PARAMETER_FUNCTION_DISPATCH_LAYER(                                 \
        1, (name, BOOST_PARAMETER_FUNCTION_SPLIT_ARGS(args), 0, 0, tag_ns)   \
    )
/**/

// Expands to a Boost.Parameter-enabled function header.  All arguments are
// accessible via args and keywords, as well as by name.
#define BOOST_PARAMETER_FUNCTION(result, name, tag_namespace, args)          \
    BOOST_PARAMETER_FUNCTION_AUX(                                            \
        result, name, tag_namespace                                          \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

#include <boost/preprocessor/control/if.hpp>

// Helper macro for BOOST_PARAMETER_MEMBER_FUNCTION
// BOOST_PARAMETER_CONST_MEMBER_FUNCTION,
// BOOST_PARAMETER_FUNCTION_CALL_OPERATOR, and
// BOOST_PARAMETER_CONST_FUNCTION_CALL_OPERATOR.
#define BOOST_PARAMETER_MEMBER_FUNCTION_AUX(r, name, impl, tag_ns, c, args)  \
    BOOST_PARAMETER_FUNCTION_HEAD(r, impl, tag_ns, args, c)                  \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(name, impl, args, 1, c)       \
    BOOST_PARAMETER_FUNCTION_DISPATCH_LAYER(                                 \
        0, (                                                                 \
            impl                                                             \
          , BOOST_PARAMETER_FUNCTION_SPLIT_ARGS(args)                        \
          , BOOST_PP_IF(                                                     \
                BOOST_PARAMETER_MEMBER_FUNCTION_IS_STATIC(impl)              \
              , 0                                                            \
              , 1                                                            \
            )                                                                \
          , c                                                                \
          , tag_ns                                                           \
        )                                                                    \
    )
/**/

// Expands to a Boost.Parameter-enabled member function header.  All
// arguments are accessible via args and keywords, as well as by name.
#define BOOST_PARAMETER_MEMBER_FUNCTION(result, name, tag_ns, args)          \
    BOOST_PARAMETER_MEMBER_FUNCTION_AUX(                                     \
        result, name, name, tag_ns, 0                                        \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled const-qualified member function
// header.  All arguments are accessible via args and keywords, as well as
// by name.
#define BOOST_PARAMETER_CONST_MEMBER_FUNCTION(result, name, tag_ns, args)    \
    BOOST_PARAMETER_MEMBER_FUNCTION_AUX(                                     \
        result, name, name, tag_ns, 1                                        \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled function call operator header.  All
// arguments are accessible via args and keywords, as well as by name.
#define BOOST_PARAMETER_FUNCTION_CALL_OPERATOR(result, tag_ns, args)         \
    BOOST_PARAMETER_MEMBER_FUNCTION_AUX(                                     \
        result, operator(), operator, tag_ns, 0                              \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled const-qualified function call operator
// header.  All arguments are accessible via args and keywords, as well as
// by name.
#define BOOST_PARAMETER_CONST_FUNCTION_CALL_OPERATOR(result, tag_ns, args)   \
    BOOST_PARAMETER_MEMBER_FUNCTION_AUX(                                     \
        result, operator(), operator, tag_ns, 1                              \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

#endif  // include guard


/* preprocessor.hpp
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
*/