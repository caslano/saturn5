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
kZ9bjJmPs30wbeg0B+eg+ktn7my1PdA22dLJRsHZvjRtk3O7AFq/dqH+Jp92Abz+7UL8pv++XRB3wz5o3x9xBXSZZtGluArYgR7TNtW8LJtyLX/QXu9SGsPWWOSSzvRQ1rniTb7rnKcWcoqx3xy1nIvVcspnjyjlXepH3sW1kFe0A3Os32a5ryHktd836mTPcXktZDP7QTPm2mVbgs53hbdshejhBpSnIrA8/QOVwSZl6r3ZlRZ5cjIxKZ2bk+mkf1ZZC7lMPV30kLq/qG32lmt0dmB5DB5Xtfp/54NH7v9dgWez/5cMnR2Ak/t/1r4m9QWrkfZYeX02yyfXwb0P2b8vd9dtmNCH+m5aJ21C2uaA+RWwzuU+bJGP88ujlI/PXHQgm+dvkG35I+p5yTIv2fjc1mrOS5Ztdj4vWbY58LzkvM1+5yURxv9uXtK0EfPm2c/aukqfT1PojxdgKPtbPxB9MubjXGp7Jukyn85ioiVNSl1W1LBcmDpA+Him8L3KSuqj4iwd+teGy3HyFh9pTacwlO1cyy0+z9JEeDWT3+sesfkG4T5eN/EeXCryJcMia25moXXNhJCV14szzz7Is1LIye9FnnjM/qJUXuttNc6rqgtqRT6B3zoPQQVM6Ogn8q+jJfLah1n0/CTkcNEesQfU9QDh+l/DcRv5P661h8aGa61FP73dVubjdN9BdC8rv3XtJr963us/eM5pFfx0/WUilRGsG1grsWZ2AfnPRljB2lS4qjAmsCzIN6IJozalF8pdp/nmuZtd7esImSbXpHH119dzhPSOcoVFhYdqyjUdzDN7vvlNLsP2Tc7pugpr/fEo+t9In3Kt3LQF6v6YZ6tcTkVPLHCbsLXmdce0aXEL7TJdo3+zFTJZ7iV3MI9dWk25VPPYqxfa+2M99LZKyKW6izxwO1oWWLaAfcVhj6vPSVmskI3Plwwo1+Kt1bp7PKCMJx5X92e3K2XEZjAH6z+210J3nK+4z8kiF3+fKFfKhU9n+ErhtA9SHli+Hk7mplKetJyHzuO8CpuM+FrmYG1ghSVvl9dgXlkeE1Q8ab+vfYn+sM1LvlsxdlL2P0KIrgHyQHnOHcLxlveeGpZFU97uTxmEQzi/08y+hEVejGGU8l5MdE20OLW8CKf645rh4JHHNfnbeN5K0I4S8fdgfYXCX29/voL+v1qEfo0x7omMDIsIroOlGcEo1JLOqjse6lGT8VDLxQbzRt63uRBuLcpqWZVuczOL9J2aWZiKGCOdiaU+Dy8BuJV470Cb0FBtQ019i72QemhVZ3KvI//u6r7/NkvfH7zijmRzHQ/R9ISuotV9f7N8IozJnK9Ex3ndkt55RP+i2Xbqm1H/IhVlcd7TSKOed/WmiPzaFuudXx9KdzidUu9b6BlD5flyyp+GiMHPWIP3SUJP1rGGlH7kPaVhMtEWetmkPZzP7Xgte1uuQ6Xb5XzGPOiEbGRzYJsEPq9z2e5FWPc5Wq/uu56PeEbcNcD3PXKbUyUjDg/LLs5zMJ+/fbszW+7vW9KJZ9T9rQpZHh7COJkfqKiFTObe1l5L+Ox8ELiANwP/0M90FzJhT8mt9rOKm3HdPE10I0Ja4e8AuFVwHUN8nAXE8pr9NU06++OGHbrPz8F9Id27wUHaLSgH8dL5Pa1Q9g/AmWcWz+T9+3PwO5X35t8PN4vda27DTYV7HHwH4QrxfkLgO1bFPog2u8Q+CPXZ0FhLsGKndHadpNfNS43A1nDfYjXbYM+bQq/4RjBefaYH0TyjtYHWOsPNVJ+FgrCcfzOQaYs1XgOqXEcs06rPTqk6B8ByZoqDehrp4HsBtS0sn6+zVRJ3G3rvn+T9PTtvGfeFLfM=
*/