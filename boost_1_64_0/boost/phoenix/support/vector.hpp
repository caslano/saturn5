#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4512) // assignment operator could not be generated
#pragma warning(disable: 4510) // default constructor could not be generated
#pragma warning(disable: 4610) // can never be instantiated - user defined constructor required
#endif
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)

#ifndef BOOST_PHOENIX_SUPPORT_VECTOR_HPP
#define BOOST_PHOENIX_SUPPORT_VECTOR_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#define BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL BOOST_FUSION_ADAPT_TPL_STRUCT

#include <boost/phoenix/support/preprocessed/vector.hpp>

#endif

#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_SUPPORT_VECTOR_HPP
#define BOOST_PHOENIX_SUPPORT_VECTOR_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#define BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL BOOST_FUSION_ADAPT_TPL_STRUCT

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif
/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define M0(Z, N, D)                                                             \
    typedef BOOST_PP_CAT(A, N) BOOST_PP_CAT(member_type, N);                    \
    BOOST_PP_CAT(A, N) BOOST_PP_CAT(a, N);                                      \
/**/
#define M1(Z, N, D)                                                             \
    (BOOST_PP_CAT(A, N))                                                        \
/**/
#define M2(Z, N, D)                                                             \
    (BOOST_PP_CAT(T, N))                                                        \
/**/
#define M3(Z, N, D)                                                             \
    (BOOST_PP_CAT(A, N), BOOST_PP_CAT(a, N))                                    \
/**/

namespace boost { namespace phoenix
{
    template <typename Dummy = void>
    struct vector0
    {
        typedef mpl::int_<0> size_type;
        static const int size_value = 0;
    };

    template <int> struct vector_chooser;

    template <>
    struct vector_chooser<0>
    {
        template <typename Dummy = void>
        struct apply
        {
            typedef vector0<> type;
        };
    };
}}


#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
        (3, (1, BOOST_PP_INC(BOOST_PHOENIX_LIMIT),                              \
        <boost/phoenix/support/vector.hpp>))
#include BOOST_PHOENIX_ITERATE()

#undef M0
#undef M1
#undef M2
#undef M3

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

namespace boost { namespace phoenix
{
    template <BOOST_PHOENIX_typename_A>
    struct BOOST_PP_CAT(vector, BOOST_PHOENIX_ITERATION)
    {
        BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M0, _)
        
        typedef mpl::int_<BOOST_PHOENIX_ITERATION> size_type;
        static const int size_value = BOOST_PHOENIX_ITERATION;

        typedef
            BOOST_PP_CAT(vector, BOOST_PP_DEC(BOOST_PHOENIX_ITERATION))<BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PHOENIX_ITERATION, A)>
            args_type;

        args_type args() const
        {
            args_type r = {BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PHOENIX_ITERATION, a)};
            return r;
        }
    };

    template <>
    struct vector_chooser<BOOST_PHOENIX_ITERATION>
    {
        template <BOOST_PHOENIX_typename_A>
        struct apply
        {
            typedef BOOST_PP_CAT(vector, BOOST_PHOENIX_ITERATION)<BOOST_PHOENIX_A> type;
        };
    };
}}

#define BOOST_PHOENIX_SUPPORT_VECTOR_ADAT_PARAM0                                \
    BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M1, _)                             \
/**/
#define BOOST_PHOENIX_SUPPORT_VECTOR_ADAT_PARAM1                                \
   (                                                                            \
        BOOST_PP_CAT(                                                           \
            boost::phoenix::vector                                              \
          , BOOST_PHOENIX_ITERATION                                             \
        )                                                                       \
    )                                                                           \
    BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M1, _)                             \
/**/
#define BOOST_PHOENIX_SUPPORT_VECTOR_ADAT_PARAM2                                \
    BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M3, _)                             \
/**/

BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    BOOST_PHOENIX_SUPPORT_VECTOR_ADAT_PARAM0
  , BOOST_PHOENIX_SUPPORT_VECTOR_ADAT_PARAM1
  , BOOST_PHOENIX_SUPPORT_VECTOR_ADAT_PARAM2
)

#endif

#endif

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

