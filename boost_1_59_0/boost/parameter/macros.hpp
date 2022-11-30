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
    !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x592))

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
ojqkH6IuoRQcbddqHwP8yrOI+odLiKdCIYEc/+Y8nvxQR578Vu7xiDOMLK+3uYuL9/beLW3+WHboQdDgzBIVfn5X/CDlDd6euYwuBD8PfLF6k6mYlVMUfl1MN2MJQQr+Zj41K0fkTtLjzjc2kPK8vjr8Q7/ZQXlnVOnaUljNov/PsqtM71331XMIJjL8d5kPeEYMgwzL9pok4X92p3qapK+/Jr/tP89W7ohDu0HoEm0mD5+G3fPMJE6U19lk2lufxtKf3/7+0P/3D7br+1CWxLWKlEYNDt3Sw3VtvXoVC5agol0mrU5h0VhW+/G5gE3E3bnmyy35n6z7O89uoMCAGdqy10nIWdHUPDby7k6JDSFhXm0bC3Iommvn+5jtHhNdgUq1NNReUbH1vv1q3Jr/bd19XKVareAayVjtdm+dQ9uXSpH85AzF1e8UxxLQHHRJo/VhHC90Yt7f7UcDdxqHBMiWQZmAZTIhgjb5EBmhgjh2llcnbMGOx+a1UBrRPMLgF2/t0tlikv5uU3y0JELovbsJ11qcl+cVSowMAjExMUNMTIpCQWNl5WksijgjCgKOl1C4VtFcqQ1sUqdOC97BS/g+GVWMGYHSEuw+5EBoXVNLJEWlyKxJQONKLFtQ2diYEyJZUJAiD3sxMDbG7XualeT9GbZsXluCCg0LbuMmumr4O7OET1w5OpzweRqOuRilJxGiFEnWaOMf3kzexfiuwHOC8moduzbxJYdz+PwxAW6/csIkX29OxzqtNt1jOzYWjIhhQq9WhtVN1sRetGl7xk4T+JborfWNf57BeuG0inPY6ln8PFaKu83mDSsUtWvYRLNSYMcJEQU1hc7Gz9HWR7fsPpLyL/7dsm+4nOLmzbWb6J8msTPgYUhKNvAQWTJetGrBIQur9D4vSYfN1N6cLu9D6E8c3mWyprceleppG/xMp7koI/XkNNLhegz9hU767z1feu7v78EhoXm7jSaECOJVVuiSCH5uGGTMMqBMnLB3LdWasgWb41kPD1lZH58rJw39rZU/57ycD48zTPnbI+e97pZYQ2bhVWvtXu8F0uHH0ih9mBabvJmjUdXVZSOjoxQ8Zc89LdUNxiiFC0DJbAYRtqVwSW6uS8P2h8seaeNydJln34+SNRUVTOUTwm8T+cK3NWsXgS19VtrzapF4uTYAG/lWJ2pUOPWYFIkYJvth0i57tweCFPtj/DReEpTO6ojNGmLvxLdxeaPtRszyquyv4yHKgSoVj9qZwW07Z/aY8vE6MloV3VUV7V/7FjS0LbvrBp9I4zvGcMeq8+PKFhFFxwXLrBrQwbii4uzPCtnaGtaOvB68cz6afYgF1/vnUpNWcC8s9qGluodl54PLHBwzPGxyf+LixmvKqBdlno875jwXjijX+B+cM2wBZyH3yn7/4VBnuamEMb2mv/XP4K72gsbCrEFpdfUyN0d7+JtqPOGSiQSHJeC5RKxUjkHWrYSycbV/ifNJh9dWU5PCvApscfS4j1PLMiJJ/WwtwPCfKjhWXv821KCTdOujqbl0Ds6yfaFgr5+WT2UJHUncsxZMm+bkdO8awCQR8C98hnZnOxZ8unMIYEYKcSY3ef/HTYHb8PuXEmn6LS5iF+dVSMb+jJVviN+KpOQkxxsaQk6cyTdOj365FfMqZUXZSZ+vP9c5G1eg8ySO8U2BF437z/M6NkHTTvGUL+vmJs06TRcc4SPXMvMXsggPtme2YJPn19mWT6PkEzBhvbwRyN92ZSxf9jBgDt7HfXG4PKVogtFXcaSc35AzzLD3htelN4d3zBVKjdxd/t9jjN/6Kp1n9x5xx8yExrZFxszEhNO5itKn4iKRBF4vMB4i85SummakmzxhmCOOm29Na9JNvqex7OK0Dz4KfD+5gseO5V/kR4Wjxkw1xrY5ylnauC0Y5ODZrOZshCNeuIoKtSmtHpnEpD2t8Q7r/TQEWSpWi+0ahItEUsmlz9VKUjccO2smQBaGx2+c9v0uRPDj2UTXo7GZbgHp+MvpXHmqUnGTjK3zP1YHE/SJXkn9Ep45UHrvjn4DuqschvJP+vNHk9eI3QXR/mSvF7+78t9uMR2ucB5y7aVlwAMy7p7+pweVBCY3onq/eFfjp7YPOYQUKs173GjI74MJjmc9dWKwX6HonPmKiLPS1g5CEivLJI2YH0mFq0zhVi7r/vJtLfwz6p62c9T7dpSwQlFOdhy3sZQavWei3QwctA06VvoS2TB1LS6cbR6ZpChFFXQ0m6ES1UDkaHeGc2DjcjyG1C+4fOpAUWBGQ1pV96pcMoF28I17/AUh1s5DmGjuIHaquJ+y4Zfx5OQ7J9cu337Y3u2FOoODYCB2ktcs8k3jD93DUtz57qAgkzodjjFHrNbWVkheFs3XgFFsEZGIHuH1UNPYSZX0wxM0IyOjy+YL58u7u/Ar806oUzYDnBIJ8ltgFxbHCOFvhDggXxZ6MNAhXcgSJSwuAH9/e+EUWQmL81wznfeJF+nGD5cAodaEzhprLHsb/ea3j7TzlIDOYABuqmtk7z8Vfh1Rew7/l1yW/kmP8CrUNSqfPRWkrDc+Voy7YF3uxVqBWPQvB3WmvJOoOAfe0PJHc5ObF9Xan/wU82pNfS+mbrH8DvqCBM0yyiC2NFRTU1MOfhE4go/Z8DcHk5GlpT617kdqOi20cGJGBGgsYt6UhWmRPfOY1j3HmIR9zYvwtbZ9alFxcRGtrfhYpKSon0gLTU+GphPqPehoq5Uhu45XCcnJcCvNdFKurlyn2dxEnh8pUNrn0UIrW00vH33VjMdw1YpeJBq3Pw5H+aCGXfVJ/rGCizIbhHg/MiooEoF163ITcnlwuhZ30Qs1k0yVX2iHF3mwxb7cRnZ+CqRStpL2/If3ko3SRtq5ecmnLJAtgoKidihk3qbPAN1SVN90/kz1qyoHvr71iOrVAuF0iQy0DUNKcNCDu1YmgGIHcpCtiWHKZJlLNIsiYJySwS8Jl0h0eaNlp3ahy7YPSbnM6wwnfQ2ZyYuL/EBMqpHXUPByaVH6yy5aMSKgXco0aFlKgBkpuEYMHUF2H03gA1ooTVAWGMWWCM8q/N/dAC3qls78B4EGJ+Db61dG4SdtmNmCnYLyCtzST8XLcBHirr8G4HA/bcmRrrkEljW4oQeH4O3sj85c/MBG+QVJ03OCKbINEH5Jc9+CcYTE3JWKgJcvX/ZHA6QDZfZgoTmzl0B8A1Zd9DvLk/xyZ9Rs9iW0NA/SraG/OuX06RJUgDILQgsLC4hBJsrzfRQVCwvq/cEwFQMDIsYFttS6tTCVVx4A5arCJAghW4gxzBzRU/pN+yh/DD9kv0JDhQApv5IKnznOUurq+9epHAKprWkHgQANDOvrPeenRTEB9QSwJcN96B+BrHIGrUIBkKX1dZmvmSYK0L9oHT6NBU7FkDXUjYTYoDShR9cDw4B5Mvhd5UBasw0nUIQhJCYlry8Fdcm56RzAM3cRiZpiLNk3UOR8d81ZWvZv+wHfeW+Fq/XeUGzVhrX4ODJAWx/9zqOJ/K6vmpRkU0sdffXPlbT8a22qcMvmOvs7utfFOvwo+CbPo/fNodurPd3jMfzeaTVH404KiFNE3zn1Zi76/IDsH/w66VLvdyQLsimBF7o9w33aBnhjA+M60bAoJmIOsaQ8CliHugJofKu8PFq1KuKQMJ0QY6YQ6smebs94QyvufqD/QPc1FFBWfJXPFxOB7AEqjY7FQ4676lRrFq4ZyUE0t2QEFS0RElUlvkNBpaF82ZEndxKdQgDtIoxOVUepit++33552Eyd0HgXYIiIDk1PJw6gXNCd8PA1NzfrmTqT6QCxC1hTaVg2H/vQ2oesmhubX0+MaNZISLwDdLNVGlUkABc+P2porDg3ArympryyWFO1PqfJvfJoheUSQl4RRR42cVZ0rNA8bm6vX3bb/aIgWE8SQ86dcWomy276JQXTrt9KDxQoHXD5+F4xJW00hJVmeMPUUESUieQPowTHWpb6AvxTZeTkZGXlAm1sGtJJSQVZc40IFfCQvDEoP1QvTdllHPH9s/40G314KOBw4cTxYsfJL6A0848GiuK9z1EUMKTG24vaPrSOi4ujtjA0MHAh5nthjM1qBP5NLU/AENLnw4c/K1T+3C4t+unB5fvLrEYBoyTj1x9kb0oTd7ZAIVFMGshKOSrmnsgoo0rwil2u5OKQrPpajPoAjovZLiPlhYu5rohh/+y0EpiFhLPt2lv5h0nThO5kYkxh7QNcsMLXP+yL30m7hmVxO4yRN8dvbpxbMP9ULRzfLkeVyNR6bvCY7Rbih3VIpLMppeARIHmiqD0iT7Okxt6iEguMLvQdaTpWGFUs8B/OdZQQI/LmEL7IPVVGxcmvRM2E94b0guoEDFnxUHBg0yxalBk4PH1ejTPp83JVcX+/5rhNJU07NZHdXn+X6f6E/7skZiA8nIEWZ1XuE9bnZKjymNChyOjkwuvcazcWfOlLVaAUXIVHl98QAzMbpybk18BPXIZoFG4uPJgUUp1Oei1LvPBr51VXjeLjdGHJE0PZJ8K3w+yHoGl/9eRctv+9kuVjoL7QbCR2XiGuf6LycR6IzWJexmhmyYohANGyxJKdZaYiqZNl2sazmg0rEKCVwmJBQsCh+gm8LNRSLSBM8CUHwC/riYBAnVi4BXKba03KKoUhy0evczkyLa73D1W2F50Tb1XSPFqvzDhC5BgIjAECnyfjrA4Urq/7P4CUuGWKcFYvHH5aK/ITN1U2af5QeusVPWwSatVYSyzyiCOuXIZcVtrwxeToJxxlfbDPR7lWHiolFY6me3VY5xw9ovlaQ47Z9VF7eA6uxlriBAtmFXCTQiTAytcbg8q1UGPcYPVq2hVbiEL7IWyopXbsPmst7+tclragtdSlqEG3/sUU7eGxdthJhpSQZ+Drss2e1vuwTbKY3FdLro7hm3Qjo9hauN5Ehm2XoiLXySUrmF7mYc6XrMIb1WH2TrRS2bnHYraa9FbGQG16uTZxVPLR6EQVLvYa5z/TeGgbcJJguhHsa7sD+iFdvcPxmkVun2uLGCxZzOqN3XC0cLAeInuC13vHP3EuvB+4fX9/qoAivGy88Zqds423ZOLvBgOZfApPV6Mf8bu61BXj02q4eXi4sjvaNed+xCW0FI6yo7VWjkwLvb096xZMEz3ompW3nTp7W2g4xcTG/rrT2WHBtb6yS8sRxbcos9b3ucWthydOP6vW9phiHt4D6yAG/TrddrqJx5GTq9MVQZ7z735kOOf255W1KE1zcjTiYynbnnmuk1S/E3ueXphanHFrSixY+kb3o0YNDU/Yte04soooVQqtx4FT06+7ra2YGnkhnFEL74RY1v/zRzoz64OABgGa+X+3O/Zqg9H4Ruf2P249Put9jyoH8rmPuWvEg5rl5OWRfFRtnsc43oKWl/Uyk5A6BvXpGYv6HTw9b14utrdZbwkCKdsHWXhW/aqCfXgTu/XX3+vlStszSJtl8/capu7V2OVaK9GJSRqQmGMC5esWuTKoGqjZs3I+djVXsvINz+7/Qw4IML8YZheJnyZQwcAS3rXWXuNzkJ4c3I1ChZ1Ic0ZbfHR0PBsXtBtBFlGWm5unxwIPWPCzP7Od1xaPdNiLCVHGkpbgzjI7/UfJ/zvlbm/vbz+ioN9TktLqc7E/51oMO/qFkexO/ZZH4avGE9/jwmFEFo74WO3+go3PodjlwGc1po9bfnR5vtAWLsNdzDzhcTb/SpTpoNrDYOS+2qCzfd9835xKm+0E11VdUCDpCcGW27nJzGEv7tfLXDTa4N2qavm5B9YviX6pfK4Pfvz8jiSVIP3oE/4veMRsr1FECl+mX0akHHvLJZfTjskdIHwkHodvSitXMwbbWBJ4RIwiN/NvnJAOAJvXM8sPydygqPleYfOWFHd2dtIRFpdkkpJaVpYOT935uwOa87oUxfaEh2bvDWo/UfdcaN13V2KPa7T/3izv5vUXZxvV9anntQkUOtVlVV0pur9vJqMI79Ebstriuf/cgzRu1SBYNcoc6l9y/JH1MfU0WRkBRdHBcMjjN5Hft8U/5FfTHh6Bxx6RY4xaajQ4jea0TSoKQ0JYFCRfPnk7UAiLPQgfcBnIK07+R0K1mYSMsDOrktxjV531ken82PRlBnymWTA5/WQ0tL5YM5jmq/j2i2MNwsqomLLGYw5WjQ2wI1EWt8u1iltn/kPHZrv14SFppd4PJmShdPIc2WmMw5w6Vi01fWEuFRGCNYzTG5x88M/FVVjy5yGuDUF6+pHPHaZEU0J/GXpw3W9/xHIUXcvBmxWG+3DJ2Wz8HfwpIgVDaCbJ7VuWtwLED+3Umo3+7P7ekP2UO65oOScxr/q33elEaYqTR8cybKlenC132gF5AIkOoZDXJEZYmNKLD+tI0MF/aIjbn5Tu0ycRtoMTabqJNFZrpX/6hacLQnY7Xl/Ja7inoVNRns4ytOexZsypWhC++Nabq50JAorgQY+scdPwgpdWVXoXwTrheMEgXP6AY6ROJ8TaOJwf3bsf+/MExudWF3Hdel9VOVU/fK6NGBwKqI8TeVkMmR62clsiY4vEp0ydTmfAvvH+nl0LPeI/MO41MEs38giaV/35aUEksAPjbzxK5XV/dmocFbLsJICPTTC+/Q8FP4MpV4+l29X494dRm3wscSamq0ulBizZFPNh9zVq6X2Ceyf/uZpIPu8a3vm8SvHxFIsX47Bt5jEC/k3Q545Pm+3LHFq+pIjFTr0adIRXuBh+Yw6ajGSESnMB+ievaecIE7gnjJpH1ecF2OlhNCPHcxUuKJt4MXimYRGUAtBvh8dHx3aE11jGjLsobWRKlfmJhbSfPtQJUHMOv6RKUXeb2FfYl792zRXeTPYY52/tReNWf2PpXiRQyiamOD47Oz+LfwzUohDaBEQeHx8d2U6a3rSKUMdHblPGpfCZRX/AiXEd+O5yovQXu9su0fxarWJ6eX6SRUV2au/zwEdMbeWHquH8e4YY/DZ2kZ8MiZxEpj523jKDNgcuSa3IV8SK6BpiKOzbMbgvno3M+CiWJ/+4NQ/ONiirzm6zUZ2bUlmuqlSyL509bmjRwkLGCawSyevZqA/9ZC58koepPQ/oCsQFI0czM0tFOHsP6KPNF5oKnz5rpjSvhQuzef9HjG/bVuXL1PpY8KpkhZFCvWDNw0iu3Ml0ON+vj+1WKCtyXxioxXKTFKbavme3LvN99ZDFoR1WVDD9lbjFjJ+94Fn2p1bBr7E5YOsGtsZcSNmF91DtTUQFRmAYQVtaZU3UUZPnbWzcEN8jjEDL7u/vD+uzRFL+Ths1ecDgoGSjua3z80JnK6Azpunexr7kIKlF+LMFFd5u/EnwfnUuaTMl2pDKiBmqz4df+aURv5sH65PDWvtcOv/FYBsOHpScZkuTGnfSbTu6pMyMsp2bS6CEvwzm2iLkOSEJtFIi19c3NCRSd0PsqPDEU3I+lx6GpxXcvrTatkRtdwpXN91lCFufysU3uwq9b7O2S1f+0vrvoPG5pjdvxoGIbausHexCAU+NhzwF+ZmZmXrn/NjeLrlfWcd38y4F5NAq/J/oOIoIDUv14tiaTxhEtU8kSDBaCbnclg9IwRgU2FZ7UQnUeR208B42TNGFWIb0
*/