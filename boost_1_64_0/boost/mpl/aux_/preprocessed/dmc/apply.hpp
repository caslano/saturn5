
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F
    >
struct apply0

    : apply_wrap0<
          typename lambda<F>::type
       
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          1
        , apply0
        , (F )
        )
};

template<
      typename F
    >
struct apply< F,na,na,na,na,na >
    : apply0<F>
{
};

template<
      typename F, typename T1
    >
struct apply1

    : apply_wrap1<
          typename lambda<F>::type
        , T1
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          2
        , apply1
        , (F, T1)
        )
};

template<
      typename F, typename T1
    >
struct apply< F,T1,na,na,na,na >
    : apply1< F,T1 >
{
};

template<
      typename F, typename T1, typename T2
    >
struct apply2

    : apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , apply2
        , (F, T1, T2)
        )
};

template<
      typename F, typename T1, typename T2
    >
struct apply< F,T1,T2,na,na,na >
    : apply2< F,T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

    : apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , apply3
        , (F, T1, T2, T3)
        )
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply< F,T1,T2,T3,na,na >
    : apply3< F,T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

    : apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , apply4
        , (F, T1, T2, T3, T4)
        )
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply< F,T1,T2,T3,T4,na >
    : apply4< F,T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

    : apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , apply5
        , (F, T1, T2, T3, T4, T5)
        )
};

/// primary template (not a specialization!)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply
    : apply5< F,T1,T2,T3,T4,T5 >
{
};

}}


/* apply.hpp
Lk5RuzgNjoIxcA5sCJfDRrAENoY7YFO4FzaDh+QnsjOyz4Z/gufDQtgaPgrbwGLYAW6BHeFLsBN8FV4Ky2FX+G+YAI19SN1hLOwBW8Ge8EJ4mdpNf9gdDlD7GQgT4SBvefIADNwfW5v96Y1Wf6ys3AnFowPXTyfzvupK5LYz+wdwyw2SXkUlctubx5VKxp+zzfpdI7mVpNeXf4xXvAc1/p5jrNGonT2tdrYBRsNntP97o/xabobt4bOwI3wOdoPPw+5wC+wLX5LfhJdhKtwKM+E2OA2+Am+Gr8qv73a4Db4Gd8DX4YfwDbgHvgn3w7fkv+Bt+S3YAevBd2A0fBc2hO/BFnCnngvvw07wA0M/+CEcCnfBdPgRvA5+Am+D5XAu/BQugLvhcvgFvB/uUXniR1TfPYmrcm8Al6rc71V5LlF5LlV5LlN5Lld5rlB5rlR5PqDyfFDl+RBMNOTBMfBhOA4+Aovgo/BJuEb+Ah+DpfAJPTeLofxY6jsoz3UbP5Zf6vmzFw6A30Ddp2+ZtEeb+6bV0HMbDoQzoO7je2RgeUMlb5jkjTDJK9Z9i2zu+6vkPQTnw2KPPH0HhE1t7kuIZJyG3WEs7AHd/kcLdd9IG/+j/XXfAHgiHAij4CB4DhwMz4dDYAJMhL3g5fAKmARl36Bvb7yL2fj7mKV8zYbnwdthJzgXdod3wMvgnXAwLITD4V1wOpwPl8MFcDVcCNfDu+EmuAh+DO9ReRXB/fBeaMynFsOT4RJ4KlwKo+Ay2BAuh03hCt0fV0Pf1fS9zciPoWcMNH7blJ9XYDP4KoyHr8OJ8A24ApbBd+F7cBfcCT+H78Ov4QdwH/wQ/gB3wdpGv4UXwY9hb/gJ7A8/hVfBz+Bq+DkshrvhVrgHvgG/hG/Crwy58Fv4BfwH/AVWwFrk5XtYB/4Ao+EheCk8DIfAX+B0eATOhhHU90J4AvwM1oBfwprwMKwFaUsRtWEyrAMfg3XhOngifAaeBD+Fp0FjXlEfNoYNYAsYDeNgDMyGjeEtMBa+CZvAnbAp/AQ2h3Vq0fZga3gm7AbPgn3g2bAvbAkXwT/CJbAV3Apbw53wQvhvGA+7U+9tYSq8CK6BneATsDP0PBcnuu2XKp9v8z1N8Sp/bsdb4gV+zqYEjqfnovq/4i0g+Pb/bzWO/wP2kd/WUfLXOl7+WnPhDzBf/lpnwH/Lj/WP5ud5juyzgpRDgSdekPmLO16QciivJF57r/9bfZ+gz9j4v+1m8kcUDXvC02EveAnsDSkziz+iybA/XAEHwL/DQfANOER+uhNhhfwR1UduEmwJh8Lz4HDYG14BB8IRcCIcCQvglXAZvErP56sNOXAU3AZHw1dhsiEXpsIdcAx8F6bBD+A4+AkcD+VnXt8tjDUrfz/z2SqPHJWHA6bDfFO5O3K9dm9FVrs3xivTfFXx6geJVxxivLIQ5VaEmF5UXmjpxed50+tbiX+sRHd6QeI5TOkV+8hNNc/33ekFjoc9odZHtW5KfTplD4TG7wfNR/br/epf8Cx4EMbDHzVP+QkmwcPwBvgLnAuPwCdgTcrjZVgLlsHa/2HvTuCbqPIAjhfaQkXUlhZoAbFyyU2577vcBcppuewNLfQIPRCQ1bqCIqBWRWGlalVYUVCrgLYcWhUVBN2iqIiIVUERUaqigiDsb5J/kpnMpEkquO5u8tnndxMm8445M33/9/AY1sSTGIA/4GVyvb0ce2Jt7Id1cDIG42wMwUysi3dhfdyKofgKNsaP8Bo8huFKPngtnsImeBabYhh1bYZtsDmOwOtwHrbEm7A1LsY2+Di2xVJsh/uwPZ7ECGzky/kfr8UeeB32xN7YCydjb5yGfTEO++E=
*/