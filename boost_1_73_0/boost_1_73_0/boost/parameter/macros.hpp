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
3M07q3Yntlh0e6dn7dqQBevkbPZYO/aSW1r2zq8hJP4GZCdQj7QEstctZ+8PK1uM1Pcq3cvLO8vzPiAmJquvwL2pDu4Rw48qE6Rt+U8o9T3XP1BLAwQKAAAACAAtZ0pSM18ua68OAACZTgAAIAAJAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvdGVzdC5oVVQFAAG2SCRgzVz7c9s2Ev7dfwXqTkeSR7Fjt70+knROtpVEV0fKWHJb93LDoUhIRMOHSpCS3cf/frsA32+aslNmYssksFjs7vftAhJ0crS/64AckdpLEf8VuOC36PHedX6jmlfcWlH+IvIf9PoAv+sGOSFxl7+UAanv8hfpiy5KMMpLfK0odQN9QN3wxwn2/KDgS7gD3bDnhbO5d9na8Ej/YkBOv/vuW/KMnD0/ez4kl6rNqEnmHrWX1F0PyUtd3Pm3od7dHXP6w5BQj6jmcSBqYTBOuLPydqpLCbw2mUZtTnWicqJTrrlsCX8wm3gGJStmUnIxe387mb4Zkp3BNAOF3Ds+4Ybjmzox1C0lLtUo20oZG9X1iLOC7iBcZ9wDgb7HHPsYxqbEo67FUQYOr5rcIepWZaa6hIFUjxiet+Hfn5xovmuC9ie6o/ETLZz+seFZ0UxuQQlLvSfO
*/