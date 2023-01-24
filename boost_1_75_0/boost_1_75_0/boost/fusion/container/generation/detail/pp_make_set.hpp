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
sZf5qWLth/LdsTucAZslt+4UNGR0vb+BlTIdwCbvmiYLgWtZB/++T5oEadEmBr2OLiIwYvtLNjHa2ANO7y2fCkDjmkGlwBi12yuX6O9M3q/Bb6URhhydjWHkAo0DGklLZS7pWoPXswy6sbep9m6Qn6cnRP3o/kPq9Of1FxXHs0vSj77yIEHHEHp8/+cY8YGTGurIWl+qikq5N9nbUwq8N0We5fCNnGiJl7t2Ulc1vMfGO88ftY1PwcKcq6AXsRWw7E5EXPmk84nGBN+oNjThihZ7HR1P4FAbtEY/wPKtbNVBT9VfEzDRTPhK6Ytg2bA/nWrVAMGxAsrCjq87votwDmFH8CXtYOYdXxBCwy93A8IKayDIhgdwcHZnafZhiNI4wjmWGsH3SxvoANNiqddIsfD+kOy221MQFAMEDwsYRkLTegA/IknsbtjqBqA4AUkEAa2vMGkqcRzGSOibTaCFFrf2cgNgSwLsNSGc0ZOfOvoAiQqoMh8hQPQEyozIE8LA9U+gFpSEgCEkNL8H8m9q3ki5YySUHMFHXKK4DXBrJFjdG7i1Cgy8kgxQcsPAe9b5BpxMBi7aXoRj4Awo0N8+IFSQ0EiOv01DaLTAOVsnAL6yOGdPJPQ6QtjV+Z/XRBkVCrTRBygIElxy+XQYcc7VGHgtGWDtjoEPrQN3iaud0zMFYlJWBN9IGvDRAOdMik1jxjlXYuBVRBkxae//
*/