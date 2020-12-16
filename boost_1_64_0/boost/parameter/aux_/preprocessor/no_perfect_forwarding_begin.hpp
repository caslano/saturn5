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
2MBsyO5l/7TIFVP6znY4mEJbPi5xOjnZAvnk1/NDEt7HsR2rrLTHbZT9wzmR9ujLCy6JtMb0rt2rz0Kbe1jtj6y95uUd6Mi7xrR/XdXyeUtruGFNtLuTjZE9/TZjflOyK9R2PdFneiAdSdv1119ZMXnmnIp62gaTQllWtGJVfZXcjkfqRwgtHmtBwxrHdKoerQuUA3/ZN9uOZa/x7fVRny9s/9uVaB5JC3kkLUZZcU787HNK3i+Lrv+t8/C1eDgna9aF95+K5V0ubjyRLGioWii5rlBVVgr7fk1qt4yc92gy516f7NS27R6nkMoT0mgkrT4xbfbaxSIzwHnd1/bTOqO9tB7LbVuX/kJdarbT6lSP2rdjc5p1qPk06lBCvlzrj3ltqVWNC7QOzcdVU392R/IbXng8WiYV82+vqJm3nP2WyEOt38iDeJN+Xc/5eyJ7Oc8DOY62QLfdN97aW/TUNtQ52oG47vdE3eGTEj6VfirHsS9VeSmfskiO7Wthq4SVU/bZ7a4DXay2Dee7a2K+1c7khTDJi1N/Sh7G5D8v57Ssl3rE96/V8j9xIuCqgixlPrRcyiFyPXN/zrTXqB0p8R3tji73a1IBHC3hWY7lgGxafXUqz4uXad4XFtjfANiswZblkbzXL6u4/rqZ5RXl110zc+rkmdOvuTr852XTr5xqrIt/Xr60vWVua/+WG3kvk7hSTI551bh227u2wEo536SDPJIOI99l4sf5EvLdq0vbfFcXcy/Zfr5Zlz61fFcm5OWT+aeXl3C6Z2i6tzukewXlVdtuullXvKJmVXW1ZaenNa/99Jg2Ky9se+56zt3Y/rlXLY+2m97JbdaYYLNvpJBGu973VpslpHtaV+c63txuumtX1S9Jrayb06jjzQl5/FYaeUynjk8qapvvVeS7pd183zavelVVSuUV0RXbC4C14heuccl3S0K+n0gj36SjTb4bLPz0fOZ92anuEQ0v6VzMF3F3F3I90nzXV1fMW7hQP89aUlVdvcK+majgzqLNvU9Y6aMiW6b7UUZ1TYi/ttr5s/f/sPcWPSphj3Htp+fHOV5vTVv67WuE87VV4xbYdl8+b004usbPM+Lnmbq1LnPXUV1j7O/QKuGHZP/IW7Dme3DGWuyCYr1WvSBxH7HO567lFtwGK8+2y4sS9nm0qCyrOOfqfhWV16oNY/cDXMtj188aCQ/JGMqU8Bg5CTuGYCjrvBDfDBl9gj6DabyZxHtax1Oygv2DM7JyQt7CSJyorrXEeSGsq0Pj4yFfdqwOqq5cjr2RezJc+vuicmzue2Lfg1CO9nW3CL88u95qeSXU3XuLIyfZpie7T+vukWvNuquf1rWtu+3eC6PHqY5KuR6VsGZrICMUs3EOdRT51OvokWvTq6O2brMsUtjL5WyXhYx76N4cklYP/jAAl+DXcp1dFjwsViyft6wq7tmpuM1zRkV9Qx1P5oRpO1Edq+z8q59t20XS765YRfrsvYOmX6/vgBzKxZTlPln2T6g2xp6el/Cv8IzRRfWx94/4dTBk5Bpi9wmflPBnrPPI/TusfnybNsLeI6hJ0lJq3tvbexOXStgcJLzWWJzmWc/3JGnSPsi2T2zv5M9KnJNWf+lhPDJmvZk2MboX35ARIRTIit2/aNuNxplLnD+G4+SuNe4f4+M0Eud4OE5O41b7+pugZydxzutCnI6Nr5r3bmac/dE4uY0PtonDsU/r74uFwnafcXKtQP59Yjerqq6O+Fqn9fkxsR7Z10DqCeFaT1RG7wfkmedZsSd2LdL7yOhaNfqC6PsEdoLfgesLZc631m3G8erqq9yvkpbjdXL5zPDxKPu55u9ynO3UF+m5PInPU3Y=
*/