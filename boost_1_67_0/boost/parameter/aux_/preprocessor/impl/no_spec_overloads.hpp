// Copyright Cromwell D. Enage 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_NO_SPEC_OVERLOADS_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_NO_SPEC_OVERLOADS_HPP

#include <boost/parameter/aux_/preprocessor/impl/function_name.hpp>

// Defines the no-spec implementation function header.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_HEAD(name, is_const)           \
    template <typename ResultType, typename Args>                            \
    BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(name) ResultType                  \
        BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_NAME(                          \
            name, is_const                                                   \
        )(ResultType(*)(), Args const& args)
/**/

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#include <boost/parameter/aux_/preprocessor/impl/parenthesized_return_type.hpp>

// Expands to the result metafunction for the specified no-spec function.
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_HEAD(result, name, is_const)        \
    template <typename TaggedArg0, typename ...TaggedArgs>                   \
    using BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(name, is_const)       \
    = typename BOOST_PARAMETER_PARENTHESIZED_RETURN_TYPE(result);
/**/
#else
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_HEAD(result, name, is_const)        \
    template <typename TaggedArg0, typename ...TaggedArgs>                   \
    struct BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(name, is_const)      \
      : BOOST_PARAMETER_PARENTHESIZED_RETURN_TYPE(result)                    \
    {                                                                        \
    };
/**/
#endif  // BOOST_PARAMETER_CAN_USE_MP11

#include <boost/parameter/compose.hpp>
#include <boost/parameter/are_tagged_arguments.hpp>
#include <boost/parameter/aux_/preprocessor/impl/parenthesized_type.hpp>
#include <boost/core/enable_if.hpp>

// Exapnds to a variadic constructor that is enabled if and only if all its
// arguments are tagged arguments.  The enclosing class must inherit from the
// specified base class, which in turn must implement a constructor that takes
// in the argument pack that this one passes on.
#define BOOST_PARAMETER_NO_SPEC_CONSTRUCTOR(class_, base)                    \
    template <                                                               \
        typename TaggedArg0                                                  \
      , typename ...TaggedArgs                                               \
      , typename = typename ::boost::enable_if<                              \
            ::boost::parameter                                               \
            ::are_tagged_arguments<TaggedArg0,TaggedArgs...>                 \
        >::type                                                              \
    > inline explicit                                                        \
    class_(TaggedArg0 const& arg0, TaggedArgs const&... args)                \
      : BOOST_PARAMETER_PARENTHESIZED_TYPE(base)(                            \
            ::boost::parameter::compose(arg0, args...)                       \
        )                                                                    \
    {                                                                        \
    }
/**/

// Exapnds to a variadic constructor that is enabled if and only if all its
// arguments are tagged arguments.  The specified function must be able to
// take in the argument pack that this constructor passes on.
#define BOOST_PARAMETER_NO_SPEC_NO_BASE_CONSTRUCTOR(class_, func)            \
    template <                                                               \
        typename TaggedArg0                                                  \
      , typename ...TaggedArgs                                               \
      , typename = typename ::boost::enable_if<                              \
            ::boost::parameter                                               \
            ::are_tagged_arguments<TaggedArg0,TaggedArgs...>                 \
        >::type                                                              \
    > inline explicit                                                        \
    class_(TaggedArg0 const& arg0, TaggedArgs const&... args)                \
    {                                                                        \
        func(::boost::parameter::compose(arg0, args...));                    \
    }
/**/

#include <boost/parameter/aux_/preprocessor/nullptr.hpp>
#include <boost/preprocessor/control/expr_if.hpp>

