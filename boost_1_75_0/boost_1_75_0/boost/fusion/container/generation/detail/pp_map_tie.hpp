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
6P5bo80XRGMwGSp8h9hVjcDA9Cg0/yVdmjfhtwsRIs2d2IgQHMv52Z/ApeGXIZyaUCUiAr0gQS6esEoBcLIAnHeRMP4+KFUS8KwClv1p9CcYV0eOfxGDMbXe5NtWrmfvgar2Q6MaUMLU7lvUQQz7Q57dNPlBlEanHP46lEW2MOa0hXOVUD07WM07v4g5Zii6RCuyReN8cqK4uT34k+miVub5r0v2U9hPHl6GjP0zgnPcZdGZlCF0CM6EV3c58FRHLiQBo3JYZz4KbHvgJPSqIpFwSJ0QJzuYRK2NtQCdTq8d3TKEYu5lEF5KXzQfRTyFJxGnaY06njDmgGpUq6iAHJEQp0kZH68HYMhxqB1I99RxqGYVsBRXAec+CbjY4cQ3XSUQTBxQ6JXGCgjJNsf97YVguB5gfXW5C2kyTQVi6QloUvwLCuDqlAG4iidc08CJxU7wIO9pEakvzHA7e0klPdASesCbnkBEdqQhTBOF0QmE3BjM2scfgNO/L9W6UybQeRcJt04FOv8nu0ZAb/MS0CR4XgwSrpsBqGtCirdQ6ixA9KN1aB49EM2BO6bCgplxx2Pgf6O+SyTcPgNa5Hqt2HV4hQVot1yHFtID7UQZGRZ8A3c8BP43Wj7bgBYyAWBijXTTHFkAMFFWRw+AOXF9C+MC1wjhxKQWCYQw4hxabkJYEcIhakUGJ7APZMB7WVzdv39RsNA7GNNRohkJ
*/