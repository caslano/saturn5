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
lC3UQfq9ydMvdKOk7/psWSBEo/uT80NjN4uyab3j4cCG/02TjqKYc2WcMDPVP1jcCJUQMig7ylJEhubofLsjKrk0b+FF7Yldh5vdnGCiIY62fwsngBOlVEsuykW/4V9epQkSQeQGo6XSLDd+Wnk+zs17NdAWTcB9WqWv02t7gEthsynwxPo9Q1/JytXi87n31flKGOhlh0FP1qn2gMWVNCUBGkj/ftQf8xbqJ+WsFcqzP2TRZqKoI9RdCDcldC23UeYPSvSmU1PeonRY2xc2YIgf/tE5qRzy6GlYENEfa+268CiXvMobjBnZplfQkNfQOzzsIdAqYG7UiU6p9cxh1WEx9IDvE5uSZshlUFQFy909VEzQvKiG64v5RvGG1k+XSkcPcgGvd88jk4YI5Pnjx85Gv2M7wwBrcU8UIVKU/f4tcZK0Ow3F5TWS+2isDk0j2bf0mLn1oTQY0anlggt+iXDZBxblrd5w9HcpoyRyRsSaZ7gA0iWNw8l2JVBQgZyKpgUTw0P3tj0yUHg171TjRufTkkkYAVAc4mmJnSky6yuGAuvpiji62kuoZA==
*/