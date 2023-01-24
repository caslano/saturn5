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
iLysQ1dKPXfaN7SBrRjJD9d3aofr8UzPuRL9PXO4v6d/dBP+nsWjwPIuTvvsZS+beEw/jV0Zz9M/RW+6JRTVb0yBdqYeZxaenrdrnp5tDTWHOXtOaboudN/iHIjOzh/rEebKWd5DnLfP0w/hi3uE+XdOCwGzqo5ceBHsozqyNPh+vMYU7U0Sf9NFe3M+R9BXjlmMB1EhhwOLslHDKMk+53m974Vmz+tfS2ruvH6wPKSYjurnJV2Idf/Mb6QKNT6q75UZlm+70Tl93fOGc3q58TG9KSn8mF5eWCxO6IF9ZPrmMPlxmaAgC40n9Y3O5LfuZYiRJe/Nlu8nO9DogqaO5jN9C7U6G5/MN4Jv6mg+44oLOZrf8R/LeY7mH7kRl9p/Y4jPQ5M+NY+uNvrU/NDIp+b97o18an5yQ6LAEu5Q86Gr555mHWrMSCMWlkAo8KdGGr1pPoNXSSNgV9YqL46E5zJt3z8KaoTmZdOEL82WWlyWPTk0rS6+LLj915mES80ITlhqlXYj9AYae9U0qijUrebZyxu71Tx0eYhbzfzLL8StxhK0NO9Wc1jCtdsvnX/tjjzX/Nqd7tbE2qUYDOkXsnxRuHxbS3FmapUjeY1WsHA4reAPef/TFdz3P1vBUcP/Fyv4ddfGK7iva8gKbux6ISs4OHCeFWw7FFfQPjTE/8K4cInPhvH44+E8fkDXc/H4MouFwrwkZ8olDU7h
*/