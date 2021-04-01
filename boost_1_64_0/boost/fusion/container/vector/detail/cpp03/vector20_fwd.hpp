#ifndef BOOST_PP_IS_ITERATING
/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VECTOR20_FWD_HPP_INCLUDED)
#define BOOST_FUSION_VECTOR20_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector20_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector20_fwd.hpp")
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
    // expand vector11 to vector20
    #define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector20_fwd.hpp>
    #define BOOST_PP_ITERATION_LIMITS (11, 20)
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

/* vector20_fwd.hpp
ecIR8BNRo5E3Q7ZdydnT1AURX2z6bbUAeyMUuSPHUKYbuSfjnZ8oHwDQMOOaYgpOwmz8MHjKHJ2s+iq7KFcT3IvecYaWKJT+yG8VaGxIj/GGJmuv8aUTaLP+Ih9i7myOmDEBWcHZ0wWwtcKkSFjUduUf4eIoflGslvj+WpuAHIt1vaOFOT9P0JtXCf6r9zwanbL2IqMp5gHlOoqqsYMl3nLJxDpcr7JDAdSHEGEraVeO7pv+Q1MAsnOl21j4+SkfcDAREzlbe+zUdAzjg3Nj6dVYXGJ8+enOkUgYTHl81VmxYt9WMqMrbhwahuJnu3QqLgy9ADzXwmthLUj7TGg58NriYsXVqjU1IS1NRETdOfiDRYbZ0iLyoecGj/FsOTymFxUQylXvcmVOgOiA2Ej6e0a1QNxjxVddm8l8OSQnxfsaOiU2ybKigrc46XmScAc2KozE9K7CLlAClxhlSfRNSU6wGBeJ8i8Gr0oJQyzNJlsJIbxF3g0KmbZbZ8CkeJNkRDJVjFeZoeJcoauDEr36k9IwR84GMFKZSjidJ33zcESXAtTXF85dz9UlZw==
*/