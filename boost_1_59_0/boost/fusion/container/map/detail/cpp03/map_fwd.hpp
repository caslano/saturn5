/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_FORWARD_07212005_1105)
#define FUSION_MAP_FORWARD_07212005_1105

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/limits.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/map/detail/cpp03/preprocessed/map_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/map" FUSION_MAX_MAP_SIZE_STR "_fwd.hpp")
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
    struct map_tag;
    struct map_iterator_tag;

    template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
            FUSION_MAX_MAP_SIZE, typename T, void_)
    >
    struct map;
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* map_fwd.hpp
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
*/