// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_DISPATCH_LAYER_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_DISPATCH_LAYER_HPP

#include <boost/preprocessor/cat.hpp>

// Expands to keyword_tag_type for some keyword_tag.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_TYPE(keyword_tag)              \
    BOOST_PP_CAT(keyword_tag, _type)
/**/

// Expands to a template parameter for each dispatch function.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_TEMPLATE_ARG(r, macro, arg)        \
  , typename BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_TYPE(macro(arg))
/**/

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

// Expands to a forwarding parameter for a dispatch function.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_DEFN(r, macro, arg)            \
  , BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_TYPE(macro(arg))&& macro(arg)
/**/

#include <utility>

// Expands to an argument passed from one dispatch function to the next.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_FWD(r, macro, arg)             \
  , ::std::forward<                                                          \
        BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_TYPE(macro(arg))               \
    >(macro(arg))
/**/

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

// Expands to a forwarding parameter for a dispatch function.  The parameter
// type stores its const-ness.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_DEFN(r, macro, arg)            \
  , BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_TYPE(macro(arg))& macro(arg)
/**/

#include <boost/parameter/aux_/as_lvalue.hpp>

// Expands to an argument passed from one dispatch function to the next.
// Explicit forwarding takes the form of forcing the argument to be an lvalue.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_FWD(r, macro, arg)             \
  , ::boost::parameter::aux::as_lvalue(macro(arg))
/**/

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING

#include <boost/parameter/aux_/preprocessor/impl/argument_specs.hpp>
#include <boost/parameter/aux_/preprocessor/impl/split_args.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/first_n.hpp>

// Iterates through all required arguments and the first n optional arguments,
// passing each argument to the specified macro.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_REPEAT(macro, n, split_args)   \
    BOOST_PP_SEQ_FOR_EACH(                                                   \
        macro                                                                \
      , BOOST_PARAMETER_FN_ARG_NAME                                          \
      , BOOST_PARAMETER_SPLIT_ARG_REQ_SEQ(split_args)                        \
    )                                                                        \
    BOOST_PP_SEQ_FOR_EACH(                                                   \
        macro                                                                \
      , BOOST_PARAMETER_FN_ARG_NAME                                          \
      , BOOST_PP_SEQ_FIRST_N(                                                \
            n, BOOST_PARAMETER_SPLIT_ARG_OPT_SEQ(split_args)                 \
        )                                                                    \
    )
/**/

#include <boost/parameter/aux_/preprocessor/impl/function_dispatch_tuple.hpp>
#include <boost/parameter/aux_/preprocessor/impl/function_name.hpp>
#include <boost/preprocessor/control/if.hpp>

// Produces a name for the dispatch functions.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_NAME(x, n)                         \
    BOOST_PP_CAT(                                                            \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(                                                     \
                BOOST_PARAMETER_FUNCTION_DISPATCH_IS_CONST(x)                \
              , boost_param_dispatch_const_                                  \
              , boost_param_dispatch_                                        \
            )                                                                \
          , BOOST_PP_CAT(BOOST_PP_CAT(n, boost_), __LINE__)                  \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(                                \
            BOOST_PARAMETER_FUNCTION_DISPATCH_BASE_NAME(x)                   \
        )                                                                    \
    )
/**/

// Expands to the template parameter list of the dispatch function with all
// required and first n optional parameters; also extracts the static keyword
// if present.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_HEAD_TPL(n, x)                     \
    template <                                                               \
        typename ResultType, typename Args                                   \
        BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_REPEAT(                        \
            BOOST_PARAMETER_FUNCTION_DISPATCH_TEMPLATE_ARG                   \
          , n                                                                \
          , BOOST_PARAMETER_FUNCTION_DISPATCH_SPLIT_ARGS(x)                  \
        )                                                                    \
    > BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(                                \
        BOOST_PARAMETER_FUNCTION_DISPATCH_BASE_NAME(x)                       \
    )
/**/

#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

// Expands to the result type, name, parenthesized list of all required and
// n optional parameters, and const-ness of the dispatch function; the bit
// value b determines whether or not this dispatch function takes in
// boost::parameter::aux::use_default_tag as its last parameter.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_HEAD_PRN(n, x, b1, b2)             \
    ResultType BOOST_PARAMETER_FUNCTION_DISPATCH_NAME(x, b1)(                \
        ResultType(*)(), Args const& args, long                              \
        BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_REPEAT(                        \
            BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_DEFN                       \
          , n                                                                \
          , BOOST_PARAMETER_FUNCTION_DISPATCH_SPLIT_ARGS(x)                  \
        )                                                                    \
        BOOST_PP_COMMA_IF(b2)                                                \
        BOOST_PP_EXPR_IF(b2, ::boost::parameter::aux::use_default_tag)       \
    ) BOOST_PP_EXPR_IF(BOOST_PARAMETER_FUNCTION_DISPATCH_IS_CONST(x), const)
