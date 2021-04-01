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
qGLmLPHGpaYmlWlgBYih6cUPpbQ3kOzuKTlu6dD1BcEPT7E3/VIOodFKACdsvTvMWTn8+vrBwwkzO0SVQLqATlSGu7gufFnXZTLjMkVpC2EjzsjcXCmWRES985YhLuZ7V4wx8iG0PbYAzOMsZLKjWlDmfb9z18pWf42cJugBd+Hg9IOZi+rYUnfieDdS1wpBKqdrEFSWRSUTlehe62pglmG25N5wtY4LwnqWabdKy3QxNv2FAiGccisQkAXD2VSjVzXq2d4jig1j/Cxxs6Q9qwOYDUMy4ai7n1eNf5cAggv8V0Npo/eU4hesDEZPLMVD/ObhPvI1EqQ4E+R4fDokn/M4fZtZ5LFMRjZajz7XVQQ3nv2syAkOkF0WBSCBt849tYPhS/tA3CHaoUi/33DbQIzlUrdApSq5AhmUxi67gedyX2mQr9E4yWJBsi0O1Nj9l5VcdYSVaTqr1rbT4oGLqJsryv3e8M8iaM43lM9Tewdcr6VxoP1iAHYPjtfV6lORiinwl2KtfrFP4wn2iGSptiTmWDIzLYpNkIrsfd7OhDuv2tz9gEXfpioarQ==
*/