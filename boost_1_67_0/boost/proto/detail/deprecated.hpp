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