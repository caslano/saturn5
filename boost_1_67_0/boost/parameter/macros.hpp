// Copyright David Abrahams, Daniel Wallin 2003.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_MACROS_050412_HPP
#define BOOST_PARAMETER_MACROS_050412_HPP

#include <boost/parameter/config.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#if !defined(BOOST_NO_SFINAE) && \
    !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x592))

#define BOOST_PARAMETER_MATCH_TYPE(n, param)                                 \
  , typename param::match<BOOST_PP_ENUM_PARAMS(n, T)>::type kw = param()
/**/

#define BOOST_PARAMETER_MATCH_TYPE_Z(z, n, param)                            \
  , typename param::match<BOOST_PP_ENUM_PARAMS_Z(z, n, T)>::type kw = param()
/**/

#else   // SFINAE disbled, or Borland workarounds needed.

#define BOOST_PARAMETER_MATCH_TYPE(n, param) , param kw = param()
/**/

#define BOOST_PARAMETER_MATCH_TYPE_Z(z, n, param) , param kw = param()
/**/

#endif  // SFINAE enabled, not Borland.

#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/cat.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#define BOOST_PARAMETER_FUN_0(z, n, params)                                  \
    BOOST_PP_TUPLE_ELEM(3, 0, params) BOOST_PP_TUPLE_ELEM(3, 1, params)()    \
    {                                                                        \
        return BOOST_PP_CAT(                                                 \
            BOOST_PP_TUPLE_ELEM(3, 1, params)                                \
          , _with_named_params                                               \
        )(BOOST_PP_TUPLE_ELEM(3, 2, params)()());                            \
    }
/**/

#include <utility>

#define BOOST_PARAMETER_FUN_DECL_PARAM(z, n, p)                              \
    ::std::forward<BOOST_PP_CAT(T, n)>(BOOST_PP_CAT(p, n))
/**/

#include <boost/preprocessor/repetition/enum.hpp>

#define BOOST_PARAMETER_FUN_DEFN_1(z, n, params)                             \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename T)>                      \
    BOOST_PP_TUPLE_ELEM(3, 0, params)                                        \
        BOOST_PP_TUPLE_ELEM(3, 1, params)(                                   \
            BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, T, && p)                     \
            BOOST_PARAMETER_MATCH_TYPE_Z(                                    \
                z, n, BOOST_PP_TUPLE_ELEM(3, 2, params)                      \
            )                                                                \
        )                                                                    \
    {                                                                        \
        return BOOST_PP_CAT(                                                 \
            BOOST_PP_TUPLE_ELEM(3, 1, params)                                \
          , _with_named_params                                               \
        )(                                                                   \
            kw(                                                              \
                BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                             \
                    n, BOOST_PARAMETER_FUN_DECL_PARAM, p                     \
                )                                                            \
            )                                                                \
        );                                                                   \
    }
/**/

#define BOOST_PARAMETER_FUN_DECL(z, n, params)                               \
    BOOST_PP_IF(                                                             \
        n                                                                    \
      , BOOST_PARAMETER_FUN_DEFN_1                                           \
      , BOOST_PARAMETER_FUN_0                                                \
    )(z, n, params)
/**/

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#define BOOST_PARAMETER_FUN_DEFN_0(z, n, params)                             \
    template <BOOST_PP_ENUM_PARAMS_Z(z, n, typename T)>                      \
    BOOST_PP_TUPLE_ELEM(3, 0, params)                                        \
        BOOST_PP_TUPLE_ELEM(3, 1, params)(                                   \
            BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, T, const& p)                 \
            BOOST_PARAMETER_MATCH_TYPE_Z(                                    \
                z, n, BOOST_PP_TUPLE_ELEM(3, 2, params)                      \
            )                                                                \
        )                                                                    \
    {                                                                        \
        return BOOST_PP_CAT(                                                 \
            BOOST_PP_TUPLE_ELEM(3, 1, params)                                \
          , _with_named_params                                               \
        )(kw(BOOST_PP_ENUM_PARAMS_Z(z, n, p)));                              \
    }
/**/

#include <boost/preprocessor/seq/seq.hpp>

