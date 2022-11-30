/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_MAKE_VECTOR_07162005_0243)
#define FUSION_MAKE_VECTOR_07162005_0243

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/generation/detail/preprocessed/make_vector.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_vector" FUSION_MAX_VECTOR_SIZE_STR".hpp")
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
                FUSION_MAX_VECTOR_SIZE, typename T, void_)
          , typename Extra = void_
        >
        struct make_vector;

        template <>
        struct make_vector<>
        {
            typedef vector0<> type;
        };
    }

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector0<>
    make_vector()
    {
        return vector0<>();
    }

#define BOOST_FUSION_AS_FUSION_ELEMENT(z, n, data)                               \
    typename detail::as_fusion_element<BOOST_PP_CAT(T, n)>::type

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp_make_vector.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
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
        struct make_vector< BOOST_PP_ENUM_PARAMS(N, T) BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(N), FUSION_MAX_VECTOR_SIZE, TEXT, void_) >
        #undef TEXT
        {
            typedef BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)> type;
        };
    }

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>
    make_vector(BOOST_PP_ENUM_BINARY_PARAMS(N, T, const& arg))
    {
        return BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* pp_make_vector.hpp
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
*/