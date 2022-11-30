/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR_FORWARD_07072005_0125)
#define FUSION_VECTOR_FORWARD_07072005_0125

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/limits.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

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

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vvector" FUSION_MAX_VECTOR_SIZE_STR "_fwd.hpp")
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

    template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
            FUSION_MAX_VECTOR_SIZE, typename T, void_)
    >
    struct vector;
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* vector_fwd.hpp
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
*/