// Exapnds to a variadic function that is enabled if and only if
// all its arguments are tagged arguments.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_OVERLOAD(name, impl, is_m, c)       \
    template <typename TaggedArg0, typename ...TaggedArgs>                   \
    BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(impl)                             \
    inline typename ::boost::lazy_enable_if<                                 \
        ::boost::parameter                                                   \
        ::are_tagged_arguments<TaggedArg0,TaggedArgs...>                     \
      , BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(                        \
            impl, c                                                          \
        )<TaggedArg0,TaggedArgs...>                                          \
    >::type BOOST_PARAMETER_MEMBER_FUNCTION_NAME(name)                       \
    (TaggedArg0 const& arg0, TaggedArgs const&... args)                      \
    BOOST_PP_EXPR_IF(c, const)                                               \
    {                                                                        \
        return BOOST_PP_EXPR_IF(is_m, this->)                                \
        BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_NAME(impl, c)(                 \
            static_cast<                                                     \
                typename BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(       \
                    impl, c                                                  \
                )<TaggedArg0,TaggedArgs...>::type(*)()                       \
            >(BOOST_PARAMETER_AUX_PP_NULLPTR)                                \
          , ::boost::parameter::compose(arg0, args...)                       \
        );                                                                   \
    }
/**/

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/preprocessor/impl/parenthesized_return_type.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

// Expands to the result metafunction for the specified no-spec function.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_HEAD(result, name, is_const)        \
    template <                                                               \
        BOOST_PP_ENUM_BINARY_PARAMS(                                         \
            BOOST_PARAMETER_COMPOSE_MAX_ARITY                                \
          , typename TaggedArg                                               \
          , = ::boost::parameter::void_ BOOST_PP_INTERCEPT                   \
        )                                                                    \
    >                                                                        \
    struct BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(name, is_const)      \
      : BOOST_PARAMETER_PARENTHESIZED_RETURN_TYPE(result)                    \
    {                                                                        \
    };
/**/

#include <boost/parameter/compose.hpp>
#include <boost/parameter/aux_/preprocessor/impl/parenthesized_type.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

#if defined(BOOST_NO_SFINAE)

// Exapnds to a tagged-argument constructor overload that passes the argument
// pack to the base class delegate constructor.
#define BOOST_PARAMETER_NO_SPEC_CONSTRUCTOR_OVERLOAD_Z(z, n, data)           \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename TaggedArg)>              \
    BOOST_PP_EXPR_IF(BOOST_PP_EQUAL(n, 1), explicit) inline                  \
    BOOST_PP_TUPLE_ELEM(2, 0, data)(                                         \
        BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, TaggedArg, const& arg)           \
    ) : BOOST_PARAMETER_PARENTHESIZED_TYPE(BOOST_PP_TUPLE_ELEM(2, 1, data))( \
            ::boost::parameter::compose(BOOST_PP_ENUM_PARAMS_Z(z, n, arg))   \
        )                                                                    \
    {                                                                        \
    }
/**/

// Exapnds to a tagged-argument constructor overload that passes the argument
// pack to the delegate function.
#define BOOST_PARAMETER_NO_SPEC_NO_BASE_CONSTRUCTOR_OVERLOAD_Z(z, n, data)   \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename TaggedArg)>              \
    BOOST_PP_EXPR_IF(BOOST_PP_EQUAL(n, 1), explicit) inline                  \
    BOOST_PP_TUPLE_ELEM(2, 0, data)(                                         \
        BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, TaggedArg, const& a)             \
    )                                                                        \
    {                                                                        \
        BOOST_PP_TUPLE_ELEM(2, 1, data)(                                     \
            ::boost::parameter::compose(BOOST_PP_ENUM_PARAMS_Z(z, n, a))     \
        );                                                                   \
    }
/**/

#include <boost/parameter/aux_/preprocessor/nullptr.hpp>

