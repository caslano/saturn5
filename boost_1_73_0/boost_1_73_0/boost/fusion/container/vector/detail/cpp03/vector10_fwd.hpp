#ifndef BOOST_PP_IS_ITERATING
/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VECTOR10_FWD_HPP_INCLUDED)
#define BOOST_FUSION_VECTOR10_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace boost { namespace fusion
{
    template <typename Dummy = void>
    struct vector0;
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector10_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector10_fwd.hpp")
#endif

/*=============================================================================
    Copyright (c) 2011 Eric Niebler
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
    // expand vector1 to vector10
    #define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector10_fwd.hpp>
    #define BOOST_PP_ITERATION_LIMITS (1, 10)
    #include BOOST_PP_ITERATE()
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

#else

    template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename T)>
    struct BOOST_PP_CAT(vector, BOOST_PP_ITERATION());

#endif

/* vector10_fwd.hpp
68SpPUE2FxXDvLvrQGl3lxVaik/gs8JNNxQssthkKTb6Ie8xyr8nPtq8W9/aoYKBmVCUNQ6NOPwdOlu6/YtLKn7rhBdtOrEgqUSbPqYlOw+xlNUkBHa0AG5hBOFKqcs1W3kFo4rtmccrDFCcylLktkOSjkGNQgw5LxqWsKdqJRrU4/1XxqYKQxi0zSgqXRm0CMyVBip3GZV8Qgu2LbJOhzgdd0BlclukyR0HJwwlsHvyqEYU/OJ58dGVp41uZKqeh9fk+ZGLjOo07WCwJZYrIocflukCQZ4KHqmyQxSMicZvlYg3R1/yUAXbj0V4HUZxk4ywXdilI398NIsvh3s2KYY8xcwB6xsbFd4HtVKyYvZXEvajfQb4Q5aYXVzHeqcBxiLBeU2VhsmSetrpkyJ9cdn7/bN6keBOby/uvPcvflfBTI8uk2EIiSiBatBS73UbqKlKdgmu5+XQdu1scFG3lYx0WWHEDormVpyCYg1AmU7ScjtEti1R013YIWzVAK32ucnt6gOneCvIO8vA2u2Mm2+9L/F5QF808dUmaZVH5ffJvpcnnELud+F+5b/vORb67ZNe97R1+ZkN4YVOzDJNavKRnqHu9thZs1aJHlgq15MsrZTefNwki9MLvHcrAETfvy2ApuIl5p6ORUTZ
*/