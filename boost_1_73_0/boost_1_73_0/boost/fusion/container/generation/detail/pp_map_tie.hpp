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
d8WeNzs3ey08qJA1bU17bZjhBR+z3vqEegP5VxQ/CAjSTnewz+jtZy7X3tJ6W9Da//YItCl4K/IqGB7Uq7LH1iVAMXzCv3MgZm2LrIhqE92TyvOdrTXbq9eOViVz9vLOnp4RJjZ96jbEoa25aKs09w/pnh1U3pTIda+N+k9SKZbw7rxCtCfD23EbLa+pJNfX3VYHwUbyQFdO2S5s8+8cZcltXaAYGHOVSLv6vU7ttK+77S+Tcbug8ZDMKhUHH6eYuWB+KMgRIePbgW0Mjsjbi/+Y1QbSJl4l1ymQyutE0/kH5grYyvHFqDvuX4CsbCa2rx1uZz2PPLJFs9NEfjeI5dL72jc//LGFt6SZDvdM60jtmf1/xv0900qVEJV1Uux0L28/m58TUOoCNssWtn0PUNMeUOl9WrTbtgwr+9MASiGSThZRaa+YKKlLcY9jxYIbCZ9GzfWla9NOBVzZX1zy3yZwFc8vGabOx7i1o9L7NLNNy5xG5t4hFDe3F+VMe50763Pnbg6LN67XuOyiT139waSrGCzJ9Qp+ZD9Za9SrKS39dFV9SitSzZNaih4AjRRNcNEdoV2A3GeUS2ou2bXbhCfQBIM/kMGfEvm4ytQGIhmgQRhRSeO2UZHJA4Sg6qDrmOM/RBMX58S0Y7fY
*/