// Copyright David Abrahams, Daniel Wallin 2003.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// No include guard.  This file is intended for multiple inclusion.

#define BOOST_PARAMETER_right_angle(z, n, _) >
/**/

#define BOOST_PARAMETER_satisfies_end(z, n, false_t) ,false_t>
/**/

#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/cat.hpp>

// Generates:
//
//   make<
//       parameter_spec##0, argument_type##0
//     , make<
//           parameter_spec##1, argument_type##1
//         , ... boost::mpl::identity<boost::parameter::aux::empty_arg_list>
//    ...>
//   >
#define BOOST_PARAMETER_make_arg_list(z, n, names)                           \
    BOOST_PP_SEQ_ELEM(0, names)<                                             \
        BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(1, names), n),                        \
        BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(2, names), n),
/**/

#include <boost/parameter/aux_/void.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#define BOOST_PARAMETER_build_arg_list(n, make, param_spec, arg_type)        \
    BOOST_PP_REPEAT(                                                         \
        n, BOOST_PARAMETER_make_arg_list, (make)(param_spec)(arg_type)       \
    )                                                                        \
    ::boost::mpl::identity< ::boost::parameter::void_>                       \
    BOOST_PP_REPEAT(n, BOOST_PARAMETER_right_angle, _)
/**/

#define BOOST_PARAMETER_make_deduced_list(z, n, names)                       \
    BOOST_PP_SEQ_ELEM(0, names)<BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(1, names), n),
/**/

#define BOOST_PARAMETER_build_deduced_list(n, make, parameter_spec)          \
    BOOST_PP_REPEAT(                                                         \
        n, BOOST_PARAMETER_make_deduced_list, (make)(parameter_spec)         \
    )                                                                        \
    ::boost::mpl::identity< ::boost::parameter::void_>                       \
    BOOST_PP_REPEAT(n, BOOST_PARAMETER_right_angle, _)
/**/

#define BOOST_PARAMETER_forward_typedef(z, n, names)                         \
    typedef BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(0, names), n)                     \
    BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(1, names), n);
/**/

#define BOOST_PARAMETER_template_args(z, n, prefix)                          \
    typename BOOST_PP_CAT(prefix, n) = ::boost::parameter::void_
/**/

#include <boost/mpl/pair.hpp>

#if (0 < BOOST_PARAMETER_EXPONENTIAL_OVERLOAD_THRESHOLD_ARITY)

#include <boost/parameter/aux_/pack/item.hpp>
#include <boost/preprocessor/control/iif.hpp>

#define BOOST_PARAMETER_make_arg_items_R(r, prefix, i, elem)                 \
    ::boost::parameter::aux::item<BOOST_PP_CAT(prefix, i),                   \
    BOOST_PP_CAT(A, i) BOOST_PP_IIF(elem, &, const&),
/**/

#include <boost/parameter/aux_/pack/make_arg_list.hpp>
#include <boost/parameter/aux_/pack/tag_keyword_arg.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/size.hpp>

#define BOOST_PARAMETER_function_call_arg_list_R(r, seq)                     \
    ::boost::parameter::aux::make_arg_list<                                  \
        BOOST_PP_SEQ_FOR_EACH_I_R(                                           \
            r, BOOST_PARAMETER_make_arg_items_R, PS, seq                     \
        )                                                                    \
        ::boost::parameter::void_                                            \
        BOOST_PP_REPEAT(                                                     \
            BOOST_PP_SEQ_SIZE(seq), BOOST_PARAMETER_right_angle, _           \
        )                                                                    \
      , deduced_list                                                         \
      , ::boost::parameter::aux::tag_keyword_arg                             \
    >
/**/

#include <boost/preprocessor/arithmetic/sub.hpp>

#define BOOST_PARAMETER_function_call_arg_pack_init(z, n, limit)             \
    BOOST_PP_CAT(a, BOOST_PP_SUB(limit, n))
/**/

#include <boost/parameter/aux_/preprocessor/binary_seq_to_args.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/seq/seq.hpp>

#define BOOST_PARAMETER_function_call_op_overload_R(r, seq)                  \
    template <                                                               \
        BOOST_PP_ENUM_PARAMS(                                                \
            BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq))                             \
          , typename A                                                       \
        )                                                                    \
    >                                                                        \
    inline typename ::boost::mpl::first<                                     \
        typename BOOST_PARAMETER_function_call_arg_list_R(                   \
            r, BOOST_PP_SEQ_TAIL(seq)                                        \
        )::type                                                              \
    >::type                                                                  \
        operator()(                                                          \
            BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARGS(                       \
                BOOST_PP_SEQ_TAIL(seq), (A)(a)                               \
            )                                                                \
        ) const                                                              \
    {                                                                        \
        typedef typename BOOST_PARAMETER_function_call_arg_list_R(           \
            r, BOOST_PP_SEQ_TAIL(seq)                                        \
        )::type result;                                                      \
        typedef typename ::boost::mpl::first<result>::type result_type;      \
        typedef typename ::boost::mpl::second<result>::type error;           \
        error();                                                             \
        return result_type(                                                  \
            BOOST_PP_ENUM(                                                   \
                BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq))                         \
              , BOOST_PARAMETER_function_call_arg_pack_init                  \
              , BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq)))           \
            )                                                                \
            BOOST_PP_ENUM_TRAILING_PARAMS(                                   \
                BOOST_PP_SUB(                                                \
                    BOOST_PARAMETER_COMPOSE_MAX_ARITY                        \
                  , BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq))                     \
                )                                                            \
              , ::boost::parameter::aux::void_reference() BOOST_PP_INTERCEPT \
            )                                                                \
        );                                                                   \
    }
/**/

#endif  // exponential overloads

#include <boost/parameter/aux_/pack/satisfies.hpp>
#include <boost/mpl/eval_if.hpp>

#define BOOST_PARAMETER_satisfies_begin(z, n, prefix)                        \
    ::boost::mpl::eval_if<                                                   \
        ::boost::parameter::aux::satisfies_requirements_of<                  \
            typename ::boost::mpl::first<ArgumentPackAndError>::type         \
          , BOOST_PP_CAT(prefix, n)                                          \
        >,
/**/


/* no_perfect_forwarding_begin.hpp
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
*/