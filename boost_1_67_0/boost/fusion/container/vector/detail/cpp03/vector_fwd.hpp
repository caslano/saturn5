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