/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PP_DEQUE_FORWARD_02092007_0749)
#define FUSION_PP_DEQUE_FORWARD_02092007_0749

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/fusion/container/deque/detail/cpp03/limits.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/deque/detail/cpp03/preprocessed/deque_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/deque" FUSION_MAX_DEQUE_SIZE_STR "_fwd.hpp")
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

    template<
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
            FUSION_MAX_DEQUE_SIZE, typename T, void_)>
    struct deque;
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* deque_fwd.hpp
Q1ODrbC2Agolx2Wt3sfnvdYhfFxJEclOqBMnrKpbS1wCqiLg/ypHn1Tuigkpl9FgOUEH71ZVMvYuzPkGHZQL6TcBiNBOB4NbGDReDFOe4bdYUcxXT25cOuMUm2kBwxhVfDpAgtj7FUbIBHc1FaJkUEmAdgTIEGGW3upjL4ilWD6UAQ50Ii6BV1FqJPaZ9BCxzmS41lKwd6i7L08vL9T90M/RHFPJxQhG+bfvcqFW8WtO3//gBzPMA9A9atQmFQz06nSfSCcfbnY5eqSd3JkA0gB7XftAMPKOGLAfiAH3HtSGqqKey8j/reIM4fMSkFq9HRzpq0TTRyNLHg+jxVotc3MVdsdNkp4Tiyuai7epkvDJGg3GvzGQKp6wVkbSvIIBtoF1ba6SBzmFZm4rz1HGUyQz2DKW7RXX+SJAYil/FFSf0GkELAX35JxoPzANzwIaP5SXEqf0deBWevFVhb41EIsNRULWdxQC71AEaaZzNeza217qcFFiEaYP+dB5VvS6L1bSUO3G3E0eU6hKEwCCEMsgRqzduRve9KvBdmkvu7w/lvMpOtn1Eg+Qyw==
*/