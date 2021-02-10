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
ecfPuEQPuRyFS74sBWtCShP+xUowBhGiPmnu2suwwPqflI1Z0FC1Dqs+kxJes+Dki2VpiEK47EFFCC3GYoriy/67JsSz+OxwVe1zvF8jvGMI6SBxMnWvstSv0atVJZLSUioif10kOHI/qMjfNUp39SiHTx/Fg5y6NqEK7gd/vF2zLn7xqJQkqsxipREO/RGcca25TEVGa8v5kXMzoTaCV/dL1V77F+0Tx8TthU8fmntoiHgyTC3PKhAtHIGyjdFNfCvHhso5P6t5hxkPTTejPMsaymh1yB+r7m5fv2zYr62bl1uw3K2bV494+XD1y3WTCo61z/RRTQbQiLKFtYENFkmXmrPkkEwEio9fzD1OjPJO9jH8/kU8Jw+DOpPcXGQu9b8mo+FRhf6rsgoqsoCtuOndcL8mWl4XMXnQp1c2gj2UflfcLWUX+7V1cfE5aH9uv2udn/e9Mv5WAKPQTXOCTdBUjfCirP0ILwHAR7iCqnNugjFH0Mexif+kKBWMKlbp1U8+UFcfp6wKoyYz99zWZt67E6dIsn1ap1dswKIOXzRalWW2dLHvazHZe2OWbqozgoKqLi3E9t7BdKg9eurzgSMr0ZUtqITfYYmP3DVdu2tUs9aHwDyhxKAR3ROya69FUFGMLG0ZmOqAiAEl
*/