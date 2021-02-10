#ifndef BOOST_PP_IS_ITERATING
/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VECTOR40_FWD_HPP_INCLUDED)
#define BOOST_FUSION_VECTOR40_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector40_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector40_fwd.hpp")
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
    // expand vector31 to vector40
    #define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector40_fwd.hpp>
    #define BOOST_PP_ITERATION_LIMITS (31, 40)
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

/* vector40_fwd.hpp
tD0goyAWxuu2xUHFFxeX7Y+d/qAlDiu+pG8CxPjWoH0pnm844cdZPAbcxKj59YTLt7jS6YN6MRrU4dzp/O+2+Fm8eK7PL+iDGx44T7wYfm7Bgo9iN3QnDoGvl/XJTfG6sGR7847XqtjMidbl62bZtBLcMox14evaK0oNuABooCUdiak7eFxhDzhw+yiVvL9sIyiDwa+tbtD+jyvgvVqSWb0SfxtKcuvqF/Xmuj7cNaDwx6krMYlj5TfcBIg1XJeRFa/wIE2svs371hDbvKHq7g4H3LjvbxBNfNWFN/oJ4zn6X33bvaWXrug93rB3XHBUSbEEQl3dJIohvMwF6dqZQtEtjArWRUa05MjlrMgOvoPT3KEDAN1qu0WNtil6dIYS21d33EyTWwp5V4ImMKCFaaEvgS1NVk/K3MbKBrfOBTEj5ffDUOd73S/OL8EaX7sYmuDE1RdqullT2HfeLlw6Xb+7is5o/e3DD75fUS2lMhVI3pFm74XE7BnZ2oukUddllaNZNqolGIqZ8gN4jjceYTF08xD1FV2gaxgXBcq9Z63+ABSerrYjaVFJX5196Og+awUZf+J0DyFdhFmw0fjFT0yzqkonfhCC53XA8iLbnLS77eQwFLzjZds7aWdobPHTOWwKCdWA0Ye1Y9nW
*/