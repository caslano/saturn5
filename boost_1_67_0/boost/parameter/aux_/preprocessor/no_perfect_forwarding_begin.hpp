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