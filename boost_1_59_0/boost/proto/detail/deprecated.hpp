///////////////////////////////////////////////////////////////////////////////
/// \file deprecated.hpp
/// Definition of the deprecated BOOST_PROTO_DEFINE_FUCTION_TEMPLATE and
/// BOOST_PROTO_DEFINE_VARARG_FUCTION_TEMPLATE macros
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_DEPRECATED_HPP_EAN_11_25_2008
#define BOOST_PROTO_DETAIL_DEPRECATED_HPP_EAN_11_25_2008

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/to_list.hpp>
#include <boost/preprocessor/logical/and.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/to_tuple.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/pop_back.hpp>
#include <boost/preprocessor/seq/push_back.hpp>
#include <boost/preprocessor/seq/push_front.hpp>
#include <boost/preprocessor/list/for_each_i.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/proto/proto_fwd.hpp>

/// INTERNAL ONLY
///
#define BOOST_PROTO_VARARG_TEMPLATE_AUX_(R, DATA, I, ELEM)                                      \
    (ELEM BOOST_PP_CAT(BOOST_PP_CAT(X, DATA), BOOST_PP_CAT(_, I)))                              \
    /**/

/// INTERNAL ONLY
///
#define BOOST_PROTO_VARARG_TEMPLATE_YES_(R, DATA, I, ELEM)                                      \
    BOOST_PP_LIST_FOR_EACH_I_R(                                                                 \
        R                                                                                       \
      , BOOST_PROTO_VARARG_TEMPLATE_AUX_                                                        \
      , I                                                                                       \
      , BOOST_PP_TUPLE_TO_LIST(                                                                 \
            BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(ELEM))                                               \
          , BOOST_PP_SEQ_TO_TUPLE(BOOST_PP_SEQ_TAIL(ELEM))                                      \
        )                                                                                       \
    )                                                                                           \
    /**/

/// INTERNAL ONLY
///
#define BOOST_PROTO_VARARG_TEMPLATE_NO_(R, DATA, I, ELEM)                                       \
    /**/

/// INTERNAL ONLY
///
#define BOOST_PROTO_VARARG_TEMPLATE_(R, DATA, I, ELEM)                                          \
    BOOST_PP_IF(                                                                                \
        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(ELEM))                                                   \
      , BOOST_PROTO_VARARG_TEMPLATE_YES_                                                        \
      , BOOST_PROTO_VARARG_TEMPLATE_NO_                                                         \
    )(R, DATA, I, ELEM)                                                                         \
    /**/

/// INTERNAL ONLY
///
#define BOOST_PROTO_VARARG_TYPE_AUX_(R, DATA, I, ELEM)                                          \
    (BOOST_PP_CAT(BOOST_PP_CAT(X, DATA), BOOST_PP_CAT(_, I)))                                   \
    /**/

/// INTERNAL ONLY
///
#define BOOST_PROTO_TEMPLATE_PARAMS_YES_(R, DATA, I, ELEM)                                      \
    <                                                                                           \
        BOOST_PP_SEQ_ENUM(                                                                      \
            BOOST_PP_LIST_FOR_EACH_I_R(                                                         \
                R                                                                               \
              , BOOST_PROTO_VARARG_TYPE_AUX_                                                    \
              , I                                                                               \
              , BOOST_PP_TUPLE_TO_LIST(                                                         \
                    BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(ELEM))                                       \
                  , BOOST_PP_SEQ_TO_TUPLE(BOOST_PP_SEQ_TAIL(ELEM))                              \
                )                                                                               \
            )                                                                                   \
        )                                                                                       \
    >                                                                                           \
    /**/

/// INTERNAL ONLY
///
#define BOOST_PROTO_TEMPLATE_PARAMS_NO_(R, DATA, I, ELEM)                                       \
    /**/