// Exapnds to a tagged-argument function overload.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_OVERLOAD_Z(z, n, data)              \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename TaggedArg)>              \
    BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(BOOST_PP_TUPLE_ELEM(4, 1, data))  \
    inline typename BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(            \
        BOOST_PP_TUPLE_ELEM(4, 1, data)                                      \
      , BOOST_PP_TUPLE_ELEM(4, 3, data)                                      \
    )<BOOST_PP_ENUM_PARAMS_Z(z, n, TaggedArg)>::type                         \
        BOOST_PARAMETER_MEMBER_FUNCTION_NAME(                                \
            BOOST_PP_TUPLE_ELEM(4, 0, data)                                  \
        )(BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, TaggedArg, const& arg))        \
        BOOST_PP_EXPR_IF(BOOST_PP_TUPLE_ELEM(4, 3, data), const)             \
    {                                                                        \
        return BOOST_PP_EXPR_IF(BOOST_PP_TUPLE_ELEM(4, 2, data), this->)     \
        BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_NAME(                          \
            BOOST_PP_TUPLE_ELEM(4, 1, data)                                  \
          , BOOST_PP_TUPLE_ELEM(4, 3, data)                                  \
        )(                                                                   \
            static_cast<                                                     \
                typename BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(       \
                    BOOST_PP_TUPLE_ELEM(4, 1, data)                          \
                  , BOOST_PP_TUPLE_ELEM(4, 3, data)                          \
                )<BOOST_PP_ENUM_PARAMS_Z(z, n, TaggedArg)>::type(*)()        \
            >(BOOST_PARAMETER_AUX_PP_NULLPTR)                                \
          , ::boost::parameter::compose(BOOST_PP_ENUM_PARAMS_Z(z, n, arg))   \
        );                                                                   \
    }
/**/

#else   // !defined(BOOST_NO_SFINAE)

#include <boost/parameter/are_tagged_arguments.hpp>
#include <boost/parameter/aux_/preprocessor/nullptr.hpp>
#include <boost/core/enable_if.hpp>

// Exapnds to a tagged-argument constructor overload that passes the argument
// pack to the base class delegate constructor.  This constructor is enabled
// if and only if all its arguments are tagged arguments.
#define BOOST_PARAMETER_NO_SPEC_CONSTRUCTOR_OVERLOAD_Z(z, n, data)           \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename TaggedArg)>              \
    BOOST_PP_EXPR_IF(BOOST_PP_EQUAL(n, 1), explicit) inline                  \
    BOOST_PP_TUPLE_ELEM(2, 0, data)(                                         \
        BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, TaggedArg, const& arg)           \
      , typename ::boost::enable_if<                                         \
            ::boost::parameter::are_tagged_arguments<                        \
                BOOST_PP_ENUM_PARAMS_Z(z, n, TaggedArg)                      \
            >                                                                \
        >::type* = BOOST_PARAMETER_AUX_PP_NULLPTR                            \
    ) : BOOST_PARAMETER_PARENTHESIZED_TYPE(BOOST_PP_TUPLE_ELEM(2, 1, data))( \
            ::boost::parameter::compose(BOOST_PP_ENUM_PARAMS_Z(z, n, arg))   \
        )                                                                    \
    {                                                                        \
    }
/**/

// Exapnds to a tagged-argument constructor overload that passes the argument
// pack to the delegate function.  This constructor is enabled if and only if
// all its arguments are tagged arguments.
#define BOOST_PARAMETER_NO_SPEC_NO_BASE_CONSTRUCTOR_OVERLOAD_Z(z, n, data)   \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename TaggedArg)>              \
    BOOST_PP_EXPR_IF(BOOST_PP_EQUAL(n, 1), explicit) inline                  \
    BOOST_PP_TUPLE_ELEM(2, 0, data)(                                         \
        BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, TaggedArg, const& a)             \
      , typename ::boost::enable_if<                                         \
            ::boost::parameter::are_tagged_arguments<                        \
                BOOST_PP_ENUM_PARAMS_Z(z, n, TaggedArg)                      \
            >                                                                \
        >::type* = BOOST_PARAMETER_AUX_PP_NULLPTR                            \
    )                                                                        \
    {                                                                        \
        BOOST_PP_TUPLE_ELEM(2, 1, data)(                                     \
            ::boost::parameter::compose(BOOST_PP_ENUM_PARAMS_Z(z, n, a))     \
        );                                                                   \
    }
/**/

