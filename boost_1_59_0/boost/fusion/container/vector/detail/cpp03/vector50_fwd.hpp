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
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
*/