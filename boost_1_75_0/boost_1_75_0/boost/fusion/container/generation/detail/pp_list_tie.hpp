/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_PP_LIST_TIE_07192005_0109)
#define FUSION_PP_LIST_TIE_07192005_0109

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/fusion/container/list/list.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/generation/detail/preprocessed/list_tie.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/list_tie" FUSION_MAX_LIST_SIZE_STR".hpp")
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
                FUSION_MAX_LIST_SIZE, typename T, void_)
          , typename Extra = void_
        >
        struct list_tie;
    }

// $$$ shouldn't we remove_reference first to allow references? $$$
#define BOOST_FUSION_REF(z, n, data) BOOST_PP_CAT(T, n)&

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp_list_tie.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_LIST_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_REF

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
        template <BOOST_PP_ENUM_PARAMS(N, typename T)>
        #define TEXT(z, n, text) , text
        struct list_tie< BOOST_PP_ENUM_PARAMS(N, T) BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(N), FUSION_MAX_LIST_SIZE, TEXT, void_) >
        #undef TEXT
        {
            typedef list<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)> type;
        };
    }

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>
    list_tie(BOOST_PP_ENUM_BINARY_PARAMS(N, T, & arg))
    {
        return list<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* pp_list_tie.hpp
+pp9KjSACpC+WKmhAFYj04BeTeC+Bo7dahMuPWG6/b1Tuh/qwoqREu+DuvxXJkgBpJwxACnxBBgG6ayXAdz/F9KBPxO4f5d4nwrcpyfQkeGzaAh027z/RpDTDXgFEyA9uO2WS0opSqD70A0l5STQSWOkSFCAEdL51jHSmQTh3J0GkBngov+tkIoTC+B0F3ks2AdnT4JyXB0JJEIbO/rgwhMQGAgoJ6rI/q2juihBXWJqfMArc8O6taH31cSkneMWt4z7s6jWZH47sHI8i79Z5Avl5ZyFaFV1bIi1iPuHj2FWhYHCgw+rlLFHyUM/Z3ko0PVUkRnUz2Q2py0HzakLprwSp06GjYqTLjJ3BPr5NTrwt/JdjSK/yECG80cvBcuNHvhpXaUUrf7ARQ4wB8g/296KdFBrGm5c/yUIkh88h2yorJ4xRgb3JzkL6UZ9RulG66GUEpqW85tCb0bqAJHhFZCULELsES2WvY0cD9lUaQhm33U+GDOFGoe/joOGZxDy/DUhnPb75Z4oAEGFGv9bBf3wJpGgV7SFpYzIxa88wLa3n0wDM69qIMuWVdBCsQnTgbHAUTksuJ0MH/IdAQq2nDgmD3GA8I03JX7UgwZZx2GV/vmJPO5dX6NECLtqlV129MLpJmAjaVB2QcI3TQBEAdhlQj/R4nzdMfOymLT/wi4Rqy03AXkDAsYMcGBy/Nk1Qpkoocxyfc02FepJ
*/