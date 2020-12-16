/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_MAKE_SET_09162005_1125)
#define FUSION_MAKE_SET_09162005_1125

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/support/pair.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/generation/detail/preprocessed/make_set.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_set" FUSION_MAX_SET_SIZE_STR".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#define FUSION_HASH #
#endif

namespace boost { namespace fusion
{
    struct void_;

    namespace result_of
    {
        template <
            BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
                FUSION_MAX_VECTOR_SIZE, typename T, void_)
          , typename Extra = void_
        >
        struct make_set;

        template <>
        struct make_set<>
        {
            typedef set<> type;
        };
    }

    // XXX:
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
FUSION_HASH else
    BOOST_CONSTEXPR
FUSION_HASH endif
#else
#if defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
#else
    BOOST_CONSTEXPR
#endif
#endif
    BOOST_FUSION_GPU_ENABLED
    inline set<>
    make_set()
    {
        return set<>();
    }

#define BOOST_FUSION_AS_FUSION_ELEMENT(z, n, data)                               \
    typename detail::as_fusion_element<BOOST_PP_CAT(T, n)>::type

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp_make_set.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_ELEMENT
#undef BOOST_FUSION_AS_ELEMENT

}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#undef FUSION_HASH
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
        template <BOOST_PP_ENUM_PARAMS(N, typename T)>
        #define TEXT(z, n, text) , text
        struct make_set< BOOST_PP_ENUM_PARAMS(N, T) BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(N), FUSION_MAX_SET_SIZE, TEXT, void_) >
        #undef TEXT
        {
            typedef set<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)> type;
        };
    }

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>
    make_set(BOOST_PP_ENUM_BINARY_PARAMS(N, T, const& arg))
    {
        return set<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* pp_make_set.hpp
Sl1ujHG5K9THi6Zco/wqayh3rPo4qKGdx6jXGyjlesgvcqBxub9T748atjdHfbxoyjXKr6yGch9U16+G7S1T109TrlF+5hrya6n+HA0yrl+c+nipYb1Y9fmlhnIHqo8Xya+1h/wqZb0EnfVecqwn949xgIf8zDWst1NdrnY9/fMV9z5lPQ/nlzTNekbngwrNevqfX5Yhsp6Hz5tJs57R56NMs57R8VytWU//+JN7O9jTw/4o1qxnuD806xl+f8TJeh72R2wN681X16+G9fLV9athvSHq+g2T9Tzst9ga1hurrp9mPaP9VqlZT2+/lQTIdZ5c/5k18aLb8p/DsB12wfYYjR1xCobjXOyCC7AbbsQb8CGMwO3YHR/Fnvg8RuNLGIPHsQ/KWC+5TpPPvya+6CKpTzH/64SLpT634RBcgiPwDlV+pX2N80uW/CZIfhMlv0mS32TJbwpuUOInpxJji7SVdIx0nhSaVjcglpSdVtdjXMJS1tlBOs+/D2MV6QIpLJ04XaSZpE3pdX0aHyRxCnVjFOrHJ3TGJCwiGcQhlBiE3o0j6oynmwdqYwwSX9A1rqA2nuB5kiaOoG4MQW38wJOkC6rxR6GRzjFIxAaUMUjOuIAzSXrjkQ5dGegYk1RJu9vjAp5FvfFJF3j9JO8hDiBjlUioE/vPMO6fjGOS2H/G45ksqjFNcS0CHeOalijv2elbrL+a4/x5jvGnGf+kiefnfSy/UoxBW/w+78dHqePzxSrGO2PypcSrY/G5xuE7yf68QAqbxueTlEYqJm0lHSKdITXMIK4eKZlURNpA2k/6hNQ4k/eRMkklpB2kY6SzpIZZdQOiSSmkhaStpGOkb0kNp9cNaE+KJaWQzKRSUjnpMOkTUsMZlEuaSiomlZEOkc6S6mTzflIcKZu0grSPdJJ0gRSaQ96kbFIxaW2OfzyYf/Ev/sW/+Bf/4l/8i3/xL/7Fv/iXX3z8/7ScvFT6jFiH/1/S+H9lXHaDjgGOfkPRtdz7yyxR+g3Z7hcOGWkdpeJ9v0LpR+LS5136ykh/KjP5OOOBhdUyftav38fA+Jm+/jNlo74Nvj/T13/mbtznQb/vhPEz/VHWZ+jf7Oz4fuL8+t80qxV9oM7QDrSZY278GOe956BaMjefJj5VU4zAEExhHZ37nY55WQ6TsrXxjwxiHgVr7k9KjCPjuEaaeEYppLUk7hdyn9A4ZpHcz1Pfw+PencQh8jL2kPO+m+69NrmX5hpXaFMN98si5X6Y/T5Yuf/ekH/xL/7Fv/gX/+Jf/It/8S//t8vPfv0f1QOiemTlX3r8fyV2223KeN7ZXD9ah7RH9UgtsOSn5melF+TlFliv8VnndtapzNesM70wN8NSYL2HUL9jgGPMTYrcQzCRGpFGk+5qTP16W69Xh40fnzozLz0z1ZkTVSrwfC9BHTNc/xreuD+9/rW60T2CyzfO4VbrNXzq6jlbM0/kHoxueXzpvjde72007sL3exD69z6MxhsYj2fYba3n2f33LBn60Q+RJ4tvabXju7IthvdiJGa47FM0KamWqt+X9PNqhJOxC07BGFXM7d/iaEzF9tQ3xkJfDYtxv6yFlrrSN+uXj9tcZql7UbGbD/E+Tfxm7ntc/rjN3sRs/m+P1fyJxX+fxb/4F//iX/yLf/Ev/sW//Octv8j1PxfOhZaZl3z9r1y7X+jgfP5fJtfuzTAMG+OcSP7dzXqdR2yMxKSkBOYeyOhRmJvjOQ6CPYZRe+vzf94msRHi0RIgrxHaSDXXnsTQIHtZNwUt9eQ1ZV15vTOG2V+3zDLb53YLc8bPs+bZ3vF3Ie/WxPiTufq+IjUhfUaaq8QpucFleymgBxX1fns=
*/