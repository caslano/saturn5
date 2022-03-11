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