/**/

// Expands to a forward declaration of the dispatch function that takes in
// all required and the first n optional parameters, but not
// boost::parameter::aux::use_default_tag.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_FWD_DECL_0_Z(z, n, x)              \
    BOOST_PARAMETER_FUNCTION_DISPATCH_HEAD_TPL(n, x)                         \
    BOOST_PARAMETER_FUNCTION_DISPATCH_HEAD_PRN(n, x, 0, 0);
/**/

// Expands to a forward declaration of the dispatch function that takes in
// all required parameters, the first n optional parameters, and
// boost::parameter::aux::use_default_tag.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_FWD_DECL_1_Z(z, n, x)              \
    BOOST_PARAMETER_FUNCTION_DISPATCH_HEAD_TPL(n, x)                         \
    BOOST_PARAMETER_FUNCTION_DISPATCH_HEAD_PRN(n, x, 0, 1);
/**/

#include <boost/preprocessor/seq/elem.hpp>

// Expands to the default value of the (n + 1)th optional parameter.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_DEFAULT_AUX(n, s_args)             \
    BOOST_PARAMETER_FN_ARG_DEFAULT(                                          \
        BOOST_PP_SEQ_ELEM(n, BOOST_PARAMETER_SPLIT_ARG_OPT_SEQ(s_args))      \
    )
/**/

#include <boost/parameter/keyword.hpp>

// Expands to the assignment portion which binds the default value to the
// (n + 1)th optional parameter before composing it with the argument-pack
// parameter passed in to the n-th dispatch function.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_DEFAULT(n, s_args, tag_ns)         \
    ::boost::parameter::keyword<                                             \
        tag_ns::BOOST_PARAMETER_FN_ARG_NAME(                                 \
            BOOST_PP_SEQ_ELEM(n, BOOST_PARAMETER_SPLIT_ARG_OPT_SEQ(s_args))  \
        )                                                                    \
    >::instance = BOOST_PARAMETER_FUNCTION_DISPATCH_DEFAULT_AUX(n, s_args)
/**/

#include <boost/parameter/aux_/preprocessor/impl/function_cast.hpp>

// Takes in the arg tuple (name, pred) and the tag namespace.
// Extracts the corresponding required argument from the pack.
// This form enables BOOST_PARAMETER_FUNCTION_DISPATCH_LAYER to use it
// from within BOOST_PP_SEQ_FOR_EACH.
#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
// The boost::parameter::aux::forward wrapper is necessary to transmit the
// target type to the next dispatch function.  Otherwise, the argument will
// retain its original type. -- Cromwell D. Enage
#define BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_CAST_R(r, tag_ns, arg)         \
  , ::boost::parameter::aux::forward<                                        \
        BOOST_PARAMETER_FUNCTION_CAST_T(                                     \
            tag_ns::BOOST_PARAMETER_FN_ARG_NAME(arg)                         \
          , BOOST_PARAMETER_FN_ARG_PRED(arg)                                 \
          , Args                                                             \
        )                                                                    \
      , BOOST_PARAMETER_FUNCTION_CAST_B(                                     \
            tag_ns::BOOST_PARAMETER_FN_ARG_NAME(arg)                         \
          , BOOST_PARAMETER_FN_ARG_PRED(arg)                                 \
          , Args                                                             \
        )                                                                    \
    >(                                                                       \
        args[                                                                \
            ::boost::parameter::keyword<                                     \
                tag_ns::BOOST_PARAMETER_FN_ARG_NAME(arg)                     \
            >::instance                                                      \
        ]                                                                    \
    )
/**/
#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
// The explicit type cast is necessary to transmit the target type to the next
// dispatch function.  Otherwise, the argument will retain its original type.
// -- Cromwell D. Enage
#define BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_CAST_R(r, tag_ns, arg)         \
  , BOOST_PARAMETER_FUNCTION_CAST_T(                                         \
        tag_ns::BOOST_PARAMETER_FN_ARG_NAME(arg)                             \
      , BOOST_PARAMETER_FN_ARG_PRED(arg)                                     \
      , Args                                                                 \
    )(                                                                       \
        args[                                                                \
            ::boost::parameter::keyword<                                     \
                tag_ns::BOOST_PARAMETER_FN_ARG_NAME(arg)                     \
            >::instance                                                      \
        ]                                                                    \
    )
