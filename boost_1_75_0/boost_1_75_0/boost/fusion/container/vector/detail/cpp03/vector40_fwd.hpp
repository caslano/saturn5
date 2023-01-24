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
zTpxy6HEOPJxkV2G9/mNjEYUDu4xgmfOLEYPipVtMGVgxs4tCD2/KGh0fpGfcSF07UsL0bUSzNahb6mW40SCjqhxjWRxQa8/2GSk16dDc3PUDdQFxXGMLv0hkWkREjKvGwgq6ERGKofjOGLYjwKBbsONeEAfhheJUkVaqaLQUkXawCcOvJAMJd9HNc7fESoXk71uFdnrDmzU7HVkX6NAP3ABE0a9ho16DZ6DDDDe9fiE01LVXnZ/VDM3gPcMQL/n0WinKFayJh9TIddbMcTJSMRgKFAYw/XCsc43x1qQg6nS5nb07LJzo0YCZj0ekQrohUYVNHUOGWDFrOcto7QGhw0AL+3RxdTe55Oab+9yrb0Xii6gvS9uoPZeitTa+4q9cm6LJbltQbdieWehM23CPPujVeD3WdJc41W/ica7X0jjY3njvfXGJ7BXxmYXXEizrqBo9u1pF9DsD/2p2W0RWrO/9g9ttuRCmt2hNZt6Ic3eyZsdrjdbzF6xinb/pwWPP/N7IZw2+ESQY6vwP+TUnhFfjOtyEcaxWyaMU7mwa4v4aVAR8KdtLfhZ4gkzHdsU4Vm0uMCNxsXvtE/IQHgVuGEpBxH6Zm3HU3VHNO9ihpItulihd7GCdzFD7+KDeIahaZqNuvjoVtHFu8O6WKF3cdwFdXEA8vBlwjgKycD5DfWenH2i6/Af/bjzrcFu93So3Y6z8VjVsbWf1URS
*/