/// INTERNAL ONLY
///
#define BOOST_PROTO_VARARG_TYPE_(R, DATA, I, ELEM)                                              \
    BOOST_PP_COMMA_IF(I)                                                                        \
    BOOST_PP_SEQ_HEAD(ELEM)                                                                     \
    BOOST_PP_IF(                                                                                \
        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(ELEM))                                                   \
      , BOOST_PROTO_TEMPLATE_PARAMS_YES_                                                        \
      , BOOST_PROTO_TEMPLATE_PARAMS_NO_                                                         \
    )(R, DATA, I, ELEM) BOOST_PP_EXPR_IF(BOOST_PP_GREATER(I, 1), const)                         \
    /**/

/// INTERNAL ONLY
///
#define BOOST_PROTO_VARARG_AS_EXPR_(R, DATA, I, ELEM)                                           \
    BOOST_PP_EXPR_IF(                                                                           \
        BOOST_PP_GREATER(I, 1)                                                                  \
      , ((                                                                                      \
            BOOST_PP_SEQ_HEAD(ELEM)                                                             \
            BOOST_PP_IF(                                                                        \
                BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(ELEM))                                           \
              , BOOST_PROTO_TEMPLATE_PARAMS_YES_                                                \
              , BOOST_PROTO_TEMPLATE_PARAMS_NO_                                                 \
            )(R, DATA, I, ELEM)()                                                               \
        ))                                                                                      \
    )                                                                                           \
    /**/

/// INTERNAL ONLY
///
#define BOOST_PROTO_VARARG_AS_CHILD_(Z, N, DATA)                                                \
    (BOOST_PP_CAT(DATA, N))                                                                     \
    /**/

/// INTERNAL ONLY
///
#define BOOST_PROTO_SEQ_PUSH_FRONT(SEQ, ELEM)                                                   \
    BOOST_PP_SEQ_POP_BACK(BOOST_PP_SEQ_PUSH_FRONT(BOOST_PP_SEQ_PUSH_BACK(SEQ, _dummy_), ELEM))  \
    /**/

/// INTERNAL ONLY
///
#define BOOST_PROTO_VARARG_AS_PARAM_(Z, N, DATA)                                                \
    (BOOST_PP_CAT(DATA, N))                                                                     \
    /**/

