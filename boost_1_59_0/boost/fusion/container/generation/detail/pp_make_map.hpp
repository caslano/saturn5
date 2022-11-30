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
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
*/