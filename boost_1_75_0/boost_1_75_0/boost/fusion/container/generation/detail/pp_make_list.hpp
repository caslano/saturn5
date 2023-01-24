/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_PP_MAKE_LIST_07192005_1239)
#define FUSION_PP_MAKE_LIST_07192005_1239

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/fusion/container/list/list.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/generation/detail/preprocessed/make_list.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_list" FUSION_MAX_LIST_SIZE_STR".hpp")
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
        struct make_list;

        template <>
        struct make_list<>
        {
            typedef list<> type;
        };
    }

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<>
    make_list()
    {
        return list<>();
    }

#define BOOST_FUSION_AS_FUSION_ELEMENT(z, n, data)                               \
    typename detail::as_fusion_element<BOOST_PP_CAT(T, n)>::type

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp_make_list.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_LIST_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_AS_FUSION_ELEMENT

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
        struct make_list< BOOST_PP_ENUM_PARAMS(N, T) BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(N), FUSION_MAX_LIST_SIZE, TEXT, void_) >
        #undef TEXT
        {
            typedef list<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)> type;
        };
    }

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>
    make_list(BOOST_PP_ENUM_BINARY_PARAMS(N, T, const& arg))
    {
        return list<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* pp_make_list.hpp
N66XLYbQskPK4WbI2+T43oeJIye/uV/w6a7+GcrjTAv9de+fR6XGe4vB0PvxQkLwz05RjSOz+47y99LlnmfRN9a5dy099R/90OUyX4/l9h4Ndqq+RDAjY3hW/yyWjGo55+8qFfuOCnVa1dsKF231eUfkmjX2K+yfqrYqGB72/XzUq2pW++F+9tlvoZD9kD+s7RqDTvr7zde+Xe/7Gd4Y9cpz34L7etn7sh/fNGqcROd2Zg3lB1HvI3JLrDexHZHF+1jUk7m6Nbug2Fsp4LPGnO05T4RhWGwqvGBOmKQLnBwTPlwY2aJR51xxLmO0bgdbkWLZbybB9yKj1cq3Mtk3sTiUwPz57kC9aZbCJnYk4Sjx+vbc4Dllu8aR1NvzNhRPbLjC6Qq6fGcRm62j5emRvWMHcxpn3bcAbSv70pa7rocExXKpjYfGChSfiwLt3zUeRirLbYNC9psl3zjCIF9qzjO0/JK4L492F4kYlBMTxb4DQZ/G6zwzz1XS4lw45DnHT+bkgmIl1bbQ/Kka+Rs7nEl8HMs52SuntqsbO6ITfINpsDoDnBolVvgGTq0GEzlkCp2tk706K2iCmMbHybb0TXc0EyPCMeZgnLkGn6DCUKJHjHyg5chpACFjCGwNMuGX+cjxbgdJeWfZBIa8BEJTzLkInxhCij6ERz5hpjpGfMr5jwwEv//FDTP+BAmjROU31Xn+5SU0xxNsNHAQ
*/