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