/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_MAKE_SET_09162005_1125)
#define FUSION_MAKE_SET_09162005_1125

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/support/pair.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/generation/detail/preprocessed/make_set.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_set" FUSION_MAX_SET_SIZE_STR".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#define FUSION_HASH #
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
        struct make_set;

        template <>
        struct make_set<>
        {
            typedef set<> type;
        };
    }

    // XXX:
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
FUSION_HASH else
    BOOST_CONSTEXPR
FUSION_HASH endif
#else
#if defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
#else
    BOOST_CONSTEXPR
#endif
#endif
    BOOST_FUSION_GPU_ENABLED
    inline set<>
    make_set()
    {
        return set<>();
    }

#define BOOST_FUSION_AS_FUSION_ELEMENT(z, n, data)                               \
    typename detail::as_fusion_element<BOOST_PP_CAT(T, n)>::type

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp_make_set.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_ELEMENT
#undef BOOST_FUSION_AS_ELEMENT

}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#undef FUSION_HASH
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
        struct make_set< BOOST_PP_ENUM_PARAMS(N, T) BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(N), FUSION_MAX_SET_SIZE, TEXT, void_) >
        #undef TEXT
        {
            typedef set<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)> type;
        };
    }

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>
    make_set(BOOST_PP_ENUM_BINARY_PARAMS(N, T, const& arg))
    {
        return set<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* pp_make_set.hpp
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
*/