/* vector.hpp
xi44HAfiWByM41Ctp3IZX5xNPXWT8fWQ8fWU8fWS8fXBaOyLo/BqnIxRGIsDdHFipnueHydkfpRhM3xX5sdJjMD3ZH6ckvlxWubHBzI/PkS1Py2b7vk6zYPSn76A/ngI2+JL2B5LUcbDzjzjgatsxhMl21cDsDkOxDC8BrvgIHSPh6GK8fSS8fSW8fSR8fSV8fRDaS9MqOft11bSzlpjQ7wSte3EKspNleUnFhvi9agtdzM8t88rpL9thH7oh9r1EjM8nzdNk/k8H5thBrbHTOyPWTgYnTgZF2IsZmt5Mcz0vN37ldTnPzEIv9bVX0wV5d6Xch9IuQ9R206Z6Xn9/4zU+7NS7wcwAJ/DYHweW+NBHIgv4GA8pD/vJuOfZtM+2jWgvrA9NsUOGIKdcAp2Qe045CzGg+k24+km4+mOidgTHRiJqdhLxlPGUCrj6SfHa5V4R2Q8v8r2YC1+3wtqYxTWxSFYD2PwMkzAy3EeNsQt6Id7sDE+hU3wRfTH1zAAT2AgnsIg/Aib4Xlsjr9jMPrVJjdsgaHYBsOwB7bAXtgStfk/x/Ny0EnmY2dsiF30/XQV5a6V621HY0Mco1/fzfG8/Hwpy91X6If/RG15neO5nX4q5T7DIPxcV66kinhnpNzHEu8funJlVZR7QOrlQfTDh1A7zyvlmtqUu1L62TYYiOGoHVeL99w/x0me0yXPOdgaE7A9JuqO70THe+5n8qSfWYTNcImUX4r9cRkOxuU4GW/EWFyB6n5RiYz/PZv9oi/qsBziv7A1/oAd8EfsiecwCv+Nk/AnnIc/43r8BffgBXwN/4Naf5Dgeb+lpfS7HTAUO2Ib7Iy9sIv+vrFEWY5t5s/9xGuMD2AvfBC15STRc3s/Iv3kq9gQX1Ovt+LLBCm38DJ3OeqK+23c5RpKPD9sio0lbhOppwCMxkCcg0HowOa4EoNxLYbgBgzDndgC92FLfAlb4SlsjWcwXKarHdYjufYYjB2wC3bEgdgJx2NnnINdcAH2wXXYF2/BfrgD++NDGIUHcAAexYH4IV6D3+Eg/B0HYyR1MgQn4lBMwGjMxuF4I47AdTgSN+Io3IfX4lM4Gl/FMfg+jsVvcBz+hNdhHep8PDbBCdgBJ2EkxuAgnIxjcQpOw6mYhLGYh9fjapyGW/EGvAvj8CGcjs/gDHwZZ+LbOBs/wjnYsB5NEJvjXGyBSRiBKRiF83AezsccXID5mI4bcCHuwFx8DPPwA1yMX2A+foNLsGV9lmvsgyswGlfiBFyFs3A1LsA1uAjX4Sa8GbfhejyAG/EYbsI3cAt+hVvxa7wFf8Vb0Y/2fjuG4S4cjHfiULwbR2IxxuAeXID3Ygbulfa5k8GZxvKDh2W5C8BN6nUzcp48GIMxBPtiKA7CljgaW+F1eCU6sC0uwHa4ENvjYuyAK7AjbsDOuAe74F7sioewm/56mvmer6fxl34pBJtjKKrHnYuk3Js2x51/lf2L3zAYL2Jf/B0HYS2Zrto4Gevg9Vgfs7AB5mFDXIZX4CpshIXoh9uxCT6C/vgYBuBRDEJ1v6pogefrVufLdf0L0B/TsRVmYid0YhQu1I2vvIrx5cr48mR8i2R8+TK+pTK+ZVr9M6R7vv5ihbSPmzAC10i5AwxOKfdvKdcMH5Vy18l24URshlOxM8bi1Xg95mMcrsLpWIgzcAPOwl04G+/FObgP4/EpTMAXMBEPYzIeRQe+jan4IabhWZyPP+AC1PZDMjyvj16S9VEpNsTDqF3fn+H5esTmsp0RjEEYgi0xFLXjxhme2/t3EvcsNsfvK/cXaBSUgwSb7ZKWErcN+mE4tsV2GIntcQB2wuHYGedgF11eBZmer68LkPM=
*/