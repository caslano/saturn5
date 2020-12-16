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
KHDv6/Tty2f03cq+87197gXWHId73xL3vvKZb99SX587r+d0f1amqqPUa+8YjjubeNKVnm3PkvqjqSvS76yqU/7vpFkl5XiKjDmJI0xV6k+cXjlOtjnMFqvDkR/y+UtSpUXGJUj+lMMoBepfp6IjAutUDv+qDpYeudhrU6eSglxLyyXuPhJ3D8I0M2mIDxK3XNgHI+4W9QPjzuULzuBxF1gzbQUHEvdAzViAxoQIwrGEPL5QFTxuxwy7rcb3pSrxRu4n3kjpe58keb6QYCfeXcHi7eb65Trg/Dp14p1uJu6EoPHyA1T3cvac4yjp558g8Y4n5Cv5DRavhWMol0gI7/iR69wv7uP9xvBMUs6ZXznMl/TESnraSXrsnYOlh7QcQH3zvtO7YeBvToHym+MXL/G5fmrqFp/+b41m7Ieko5ukowvBwYGqfeno401GLfLtvZ8Img5j7IUx9uLIjb1om6J8br23w0kfdvrj6tYz8lPSb1+1u25jL9JMci+ORdL32BDHyoUxTfqAc7E12jEWp2My5uMIdOBFWIg5WITT8WKUeLjHDh7PLIlntsTjlHgul3jmSDxzJZ4rJZ6rJJ55qr7UMomnl05fqkXiSUMzTlJ9b9d+vmeT72XK97LkeyWExE7+Y1eOc6XTvV0nYxNuwtNwCQ7Em3EYLsUluBxX4K24Hlfgi3g7bsGV+CGuwjDp8z4GV+NxeBc2xbu9+ZF7QDxFJz8tZExIS4zDVvK9REJ1nH85RGBP1fsljsf22B5jsRN2kHLp6D2O3HdhH53jxMtxErAjdsYE7II98BTVcZz7OU43OU53OU4POU5POU4v9VgAOU5jbXnIGJsIPB2Pxb7yvRTCLvneJPleAxwi3ztb4h8h5TFSyuMcHISj8AxMwQtxtOq49oTgxx0nxx0vxz1Pjpsqxz1fjnuBHHeiakzHLjnuBJ33ZwyW456B0TgUB+IwHIpn4nhM9pab3E9grE65DZDjDcR2OEhd/zoHr39NpP4dj3F4gup71fK9bjrfayPfa4tdsB0uNMZCGGMhgoyF2FYUYYyHqOV4iD2UWfTFEaYRhGJCGWEzYR8htpjPCQ7CcsIGwk5Cixm844KQNsMYJ2FsxmZsxmZsxmZsxmZsxlbX7XDN/7f3sR2U+f9fqOb/fyZ97X0xGnuhVZkXebK3fV7Vm2uqsX+9mfSPavtzZS659KcqfakkRjU/W9vPmxWkn9eu089bHKSf16nTzztf08/r6U9I9vTzynf7BPbnesusUvrk/5R3wv5KSOcg0bGqMitQuvA4XghlJn3KAWWQGqQM0nTykKXOg6pP5HTXZ5zAqbYZvrEO6rwZ/SRGP8mR6ycZm6J8Xn/Ruj/eWZH47G0Dfo+OS+i8s279JGUm+d3CvtLO38TVrs8m7ZfR2BTjsTmasQWOxpZYgK1wNbbGe7ANvoLt8C2Mxp8xBn/D9tiK+GLxZOyAXbAjmjEee2GCdw6e/FbgnzpzU7tKOrvjGOyFE/A0vAx74xXYF2/D/rgGB+CrOBC34CB8D5PwCxyMe3AI/opDcXmI7bL2Neyzmvao8prbaJ+y+9ppN68+uG21O1b/t9prW1CuXQh67bZD1hx42+3yNYeu/XbDdncb7qY1oc1pq17ja8fdu8a/LbdqRkSt23MbldfcphvNPsm44ZbwI962m1YeevvuDsqj3kyjndbYjM3YjO2fvB2+5/+Mg/L8/6nq+d8hz//phNaEiwgW5Z5f/fyfYQv5+d/zLBvX0n98farO821akOfbPjjc9dyaYc2Z7Htm7ev+LC/dYTyzGs+sR+6ZdYHrmTXy/Y3Twt8+9/HHpz704rBHb3ytbs+sfUxyrWG6PAs=
*/