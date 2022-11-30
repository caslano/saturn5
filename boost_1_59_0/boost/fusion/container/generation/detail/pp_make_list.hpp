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
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
*/