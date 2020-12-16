/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_PP_MAKE_MAP_07222005_1247)
#define FUSION_PP_MAKE_MAP_07222005_1247

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/fusion/container/map/map.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/support/pair.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/generation/detail/preprocessed/make_map.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_map" FUSION_MAX_MAP_SIZE_STR".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    struct void_;

    namespace result_of
    {
        template <
            BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
                FUSION_MAX_VECTOR_SIZE, typename K, void_)
          , BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
                FUSION_MAX_VECTOR_SIZE, typename D, void_)
          , typename Extra = void_
        >
        struct make_map;

        template <>
        struct make_map<>
        {
            typedef map<> type;
        };
    }

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<>
    make_map()
    {
        return map<>();
    }

#define BOOST_FUSION_PAIR(z, n, data)                                           \
    fusion::pair<                                                               \
        BOOST_PP_CAT(K, n)                                                      \
      , typename detail::as_fusion_element<BOOST_PP_CAT(D, n)>::type>

#define BOOST_FUSION_MAKE_PAIR(z, n, _)                                         \
    fusion::make_pair<BOOST_PP_CAT(K, n)>(BOOST_PP_CAT(_, n))                   \

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp_make_map.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_PAIR
#undef BOOST_FUSION_MAKE_PAIR

}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

    namespace result_of
    {
        template <
            BOOST_PP_ENUM_PARAMS(N, typename K)
          , BOOST_PP_ENUM_PARAMS(N, typename D)
        >
        #define TEXT(z, n, text) , text
        struct make_map<BOOST_PP_ENUM_PARAMS(N, K), BOOST_PP_ENUM_PARAMS(N, D) BOOST_PP_REPEAT_FROM_TO(N, FUSION_MAX_VECTOR_SIZE, TEXT, void_) BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(N), FUSION_MAX_VECTOR_SIZE, TEXT, void_)>
        #undef TEXT
        {
            typedef map<BOOST_PP_ENUM(N, BOOST_FUSION_PAIR, _)> type;
        };
    }

    template <
        BOOST_PP_ENUM_PARAMS(N, typename K)
      , BOOST_PP_ENUM_PARAMS(N, typename D)
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<BOOST_PP_ENUM(N, BOOST_FUSION_PAIR, _)>
    make_map(BOOST_PP_ENUM_BINARY_PARAMS(N, D, const& arg))
    {
        return map<BOOST_PP_ENUM(N, BOOST_FUSION_PAIR, _)>(
            BOOST_PP_ENUM(N, BOOST_FUSION_MAKE_PAIR, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* pp_make_map.hpp
AP0lf9cTts/tGGaLf+l63Nc3+Lz10S3Tp7aMHe/elrKtxPh3b8uVkbxHf1t9ak/7tiUEubfn3ZRhljJcT4Q0phfxsO1t+Sp/aNvyUJB+W4b10SuPFvHhnFk92fi4bH+Fe1uWUskK3e2kIb1sxyH2+6tXuLfjPeRfJfnrfwFZG9RjOdKeEgM+3TWOeAP99qzuW1O5vn0XpWnaVV3+kgbu7bqGyoYNqLF8Gti79rV/Fs43cG/fNfzDJOVoftD5/P1TovO5N19p0LYxumX69B1UMc74WD1xpXubrlW+J/S31efvodiG7m25nvwrJX/VjzOf2/EVne+h3Q0Nfif1cSvPtzacZPw9HtzIvQ3vVSo40K1Mr9tvoP2Yb+Tefln8I1Ly1v4o9fU7aLPOefNCI/02rIrRL9OX76DqFOPvoLSr3NtxA5U0G2yrL99B9jLeuMq9PX9PGWXaMhwnaN/Om69Le6rLNF2t156kPkZl+nbONCUZt+nuq93b9D4qWmW4vd6fL+3xoDsH62+fWb19XNB58/2qXNedD+FN1mu3HB705ueyWbxbyrRfDwW778dNyjPGQc4yPccrddl3Eqe9yKWc8zrlVPAPk6ocXz9zAarzf4SUk3mNfhumqdrQl89Z5UTNMaHapv3XuB8Tm5VzvmqbfPls2c+D2TK/QoKM4xpBekA516vzNeezU5UJzbx/Fu2ct0j6Pjj3lSbuPPO80DFA/Tw9I8QRG9p1v0pdB0g/iRjSH6hrWKwtbnyPHFsgYm/awL5fj0bY9qv9+e0M/iN1Us/JiMpr9IrQtN2K69zrs5VMzZr6yPWg13V6MNL3Ojl+xzZ2r9M2ZX9q6yTXWL601UMXUS/7Oa1Sp16PKJ/9we71kusVn+pWfhF1s7dZyvXudXuM/NLc6ianWx/q9ehF1GuI/XjXqVdFJElVL/3fz97X7/GLqJ/j/lYT9/rtilRKcNRP+1vU63o9cRH1ks8l8bTd67WH/EyaesnvO6/rtPsi6uQ4/nXq9BT5lenVSX4r+XL8772Euk0Nca/bfvKr1qub40Pgfd3+dBF145zvEvu/J6kpKYJ0kPxih1rrltMj0/dzPoWp68PcEPJdpTmOUpq5l11JBsWOsi/u/M69TP3yNZ+v0zrl/1k5lzvKv/hz+VtGddAcG5nN3etwSMkgzl6HSztvh13rXVt8olOPF5TjwFGPiz9Hv2rUFprzsaWFex0OK8eDow6Xfj6u4+Wx+W0L/c9FpbYuiXHDhvvQFgFe7o+iUPfyjygZDLOXf/Hn/hIv2+C8Th2OKceEow4Xd55/xcvPRnFL9/KPR/K6o/xLO6dv9rIeQa3c63FCORYc9bi08/frHuoRYZ+nRerxuvRhOk56UulE1kfmrmGGoWle9LV1vT7gmXF+uiUnL9dxfbDLNr81Efydc6cW275TLKr+pDJ/VVYRvUcdcyb9njrSZ5OXWM/lGsBs7q3ZnorWcm0k2zPCvj22eyr5OWyON/M6yVxSutsTr7M9Jp3tSdFsjzL31mm2ZUdrW3/dbUqdZN0wzdw+bJPLdpWE6W9Xqe2ecMGvvV272aYlYbbt2ttXvV3qPs6yXdLHdl9to3kUfO8ze7n66ur3gTWeX0G/r+7PP++Cft/ey9dX93LNx6DfZ/nXm4/h+rHK61cnlaxMGdq66z9eLgzotqlXU9/nXbD1+ZR+ARBEMtd27fN5QNU3NLiG9V5UxyOS9cJ11tupjpPTxzi/CtV6aZJfaw/5ldZQ7nZ1/KAayt2mWu+Eplz9/Fj6G5e7Xt1+NZS7Vt0u/aVcD/mZayh3vnp/aMs1iNNUoSnXKL+qGsrNV61X3de4XLO6fgOkXA/5mQYYl7s=
*/