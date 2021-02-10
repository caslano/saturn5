#ifndef BOOST_PP_IS_ITERATING
/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VECTOR30_FWD_HPP_INCLUDED)
#define BOOST_FUSION_VECTOR30_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector30_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector30_fwd.hpp")
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
    // expand vector21 to vector30
    #define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector30_fwd.hpp>
    #define BOOST_PP_ITERATION_LIMITS (21, 30)
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

/* vector30_fwd.hpp
6FdUuyrNvWGHezCzSDnBzQsri2M5G/xMVcl+NtOpy+h/r6iHZafhxCsXGz0xMKHIJdfIHVU832QeIR9GMdC4P/CHtekj9XsfL5swX7m5ClEpR4FRA0Z88NiOfEZTU29urkyb+Pq1yOwq+O1KbRJ/0CagL23UNKtIWpW9co8XFMWpCFbxiHFTRBQl8GPLpbQxwKiI3KLIgA4qZ7yy+WFlc8ekACtws7ikKa5e4Z/Tfi3lxVpNdrpzZUZkJlWoDpkusWTTkqMzioMP5USpVhqEJDUKJTXqCwzIOBNOUUOisk7pvfVGq2Ec0dBswaPlQ6uya5wonl1rnbpr/LCqO+MpfO2IaVnRmXnsHWJVbsKV/VX5Rm13fmkov2/t96O6fwaRSwO4zYq9r5qTbVq2qNmLvarZZileSXe/ilE+kUlumHfIxDOOsrI53uqoDzY8dKsn9FtGedPY4T5DSq06kC3u+XbqCpuif3W06bmuh/uxY5k71Jz9LhvTreFSFU9Z5fVyXVGgXsUgN8zC+ydFVKq4SAMBvBiu2zttn7c+48oKUY36ts1iJL26dQmDlOSNxGwj5z47kmHshbHrBBkacjWX9GPkBHshvaoCFSWaaEZ8p55amFNOgBZUcS+dLtgE36pb9RghXCmFqoJxAUh1
*/