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