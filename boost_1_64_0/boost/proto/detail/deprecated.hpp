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
eqk/0GCbvnEDWOPwzjArB7Y/24h/9oZFWWK9iV37924Sy8EuP2/yOG9YdgsoA9NxWkrs/W8F5SnxElK+J+LeGsrANj1VjILYCo2hfWeAGcJkIG5/Cb6nfKip1WfRxfXkWhoD/P6PSTBHkHOJNA/b/tjHQ/nsJKONz3V8gMPf8LqyrH0J5m8CYKIZ+/YOmFoMNltvLd6lpfI9+KaeHpEArTXKrBS21sxIGYTxMtt2uPV4XMOVE8VOYi1Ac289OunkndxY51WQ6YhZh2Xq+Fzp/ASEZf8WFnTYoH9MsH2CDdJugmoBgkycg7iyhThrA86L4tPlzr9Dcvg2/9ZSVm1823Y2kDwiYwVHsmumiURAas0+6wU9yfpOBC5NOJ/etBzgVTbbV+t3W+6DB/vzSXfDu23Dxw6t3C36zDwlflveVVzTkKMOzrshLAzKRK96S5FrspNOa1Gxh4/Xy+soXN0wb3hvRONTXtiHUysgiYllxnGZP0JpXLRBCy4bzVQSG4bYHB9DONSnN6KSVehSXRF8phW65sUXrrnmmgugF1pWOxvq/TrSQ/9733Ct2e683kdkuW9UbweqpKbGLQH0qREDKi7S5BG7hNu+sbS/4ME7LZuOyUMIa5MoYVoatI+c4Fs8y/F6/vZifO9upOM17Kj8lvHPsgzfWDvEvf61ZXmUWTPujYsyeE1OmREQ95Yvw/JpLIGMniubGFfpLqlsbb2aNecIad6z+I5BXYb3mYcO5clLLG7ROJTwVL5lME4yHX8Rx79ujOs9awBhzkFGAqXuFNMDQUJXtnKW7RzfOrJPVBUETXcMFHDT+ebFhZR+EAXjEPvjmmJPCxZMG4Rsm//ubSf55rK5z+HfbrfcZxf95bby3n543OvwG/0D1SMSTMp/sXm0u7t5mn7HdAfwYnWEv8/g9/bOC+E33hfHce/fG+vcupLzKNzwesN3DAhlUAf4xlJGrrlyrReB4aolGYU02P2twg4M0pLIAjnOKqX1KBd87SCt/8whN18sRJ75XlF3BQ9QjffWsgAYO9HcvTDDXcN6flnUY4JTtTcNG+dhPqhRr43wqCv1ypiea7YRt2cZIm5Mg+e9/qZyzaomCKV1HYUv3OfnEILsMoNupaV0LhvVNnWtHcRhJyHFiR3vBoWvHfMh1Nb0DjcL1DuM1jVJqQFNGMVHPi3ocGZd2/BG1tlGfW+usR4M3E8NytoUl9es9U0tuPUMo6pkIyj4Y4ceftCSQifzmWIcZ0GkpRFtz/zJNprJzbdL1MhM4khegYY9H0yXJocsv01/76VlHKzZIMRRnKdPWcXz6MfnwMEYPxTP3wSTkifFYyu5RKbQWnDAwSs1wA8xsyA2VYpfBlVCsUFdYDHOPVN9JW0raXqx2aCAYoXcLVR/nPmW67+5HHddNXGsaj0QGysqU8GwIiD6xqBnvP+by7XUBNfrvlMod18dzl+6qLBhp49HPcB2ySN0zgrZ234JHehqVmXjWtwr2iFY3anKB+cRHxi7MTLivqzAlcxWQVgjERWY9gVch28miIt6Simddtb/12d8XBZUP/f5oi2GKcWddIEX59fkALjAa2eTFKenHuZ5J58tbxnpl1RtuzDo02Ch7Ufl4UugY6hWIXRqvMMKOpq1wOkr0bBsr3h+c/Kb6oiGVbpynegGGrjK4KTB14+hLQbf4Qs6gbWt7Brd6WV9QorjrsFdunuHc+NjpLzgd5v7vqc0vKAyyN9B30Oc6effUdfTSDdDSTLuy265NE/V4Esd79b7YBvgciV5ij5zXVoGF+xQtndDKCNHBZFv73+TXBYRoRguuyFX4bffUL4feWeVl84tzWsWGbuU1Gw150t5FJAjb6k=
*/