/**/
#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING

// Takes in the arg tuple (name, pred, default) and the tag namespace.
// Extracts the corresponding optional argument from the pack if specified,
// otherwise temporarily passes use_default_tag() to the dispatch functions.
#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
// The boost::parameter::aux::forward wrapper is necessary to transmit the
// target type to the next dispatch function.  Otherwise, the argument will
// retain its original type. -- Cromwell D. Enage
#define BOOST_PARAMETER_FUNCTION_DISPATCH_OPT_ARG_CAST(arg, tag_ns)          \
    ::boost::parameter::aux::forward<                                        \
        BOOST_PARAMETER_FUNCTION_CAST_T(                                     \
            tag_ns::BOOST_PARAMETER_FN_ARG_NAME(arg)                         \
          , BOOST_PARAMETER_FN_ARG_PRED(arg)                                 \
          , Args                                                             \
        )                                                                    \
      , BOOST_PARAMETER_FUNCTION_CAST_B(                                     \
            tag_ns::BOOST_PARAMETER_FN_ARG_NAME(arg)                         \
          , BOOST_PARAMETER_FN_ARG_PRED(arg)                                 \
          , Args                                                             \
        )                                                                    \
    >(                                                                       \
        args[                                                                \
            ::boost::parameter::keyword<                                     \
                tag_ns::BOOST_PARAMETER_FN_ARG_NAME(arg)                     \
            >::instance || ::boost::parameter::aux::use_default_tag()        \
        ]                                                                    \
    )
/**/
#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#define BOOST_PARAMETER_FUNCTION_DISPATCH_OPT_ARG_CAST(arg, tag_ns)          \
    BOOST_PARAMETER_FUNCTION_CAST_B(                                         \
        args[                                                                \
            ::boost::parameter::keyword<                                     \
                tag_ns::BOOST_PARAMETER_FN_ARG_NAME(arg)                     \
            >::instance || ::boost::parameter::aux::use_default_tag()        \
        ]                                                                    \
      , BOOST_PARAMETER_FN_ARG_PRED(arg)                                     \
      , Args                                                                 \
    )
/**/
#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING

#include <boost/parameter/aux_/preprocessor/nullptr.hpp>