/// INTERNAL ONLY
///
#define BOOST_PROTO_VARARG_FUN_(Z, N, DATA)                                                     \
    template<                                                                                   \
        BOOST_PP_SEQ_ENUM(                                                                      \
            BOOST_PP_SEQ_FOR_EACH_I(                                                            \
                BOOST_PROTO_VARARG_TEMPLATE_, ~                                                 \
              , BOOST_PP_SEQ_PUSH_FRONT(                                                        \
                    BOOST_PROTO_SEQ_PUSH_FRONT(                                                 \
                        BOOST_PP_TUPLE_ELEM(4, 2, DATA)                                         \
                      , (BOOST_PP_TUPLE_ELEM(4, 3, DATA))                                       \
                    )                                                                           \
                  , BOOST_PP_TUPLE_ELEM(4, 1, DATA)                                             \
                )                                                                               \
            )                                                                                   \
            BOOST_PP_REPEAT_ ## Z(N, BOOST_PROTO_VARARG_AS_PARAM_, typename A)                  \
        )                                                                                       \
    >                                                                                           \
    typename boost::proto::result_of::make_expr<                                                \
        BOOST_PP_SEQ_FOR_EACH_I(                                                                \
            BOOST_PROTO_VARARG_TYPE_, ~                                                         \
          , BOOST_PP_SEQ_PUSH_FRONT(                                                            \
                BOOST_PROTO_SEQ_PUSH_FRONT(                                                     \
                    BOOST_PP_TUPLE_ELEM(4, 2, DATA)                                             \
                  , (BOOST_PP_TUPLE_ELEM(4, 3, DATA))                                           \
                )                                                                               \
              , BOOST_PP_TUPLE_ELEM(4, 1, DATA)                                                 \
            )                                                                                   \
        )                                                                                       \
        BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(Z, N, A, const & BOOST_PP_INTERCEPT)             \
    >::type const                                                                               \
    BOOST_PP_TUPLE_ELEM(4, 0, DATA)(BOOST_PP_ENUM_BINARY_PARAMS_Z(Z, N, A, const &a))           \
    {                                                                                           \
        return boost::proto::detail::make_expr_<                                                \
            BOOST_PP_SEQ_FOR_EACH_I(                                                            \
                BOOST_PROTO_VARARG_TYPE_, ~                                                     \
              , BOOST_PP_SEQ_PUSH_FRONT(                                                        \
                    BOOST_PROTO_SEQ_PUSH_FRONT(                                                 \
                        BOOST_PP_TUPLE_ELEM(4, 2, DATA)                                         \
                      , (BOOST_PP_TUPLE_ELEM(4, 3, DATA))                                       \
                    )                                                                           \
                  , BOOST_PP_TUPLE_ELEM(4, 1, DATA)                                             \
                )                                                                               \
            )                                                                                   \
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(Z, N, A, const & BOOST_PP_INTERCEPT)         \
        >()(                                                                                    \
            BOOST_PP_SEQ_ENUM(                                                                  \
                BOOST_PP_SEQ_FOR_EACH_I(                                                        \
                    BOOST_PROTO_VARARG_AS_EXPR_, ~                                              \
                  , BOOST_PP_SEQ_PUSH_FRONT(                                                    \
                        BOOST_PROTO_SEQ_PUSH_FRONT(                                             \
                            BOOST_PP_TUPLE_ELEM(4, 2, DATA)                                     \
                          , (BOOST_PP_TUPLE_ELEM(4, 3, DATA))                                   \
                        )                                                                       \
                      , BOOST_PP_TUPLE_ELEM(4, 1, DATA)                                         \
                    )                                                                           \
                )                                                                               \
                BOOST_PP_REPEAT_ ## Z(N, BOOST_PROTO_VARARG_AS_CHILD_, a)                       \
            )                                                                                   \
        );                                                                                      \
    }                                                                                           \
    /**/

/// \code
/// BOOST_PROTO_DEFINE_FUNCTION_TEMPLATE(
///     1
///   , construct
///   , boost::proto::default_domain
///   , (boost::proto::tag::function)
///   , ((op::construct)(typename)(int))
/// )
/// \endcode
#define BOOST_PROTO_DEFINE_FUNCTION_TEMPLATE(ARGCOUNT, NAME, DOMAIN, TAG, BOUNDARGS)            \
    BOOST_PP_REPEAT_FROM_TO(                                                                    \
        ARGCOUNT                                                                                \
      , BOOST_PP_INC(ARGCOUNT)                                                                  \
      , BOOST_PROTO_VARARG_FUN_                                                                 \
      , (NAME, TAG, BOUNDARGS, DOMAIN)                                                          \
    )\
    /**/

/// \code
/// BOOST_PROTO_DEFINE_VARARG_FUNCTION_TEMPLATE(
///     construct
///   , boost::proto::default_domain
///   , (boost::proto::tag::function)
///   , ((op::construct)(typename)(int))
/// )
/// \endcode
#define BOOST_PROTO_DEFINE_VARARG_FUNCTION_TEMPLATE(NAME, DOMAIN, TAG, BOUNDARGS)               \
    BOOST_PP_REPEAT(                                                                            \
        BOOST_PP_SUB(BOOST_PP_INC(BOOST_PROTO_MAX_ARITY), BOOST_PP_SEQ_SIZE(BOUNDARGS))         \
      , BOOST_PROTO_VARARG_FUN_                                                                 \
      , (NAME, TAG, BOUNDARGS, DOMAIN)                                                          \
    )                                                                                           \
    /**/

#endif

/* deprecated.hpp
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
*/