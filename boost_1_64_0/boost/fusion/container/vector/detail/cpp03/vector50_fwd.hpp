#ifndef BOOST_PP_IS_ITERATING
/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VECTOR50_FWD_HPP_INCLUDED)
#define BOOST_FUSION_VECTOR50_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector50_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector50_fwd.hpp")
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
    // expand vector41 to vector50
    #define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector50_fwd.hpp>
    #define BOOST_PP_ITERATION_LIMITS (41, 50)
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

/* vector50_fwd.hpp
n4F3n7MNeAXvx6sfWW/2Alke3gOX6kNTqKyssnVXYSk8oOJmPEkaHjFIhFq3ZtY0E5d8/bySo+nPOFphoSW9sjcQMkY468oA488PpPlRqbSakefmILVWBoenIeE+W/6Q4M4QD5kb2Tw60wkGGKGCBAH+2vU0CTgrzzV/8HhS48IpS2UQ24XMW1fSihiV8DR+hQxeB5FXZKpmrGDzOHi9m07p/lu0nLVeA4GlV0YQGB+zFotJDnfKOMaMrINRD4NDpSEE3n8VKUZpgglGbm5JFEMHGwmsm8BQ2Pw+PPge+AxarnabHlOxpRv9jMBt6Le5Idf8KQqU9bQynDusDapzLjdF8dD3+KQApeKvB+8lQXNf+enYa2digY7WNcAsqhVBBpMY9HItnebZoNvZeWmUNpTntpyav6phrRdz22XsxLvM5dgrpDANLIhulhgM5Bij+qAKiz75tCnLc0BSXFBDFSyuICcrz0NwgknSggoPnMWohPYOCRpsGKIPkc/ZvZpWpdqC5SVgOqDqwVwwCWSGmuvjriR3isjT+KBlbLBqSh4tAc+R3LjiuCBGjQ==
*/