// Expands to three dispatch functions that take in all required parameters
// and the first n optional parameters.  The third dispatch function bears
// the same name as the first but takes in use_default_tag as the last
// parameter.  The second dispatch function bears a different name from the
// other two.
//
// x is a tuple:
//
//   (name, split_args, is_const, tag_namespace)
//
// Where name is the base name of the functions, and split_args is a tuple:
//
//   (required_count, required_args, optional_count, required_args)
//
// The first dispatch function queries args if it has bound the (n + 1)th
// optional parameter to a user-defined argument.  If so, then it forwards
// its own arguments followed by the user-defined argument to the dispatch
// function that takes in all required parameters and the first (n + 1)
// optional parameters, but not use_default_tag.   Otherwise, it forwards
// its own arguments to the third dispatch function.
//
// The third dispatch function appends the default value of the (n + 1)th
// optional parameter to its copy of args.  Then it forwards this copy, all
// required parameters, and the first n (not n + 1) optional parameters to
// the second dispatch function.
//
// The second dispatch function forwards its arguments, then the (n + 1)th
// optional parameter that it extracts from args, to the other-named dispatch
// function that takes in all required parameters and the first (n + 1)
// optional parameters, but not use_default_tag.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_OVERLOAD_Z(z, n, x)                \
    BOOST_PARAMETER_FUNCTION_DISPATCH_HEAD_TPL(n, x)                         \
    inline BOOST_PARAMETER_FUNCTION_DISPATCH_HEAD_PRN(n, x, 0, 0)            \
    {                                                                        \
        return BOOST_PP_EXPR_IF(                                             \
            BOOST_PARAMETER_FUNCTION_DISPATCH_IS_MEMBER(x)                   \
          , this->                                                           \
        ) BOOST_PARAMETER_FUNCTION_DISPATCH_NAME(x, 0)(                      \
            static_cast<ResultType(*)()>(BOOST_PARAMETER_AUX_PP_NULLPTR)     \
          , args                                                             \
          , 0L                                                               \
            BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_REPEAT(                    \
                BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_FWD                    \
              , n                                                            \
              , BOOST_PARAMETER_FUNCTION_DISPATCH_SPLIT_ARGS(x)              \
            )                                                                \
          , BOOST_PARAMETER_FUNCTION_DISPATCH_OPT_ARG_CAST(                  \
                BOOST_PP_SEQ_ELEM(                                           \
                    n                                                        \
                  , BOOST_PARAMETER_SPLIT_ARG_OPT_SEQ(                       \
                        BOOST_PARAMETER_FUNCTION_DISPATCH_SPLIT_ARGS(x)      \
                    )                                                        \
                )                                                            \
              , BOOST_PARAMETER_FUNCTION_DISPATCH_TAG_NAMESPACE(x)           \
            )                                                                \
        );                                                                   \
    }                                                                        \
    BOOST_PARAMETER_FUNCTION_DISPATCH_HEAD_TPL(n, x)                         \
    inline BOOST_PARAMETER_FUNCTION_DISPATCH_HEAD_PRN(n, x, 1, 0)            \
    {                                                                        \
        return BOOST_PP_EXPR_IF(                                             \
            BOOST_PARAMETER_FUNCTION_DISPATCH_IS_MEMBER(x)                   \
          , this->                                                           \
        ) BOOST_PARAMETER_FUNCTION_DISPATCH_NAME(x, 0)(                      \
            static_cast<ResultType(*)()>(BOOST_PARAMETER_AUX_PP_NULLPTR)     \
          , args                                                             \
          , 0L                                                               \
            BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_REPEAT(                    \
                BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_FWD                    \
              , n                                                            \
              , BOOST_PARAMETER_FUNCTION_DISPATCH_SPLIT_ARGS(x)              \
            )                                                                \
          , args[                                                            \
                ::boost::parameter::keyword<                                 \
                    BOOST_PARAMETER_FUNCTION_DISPATCH_TAG_NAMESPACE(x)::     \
                    BOOST_PARAMETER_FN_ARG_NAME(                             \
                        BOOST_PP_SEQ_ELEM(                                   \
                            n                                                \
                          , BOOST_PARAMETER_SPLIT_ARG_OPT_SEQ(               \
                            BOOST_PARAMETER_FUNCTION_DISPATCH_SPLIT_ARGS(x)  \
                            )                                                \
                        )                                                    \
                    )                                                        \
                >::instance                                                  \
            ]                                                                \
        );                                                                   \
    }                                                                        \
    BOOST_PARAMETER_FUNCTION_DISPATCH_HEAD_TPL(n, x)                         \
    inline BOOST_PARAMETER_FUNCTION_DISPATCH_HEAD_PRN(n, x, 0, 1)            \
    {                                                                        \
        return BOOST_PP_EXPR_IF(                                             \
            BOOST_PARAMETER_FUNCTION_DISPATCH_IS_MEMBER(x)                   \
          , this->                                                           \
        ) BOOST_PARAMETER_FUNCTION_DISPATCH_NAME(x, 1)(                      \
            static_cast<ResultType(*)()>(BOOST_PARAMETER_AUX_PP_NULLPTR)     \
          , (args                                                            \
              , BOOST_PARAMETER_FUNCTION_DISPATCH_DEFAULT(                   \
                    n                                                        \
                  , BOOST_PARAMETER_FUNCTION_DISPATCH_SPLIT_ARGS(x)          \
                  , BOOST_PARAMETER_FUNCTION_DISPATCH_TAG_NAMESPACE(x)       \
                )                                                            \
            )                                                                \
          , 0L                                                               \
            BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_REPEAT(                    \
                BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_FWD                    \
              , n                                                            \
              , BOOST_PARAMETER_FUNCTION_DISPATCH_SPLIT_ARGS(x)              \
            )                                                                \
        );                                                                   \
    }
