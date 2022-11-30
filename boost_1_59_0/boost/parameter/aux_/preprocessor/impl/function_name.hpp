// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_NAME_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_NAME_HPP

#define BOOST_PARAMETER_MEMBER_FUNCTION_CHECK_STATIC_static ()
/**/

#include <boost/parameter/aux_/preprocessor/is_nullary.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_MEMBER_FUNCTION_IS_STATIC(name)                      \
    BOOST_PARAMETER_IS_NULLARY(                                              \
        BOOST_PP_CAT(BOOST_PARAMETER_MEMBER_FUNCTION_CHECK_STATIC_, name)    \
    )
/**/

#include <boost/preprocessor/seq/seq.hpp>
#include <boost/config.hpp>

#if defined(BOOST_MSVC)

// Workaround for MSVC preprocessor.
//
// When stripping static from "static f", msvc will produce " f".  The leading
// whitespace doesn't go away when pasting the token with something else, so
// this thing is a hack to strip the whitespace.
#define BOOST_PARAMETER_MEMBER_FUNCTION_STRIP_STATIC_static (
/**/

#define BOOST_PARAMETER_MEMBER_FUNCTION_STRIP_STATIC_AUX(name)               \
    BOOST_PP_CAT(BOOST_PARAMETER_MEMBER_FUNCTION_STRIP_STATIC_, name))
/**/

#define BOOST_PARAMETER_MEMBER_FUNCTION_STRIP_STATIC(name)                   \
    BOOST_PP_SEQ_HEAD(                                                       \
        BOOST_PARAMETER_MEMBER_FUNCTION_STRIP_STATIC_AUX(name)               \
    )
/**/

#else

#define BOOST_PARAMETER_MEMBER_FUNCTION_STRIP_STATIC_static
/**/

#define BOOST_PARAMETER_MEMBER_FUNCTION_STRIP_STATIC(name)                   \
    BOOST_PP_CAT(BOOST_PARAMETER_MEMBER_FUNCTION_STRIP_STATIC_, name)
/**/

#endif  // MSVC workarounds needed

#include <boost/preprocessor/control/expr_if.hpp>

#define BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(name)                         \
    BOOST_PP_EXPR_IF(                                                        \
        BOOST_PARAMETER_MEMBER_FUNCTION_IS_STATIC(name), static              \
    )
/**/

#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

#define BOOST_PARAMETER_MEMBER_FUNCTION_NAME(name)                           \
    BOOST_PP_IF(                                                             \
        BOOST_PARAMETER_MEMBER_FUNCTION_IS_STATIC(name)                      \
      , BOOST_PARAMETER_MEMBER_FUNCTION_STRIP_STATIC                         \
      , name BOOST_PP_TUPLE_EAT(1)                                           \
    )(name)
/**/

// Produces a name for a parameter specification for the function named base.
#define BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(base, is_const)          \
    BOOST_PP_CAT(                                                            \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(                                                     \
                is_const                                                     \
              , boost_param_parameters_const_                                \
              , boost_param_parameters_                                      \
            )                                                                \
          , __LINE__                                                         \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(base)                           \
    )
/**/

// Produces a name for a result type metafunction for the no-spec function
// named base.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(base, is_const)         \
    BOOST_PP_CAT(                                                            \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(                                                     \
                is_const                                                     \
              , boost_param_no_spec_result_const_                            \
              , boost_param_no_spec_result_                                  \
            )                                                                \
          , __LINE__                                                         \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(base)                           \
    )
/**/

// Produces a name for a result type metafunction for the function named base.
#define BOOST_PARAMETER_FUNCTION_RESULT_NAME(base, is_const)                 \
    BOOST_PP_CAT(                                                            \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(                                                     \
                is_const                                                     \
              , boost_param_result_const_                                    \
              , boost_param_result_                                          \
            )                                                                \
          , __LINE__                                                         \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(base)                           \
    )
/**/

// Produces a name for the implementation function to which the no-spec
// function named base forwards its result type and argument pack.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_NAME(base, is_const)           \
    BOOST_PP_CAT(                                                            \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(                                                     \
                is_const                                                     \
              , boost_param_no_spec_impl_const                               \
              , boost_param_no_spec_impl                                     \
            )                                                                \
          , __LINE__                                                         \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(base)                           \
    )
/**/

// Can't do boost_param_impl_ ## basee
// because base might start with an underscore.
// daniel: what? how is that relevant? the reason for using CAT()
// is to make sure base is expanded. i'm not sure we need to here,
// but it's more stable to do it.
#define BOOST_PARAMETER_FUNCTION_IMPL_NAME(base, is_const)                   \
    BOOST_PP_CAT(                                                            \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(is_const, boost_param_impl_const, boost_param_impl)  \
          , __LINE__                                                         \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(base)                           \
    )
/**/

#endif  // include guard


/* function_name.hpp
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
*/