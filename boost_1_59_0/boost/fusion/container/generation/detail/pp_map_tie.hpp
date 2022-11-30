/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_PP_MAP_TIE_20060814_1116)
#define FUSION_PP_MAP_TIE_20060814_1116

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/fusion/container/map/map.hpp>
#include <boost/fusion/container/map/detail/cpp03/limits.hpp>
#include <boost/fusion/support/pair.hpp>
#include <boost/fusion/container/generation/pair_tie.hpp>
#include <boost/type_traits/add_reference.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/generation/detail/preprocessed/map_tie.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/map_tie" FUSION_MAX_MAP_SIZE_STR".hpp")
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
                FUSION_MAX_MAP_SIZE, typename K, void_)
          , BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
                FUSION_MAX_MAP_SIZE, typename D, void_)
          , typename Extra = void_
        >
        struct map_tie;

        template <>
        struct map_tie<>
        {
            typedef map<> type;
        };
    }

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<>
    map_tie()
    {
        return map<>();
    }

#define BOOST_FUSION_TIED_PAIR(z, n, data)                                                          \
    fusion::pair<                                                                                   \
        BOOST_PP_CAT(K, n)                                                                          \
      , typename add_reference<BOOST_PP_CAT(D, n)>::type>

#define BOOST_FUSION_PAIR_TIE(z, n, _)                                         \
    fusion::pair_tie<BOOST_PP_CAT(K, n)>(BOOST_PP_CAT(_, n))                   \

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp_map_tie.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_MAP_SIZE)
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
        struct map_tie<BOOST_PP_ENUM_PARAMS(N, K), BOOST_PP_ENUM_PARAMS(N, D) BOOST_PP_REPEAT_FROM_TO(N, FUSION_MAX_MAP_SIZE, TEXT, void_) BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(N), FUSION_MAX_MAP_SIZE, TEXT, void_)>
        #undef TEXT
        {
            typedef map<BOOST_PP_ENUM(N, BOOST_FUSION_TIED_PAIR, _)> type;
        };
    }

    template <
        BOOST_PP_ENUM_PARAMS(N, typename K)
      , BOOST_PP_ENUM_PARAMS(N, typename D)
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<BOOST_PP_ENUM(N, BOOST_FUSION_TIED_PAIR, _)>
    map_tie(BOOST_PP_ENUM_BINARY_PARAMS(N, D, & arg))
    {
        return map<BOOST_PP_ENUM(N, BOOST_FUSION_TIED_PAIR, _)>(
            BOOST_PP_ENUM(N, BOOST_FUSION_PAIR_TIE, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* pp_map_tie.hpp
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
*/