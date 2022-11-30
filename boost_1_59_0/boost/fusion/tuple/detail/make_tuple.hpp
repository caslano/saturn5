/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_MAKE_TUPLE_10032005_0843)
#define FUSION_MAKE_TUPLE_10032005_0843

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/fusion/tuple/detail/tuple.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>

namespace boost { namespace fusion
{
    BOOST_FUSION_GPU_ENABLED inline tuple<>
    make_tuple()
    {
        return tuple<>();
    }
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/tuple/detail/preprocessed/make_tuple.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_tuple" FUSION_MAX_VECTOR_SIZE_STR ".hpp")
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
#define BOOST_FUSION_AS_FUSION_ELEMENT(z, n, data)                               \
    typename detail::as_fusion_element<BOOST_PP_CAT(T, n)>::type

#define BOOST_PP_FILENAME_1 <boost/fusion/tuple/detail/make_tuple.hpp>
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

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_FUSION_GPU_ENABLED
    inline tuple<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>
    make_tuple(BOOST_PP_ENUM_BINARY_PARAMS(N, T, const& arg))
    {
        return tuple<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* make_tuple.hpp
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
*/