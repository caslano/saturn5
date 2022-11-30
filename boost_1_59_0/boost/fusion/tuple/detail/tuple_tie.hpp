/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_TUPLE_TIE_10032005_0846)
#define FUSION_TUPLE_TIE_10032005_0846

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/fusion/tuple/detail/tuple.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/tuple/detail/preprocessed/tuple_tie.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/tuple_tie" FUSION_MAX_VECTOR_SIZE_STR ".hpp")
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
#define BOOST_FUSION_REF(z, n, data) BOOST_PP_CAT(T, n)&

#define BOOST_PP_FILENAME_1 <boost/fusion/tuple/detail/tuple_tie.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_REF

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

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_FUSION_GPU_ENABLED
    inline tuple<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>
    tie(BOOST_PP_ENUM_BINARY_PARAMS(N, T, & arg))
    {
        return tuple<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* tuple_tie.hpp
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
*/