#define BOOST_PARAMETER_FUN_0(z, n, seq)                                     \
    BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq)))     \
    BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq)))()   \
    {                                                                        \
        return BOOST_PP_CAT(                                                 \
            BOOST_PP_TUPLE_ELEM(                                             \
                3, 1, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))              \
            )                                                                \
          , _with_named_params                                               \
        )(                                                                   \
        BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(seq))) \
        ()()                                                                 \
        );                                                                   \
    }
/**/

#include <boost/parameter/aux_/preprocessor/binary_seq_to_args.hpp>
#include <boost/preprocessor/seq/size.hpp>

#define BOOST_PARAMETER_FUN_DEFN_R(r, seq)                                   \
    template <                                                               \
        BOOST_PP_ENUM_PARAMS(                                                \
            BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL(seq))                        \
          , typename T                                                       \
        )                                                                    \
    > BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_SEQ_HEAD(seq))                      \
        BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_SEQ_HEAD(seq))(                   \
            BOOST_PARAMETER_AUX_PP_BINARY_SEQ_TO_ARGS(                       \
                BOOST_PP_SEQ_TAIL(seq), (T)(p)                               \
            )                                                                \
            BOOST_PARAMETER_MATCH_TYPE(                                      \
                BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL(seq))                    \
              , BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_HEAD(seq))            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        return BOOST_PP_CAT(                                                 \
            BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_SEQ_HEAD(seq))                \
          , _with_named_params                                               \
        )(                                                                   \
            kw(                                                              \
                BOOST_PP_ENUM_PARAMS(                                        \
                    BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL(seq)), p             \
                )                                                            \
            )                                                                \
        );                                                                   \
    }
/**/

#include <boost/parameter/aux_/preprocessor/binary_seq_for_each.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

#define BOOST_PARAMETER_FUN_DEFN_1(z, n, params)                             \
    BOOST_PP_IF(                                                             \
        n                                                                    \
      , BOOST_PARAMETER_AUX_PP_BINARY_SEQ_FOR_EACH_Z                         \
      , BOOST_PARAMETER_FUN_0                                                \
    )(z, n, (BOOST_PARAMETER_FUN_DEFN_R)(params))
/**/

#include <boost/preprocessor/comparison/less.hpp>

#define BOOST_PARAMETER_FUN_DECL(z, n, params)                               \
    BOOST_PP_CAT(                                                            \
        BOOST_PARAMETER_FUN_DEFN_                                            \
      , BOOST_PP_LESS(                                                       \
            n                                                                \
          , BOOST_PARAMETER_EXPONENTIAL_OVERLOAD_THRESHOLD_ARITY             \
        )                                                                    \
    )(z, n, params)
/**/

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

// Generates:
//
// template <typename Params>
// ret name ## _with_named_params(Params const&);
//
// template <typename T0>
// ret name(
//     T0 && p0
//   , typename parameters::match<T0>::type kw = parameters()
// )
// {
//     return name ## _with_named_params(kw(p0));
// }
//
// template <typename T0, ..., typename T ## N>
// ret name(
//     T0 && p0, ..., TN && p ## N
//   , typename parameters::match<T0, ..., T ## N>::type kw = parameters()
// )
// {
//     return name ## _with_named_params(kw(p0, ..., p ## N));
// }
//
// template <typename Params>
// ret name ## _with_named_params(Params const&)
//
// lo and hi determine the min and max arities of the generated functions.

#define BOOST_PARAMETER_MEMFUN(ret, name, lo, hi, parameters)                \
    BOOST_PP_REPEAT_FROM_TO(                                                 \
        lo, BOOST_PP_INC(hi), BOOST_PARAMETER_FUN_DECL                       \
      , (ret, name, parameters)                                              \
    )                                                                        \
    template <typename Params>                                               \
    ret BOOST_PP_CAT(name, _with_named_params)(Params const& p)
/**/

#define BOOST_PARAMETER_FUN(ret, name, lo, hi, parameters)                   \
    template <typename Params>                                               \
    ret BOOST_PP_CAT(name, _with_named_params)(Params const& p);             \
    BOOST_PARAMETER_MEMFUN(ret, name, lo, hi, parameters)
/**/

#endif  // include guard


/* macros.hpp
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
*/