/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_VECTOR_N_CHOOSER_07072005_1248)
#define FUSION_VECTOR_N_CHOOSER_07072005_1248

#include <boost/fusion/container/vector/detail/cpp03/limits.hpp>

//  include vector0..N where N is FUSION_MAX_VECTOR_SIZE
#include <boost/fusion/container/vector/detail/cpp03/vector10.hpp>
#if (FUSION_MAX_VECTOR_SIZE > 10)
#include <boost/fusion/container/vector/detail/cpp03/vector20.hpp>
#endif
#if (FUSION_MAX_VECTOR_SIZE > 20)
#include <boost/fusion/container/vector/detail/cpp03/vector30.hpp>
#endif
#if (FUSION_MAX_VECTOR_SIZE > 30)
#include <boost/fusion/container/vector/detail/cpp03/vector40.hpp>
#endif
#if (FUSION_MAX_VECTOR_SIZE > 40)
#include <boost/fusion/container/vector/detail/cpp03/vector50.hpp>
#endif

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>

namespace boost { namespace fusion
{
    struct void_;
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector_chooser.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector_chooser" FUSION_MAX_VECTOR_SIZE_STR ".hpp")
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

namespace boost { namespace fusion { namespace detail
{
    template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, typename T)>
    struct vector_n_chooser
    {
        typedef BOOST_PP_CAT(vector, FUSION_MAX_VECTOR_SIZE)<BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, T)> type;
    };

    template <>
    struct vector_n_chooser<BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, void_ BOOST_PP_INTERCEPT)>
    {
        typedef vector0<> type;
    };

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/vector/detail/cpp03/vector_n_chooser.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, BOOST_PP_DEC(FUSION_MAX_VECTOR_SIZE))
#include BOOST_PP_ITERATE()

}}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#else // defined(BOOST_PP_IS_ITERATING)

#define N BOOST_PP_ITERATION()

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    struct vector_n_chooser<
        BOOST_PP_ENUM_PARAMS(N, T)
        BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_SUB(FUSION_MAX_VECTOR_SIZE, N), void_ BOOST_PP_INTERCEPT)>
    {
        typedef BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM_PARAMS(N, T)> type;
    };

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)

/* vector_n_chooser.hpp
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
*/