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
WwHw4gRyYAk8q4qYmx7o7lp43BLCImaykCtHaN5IJFva9KPWJozJXjZqJcjb+p1OsAxnPnTb4v35vgxzdceu9hWiBUSFXk3SABDqRO5ryIbliK5wkVENn3XmpFOsN/dkMtSSFXMJeuEl9Y4Wn6OLMa6mKNYJ+M71QcJfATbps2oPnHT8eNGq1Nhn/6GmcLTEfNkgJKT4S7AVULI7rV0hI+3eHApIvFTg4vXeHPhSrvRBq+ypQ56LitK/r7FGRGgSF8YwzLwYdIe/dqqlZXb4L9N8ei4R2C0/ypr4DFjPSxIxwqPrPv+ND/RDMTue13bb/ZmX2O57CoG6k5cl/JLWPcUDaNGizR2z3fogHsZt7IZ+yv4QC7+u+/BB6T+i78mfLv019bfyPQxdmCx3R35PA1V9Ae/zp9wx41aZVUczwJMCT71kgzpdpX35PoUO8kfhYaSDiCFqgvDUtwgfjjWmKiMQQYHie9d/oLaRQvGe/M08vPXzS+VIKpcfnkQ/pmBSqKLHSHKAi2IThw5y/RBk/VIVXxTVWtX9hIpH05kx7KR5jNWmdwGl8koQOA==
*/