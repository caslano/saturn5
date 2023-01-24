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
c8xD8pHRvOP0GNKqpIgD00t/U3fn+30HmICCrz8bSbVG05Ojl4hlVG2V+D31Ifsh/Bn+TK6qVeU0w35EcZj86MRq6VUjQgj3J+P5qzZlro/pgkVhdYSvZWP83bVrQWWIg7GmpRn2IpYnbwcmXKA+edWuWhxb04R8fneaxfnxYoSD3O7LtUoCdI2TR/krW3KNkUlVJjHHxs21xfQBs3s64odhD78u9uEI0d1u04nIiWoefvMTqTGbMYEeNZ+WKiMA22rfyORvnJ1FUFxRGoWDO4TgwSY4Ibh7gBDc3Qnu7i4JFiS407i7e+Pu7o1D49I4TY9VzWZqZqpm8Rbv7d+9df7vP+eYd4epHTkeY1X2My9EJPojv7zH8PRPcX1QePb1QQ5QxqiuiK6XHHmfrzQrunu2M71XWjMYq6zkSOJ/Arbf9gSTP1PwwZigpCcURYElniov/rvOg4EzOGBRsBTE9BkNSqR7Agbi/riKB/Ssk8mirm4V3LrBCSG/b+lWIrKOCJBN5cgPto0gOsFln+hdudu+xSwMwKVXYoRi4kqj5RjlgobfOLxlYiqc5QZcxlw+E2goVszi9xA4RoH5rr9hTUkb9o+ne3sLESTnZh26v/oVRgg5c5rEanMrLtiwR4mMS93kKMze8IkmswtoTj2RZE3ipQPmD3CdkQOFHyKGolEHGAPzZY4TmQWcJNXo44EWkNhWqrK0MW7h9Kjg
*/