/**/

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// x is a tuple:
//
//   (base_name, split_args, is_member, is_const, tag_namespace)
//
// Generates all dispatch functions for the function named base_name.  Each
// dispatch function that takes in n optional parameters passes the default
// value of the (n + 1)th optional parameter to the next dispatch function.
// The last dispatch function is the back-end implementation, so only the
// header is generated: the user is expected to supply the body.
//
// Also generates the front-end implementation function, which uses
// BOOST_PARAMETER_FUNCTION_CAST to extract each argument from the argument
// pack.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_LAYER(fwd_decl, x)                 \
    BOOST_PP_IF(fwd_decl, BOOST_PP_REPEAT_FROM_TO, BOOST_PP_TUPLE_EAT(4))(   \
        0                                                                    \
      , BOOST_PP_INC(                                                        \
            BOOST_PARAMETER_SPLIT_ARG_OPT_COUNT(                             \
                BOOST_PARAMETER_FUNCTION_DISPATCH_SPLIT_ARGS(x)              \
            )                                                                \
        )                                                                    \
      , BOOST_PARAMETER_FUNCTION_DISPATCH_FWD_DECL_0_Z                       \
      , x                                                                    \
    )                                                                        \
    BOOST_PP_IF(fwd_decl, BOOST_PP_REPEAT_FROM_TO, BOOST_PP_TUPLE_EAT(4))(   \
        0                                                                    \
      , BOOST_PARAMETER_SPLIT_ARG_OPT_COUNT(                                 \
            BOOST_PARAMETER_FUNCTION_DISPATCH_SPLIT_ARGS(x)                  \
        )                                                                    \
      , BOOST_PARAMETER_FUNCTION_DISPATCH_FWD_DECL_1_Z                       \
      , x                                                                    \
    )                                                                        \
    template <typename Args> BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(         \
        BOOST_PARAMETER_FUNCTION_DISPATCH_BASE_NAME(x)                       \
    ) inline typename BOOST_PARAMETER_FUNCTION_RESULT_NAME(                  \
        BOOST_PARAMETER_FUNCTION_DISPATCH_BASE_NAME(x)                       \
      , BOOST_PARAMETER_FUNCTION_DISPATCH_IS_CONST(x)                        \
    )<Args>::type BOOST_PARAMETER_FUNCTION_IMPL_NAME(                        \
        BOOST_PARAMETER_FUNCTION_DISPATCH_BASE_NAME(x)                       \
      , BOOST_PARAMETER_FUNCTION_DISPATCH_IS_CONST(x)                        \
    )(Args const& args)                                                      \
    BOOST_PP_EXPR_IF(BOOST_PARAMETER_FUNCTION_DISPATCH_IS_CONST(x), const)   \
    {                                                                        \
        return BOOST_PP_EXPR_IF(                                             \
            BOOST_PARAMETER_FUNCTION_DISPATCH_IS_MEMBER(x)                   \
          , this->                                                           \
        ) BOOST_PARAMETER_FUNCTION_DISPATCH_NAME(x, 0)(                      \
            static_cast<                                                     \
                typename BOOST_PARAMETER_FUNCTION_RESULT_NAME(               \
                    BOOST_PARAMETER_FUNCTION_DISPATCH_BASE_NAME(x)           \
                  , BOOST_PARAMETER_FUNCTION_DISPATCH_IS_CONST(x)            \
                )<Args>::type(*)()                                           \
            >(BOOST_PARAMETER_AUX_PP_NULLPTR)                                \
          , args                                                             \
          , 0L                                                               \
            BOOST_PP_SEQ_FOR_EACH(                                           \
                BOOST_PARAMETER_FUNCTION_DISPATCH_ARG_CAST_R                 \
              , BOOST_PARAMETER_FUNCTION_DISPATCH_TAG_NAMESPACE(x)           \
              , BOOST_PARAMETER_SPLIT_ARG_REQ_SEQ(                           \
                    BOOST_PARAMETER_FUNCTION_DISPATCH_SPLIT_ARGS(x)          \
                )                                                            \
            )                                                                \
        );                                                                   \
    }                                                                        \
    BOOST_PP_REPEAT_FROM_TO(                                                 \
        0                                                                    \
      , BOOST_PARAMETER_SPLIT_ARG_OPT_COUNT(                                 \
            BOOST_PARAMETER_FUNCTION_DISPATCH_SPLIT_ARGS(x)                  \
        )                                                                    \
      , BOOST_PARAMETER_FUNCTION_DISPATCH_OVERLOAD_Z                         \
      , x                                                                    \
    )                                                                        \
    BOOST_PARAMETER_FUNCTION_DISPATCH_HEAD_TPL(                              \
        BOOST_PARAMETER_SPLIT_ARG_OPT_COUNT(                                 \
            BOOST_PARAMETER_FUNCTION_DISPATCH_SPLIT_ARGS(x)                  \
        )                                                                    \
      , x                                                                    \
    )                                                                        \
    inline BOOST_PARAMETER_FUNCTION_DISPATCH_HEAD_PRN(                       \
        BOOST_PARAMETER_SPLIT_ARG_OPT_COUNT(                                 \
            BOOST_PARAMETER_FUNCTION_DISPATCH_SPLIT_ARGS(x)                  \
        )                                                                    \
      , x                                                                    \
      , 0                                                                    \
      , 0                                                                    \
    )
/**/

#endif  // include guard


/* function_dispatch_layer.hpp
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
*/