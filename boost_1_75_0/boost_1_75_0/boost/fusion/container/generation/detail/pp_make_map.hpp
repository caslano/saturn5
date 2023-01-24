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
803gxgSkfB240Q/cptOw9wpGlhyuN6fsodOiWkYmBKOVEGaazPUQnvrWac7YSc+xH6obx2rru3+9gE9g7FBhucVBf+nFP94uclM/bEPpTKaM8D7bMIhfhsTH8AP7D/G1k/MMTaOo3JUgC25762OOhDdHtv1ci4NW8ZDCYlWnN6kejPZuexHhqObQet1AprKnr7fCoiOQoKm/rOHDG+XOE7Ylunt8VK+2nZP31mTkSkjChcN8D3g3Q7HmH1W7Z3NiVN/R30ghAHIzzF6Vn6IXIgzq4AWhjX7BzD8UPR3s6KxDUMUv2KxvSl5XCM6USIiz8ppZ4m+55YNR8PmUE3ovZy/HLp+bdal+9vvqlr48iRGORk2Qzppk/6ackbi2JG7S92NgBk8wALYweJlWnSd0fh94Qv5MP59MK58KwRi5Vkp6SpgV/Haf/v7bFaqw70+mZOt6VmqTg0t4SbkixpfY5/tnBB/0ZEQVSOFgIBysUIh/CIRPul+TSzwVy3WY/ba3DlyvTeqq+2k16KKiqoTX7vnWn6DjxNq6QSxFW83+SzUsKBHMiEmT+RW0fut7oYvXjTMmWoXoXd67FcXRuy9d72L2y74YHMeP5k+Cq8ENZRsqsUrp0bZ8jsHyS4mOvd7N+8iLoepHyl1qGYvrfB+AesOFuv7fgbpwwZGfP4Ovj4VLK/9S4Wh4/Hx8wOlpMY8nX8lvOzGrFIZpvul7
*/