// Exapnds to a function overload that is enabled if and only if
// all its arguments are tagged arguments.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_OVERLOAD_Z(z, n, data)              \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename TaggedArg)>              \
    BOOST_PARAMETER_MEMBER_FUNCTION_STATIC(BOOST_PP_TUPLE_ELEM(4, 1, data))  \
    inline typename ::boost::lazy_enable_if<                                 \
        ::boost::parameter                                                   \
        ::are_tagged_arguments<BOOST_PP_ENUM_PARAMS_Z(z, n, TaggedArg)>      \
      , BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(                        \
            BOOST_PP_TUPLE_ELEM(4, 1, data)                                  \
          , BOOST_PP_TUPLE_ELEM(4, 3, data)                                  \
        )<BOOST_PP_ENUM_PARAMS_Z(z, n, TaggedArg)>                           \
    >::type BOOST_PARAMETER_MEMBER_FUNCTION_NAME(                            \
        BOOST_PP_TUPLE_ELEM(4, 0, data)                                      \
    )(BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, TaggedArg, const& arg))            \
    BOOST_PP_EXPR_IF(BOOST_PP_TUPLE_ELEM(4, 3, data), const)                 \
    {                                                                        \
        return BOOST_PP_EXPR_IF(BOOST_PP_TUPLE_ELEM(4, 2, data), this->)     \
        BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_NAME(                          \
            BOOST_PP_TUPLE_ELEM(4, 1, data)                                  \
          , BOOST_PP_TUPLE_ELEM(4, 3, data)                                  \
        )(                                                                   \
            static_cast<                                                     \
                typename BOOST_PARAMETER_NO_SPEC_FUNCTION_RESULT_NAME(       \
                    BOOST_PP_TUPLE_ELEM(4, 1, data)                          \
                  , BOOST_PP_TUPLE_ELEM(4, 3, data)                          \
                )<BOOST_PP_ENUM_PARAMS_Z(z, n, TaggedArg)>::type(*)()        \
            >(BOOST_PARAMETER_AUX_PP_NULLPTR)                                \
          , ::boost::parameter::compose(BOOST_PP_ENUM_PARAMS_Z(z, n, arg))   \
        );                                                                   \
    }
/**/

#endif  // BOOST_NO_SFINAE

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

// Emulates a variadic constructor that is enabled if and only if all its
// arguments are tagged arguments.  The enclosing class must inherit from the
// specified base class, which in turn must implement a constructor that takes
// in the argument pack that this one passes on.
#define BOOST_PARAMETER_NO_SPEC_CONSTRUCTOR(class_, base)                    \
    BOOST_PP_REPEAT_FROM_TO(                                                 \
        1                                                                    \
      , BOOST_PP_INC(BOOST_PARAMETER_COMPOSE_MAX_ARITY)                      \
      , BOOST_PARAMETER_NO_SPEC_CONSTRUCTOR_OVERLOAD_Z                       \
      , (class_, base)                                                       \
    )
/**/

// Emulates a variadic constructor that is enabled if and only if all its
// arguments are tagged arguments.  The specified function must be able to
// take in the argument pack that this constructor passes on.
#define BOOST_PARAMETER_NO_SPEC_NO_BASE_CONSTRUCTOR(class_, func)            \
    BOOST_PP_REPEAT_FROM_TO(                                                 \
        1                                                                    \
      , BOOST_PP_INC(BOOST_PARAMETER_COMPOSE_MAX_ARITY)                      \
      , BOOST_PARAMETER_NO_SPEC_NO_BASE_CONSTRUCTOR_OVERLOAD_Z               \
      , (class_, func)                                                       \
    )
/**/

// Emulates a variadic function that is enabled if and only if
// all its arguments are tagged arguments.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_OVERLOAD(name, impl, is_m, c)       \
    BOOST_PP_REPEAT_FROM_TO(                                                 \
        1                                                                    \
      , BOOST_PP_INC(BOOST_PARAMETER_COMPOSE_MAX_ARITY)                      \
      , BOOST_PARAMETER_NO_SPEC_FUNCTION_OVERLOAD_Z                          \
      , (name, impl, is_m, c)                                                \
    )
/**/

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // include guard


/* no_spec_overloads.hpp
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
*/