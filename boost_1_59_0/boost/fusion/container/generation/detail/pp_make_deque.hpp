/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_PP_MAKE_DEQUE_07162005_0243)
#define FUSION_MAKE_PP_DEQUE_07162005_0243

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/fusion/container/deque/deque.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/generation/detail/preprocessed/make_deque.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_deque" FUSION_MAX_DEQUE_SIZE_STR ".hpp")
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
                FUSION_MAX_DEQUE_SIZE, typename T, void_)
          , typename Extra = void_
        >
        struct make_deque;

        template <>
        struct make_deque<>
        {
            typedef deque<> type;
        };
    }

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<>
    make_deque()
    {
        return deque<>();
    }

#define BOOST_FUSION_AS_FUSION_ELEMENT(z, n, data)                               \
    typename detail::as_fusion_element<BOOST_PP_CAT(T, n)>::type

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp_make_deque.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_DEQUE_SIZE)
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
        struct make_deque< BOOST_PP_ENUM_PARAMS(N, T) BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(N), FUSION_MAX_DEQUE_SIZE, TEXT, void_) >
        #undef TEXT
        {
            typedef deque<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)> type;
        };
    }

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>
    make_deque(BOOST_PP_ENUM_BINARY_PARAMS(N, T, const& arg))
    {
        return deque<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* pp_make_deque.hpp
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
*/