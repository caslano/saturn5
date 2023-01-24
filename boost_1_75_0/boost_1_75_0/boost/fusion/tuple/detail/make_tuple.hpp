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
o3CMJeddSh8qMBOMKN3iSJ3vGtJ2P55qouG1Pd0lv+pXNXExLuRkn024NeiVXHv8v5ozw+YIuPRpEeQtP/DNxChW+9APS5rdFAf5qgNOBTzM3QbA8dNIrvrDCjIho0NpdZ8GD3MbiOOU4Ed0sONey5Ojn96bitVjUlwTnQHr5VMyU/CuxZi5DaCqoA/RgyIUzNQnl80Qvjh9GF5cekVxyL6bboZm+KDhHlx3ILqbQ5uvbyJ+ve0EQ5pnhFrCXpW1cZ60QRGZI6d9MGF6VUE4zsPUc0O96BCv+82dR7rP/j6cL5hdkZmfxdx/4EYZ3eWyc1M4IWGzd8h0MbCzrYb7+ILH9bfOwCcD6DyaPpPVGMsitczCnHIDU2+Vu8fWyuKZ/qtdsyHWkA8jkUYz72SQr5E6xYR+CuBlDkuRYiYlKfDyPym8VEtHnsZdg/3r89snpPuqnL9bG6wIRA7dmWQa+Trz46Va9heAnFpO2ifiPczmGFFMAyj/WXxjjsJHCvMvD/ITkFTeHAiq+tjcIxTFRoWVxNH6w3BhbDezAxsmKmfgjoFl/Q9k26NqghiCakuTlz/+ovcF+w6l23F0G/UR+mHwD/6BJM+BrwFQyBHcISGWxDhN4nrE9vRR39z0ZFzNXfpZmQrigiH5Mx0Y/GmBlViuvd4jnyTFD1/iIHNjpNa01g6nyRlkTPyv+tBiSQeWZWoHMtto5/eyTUiy
*/