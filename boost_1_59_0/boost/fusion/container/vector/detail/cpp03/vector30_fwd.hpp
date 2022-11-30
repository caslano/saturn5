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
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
*/