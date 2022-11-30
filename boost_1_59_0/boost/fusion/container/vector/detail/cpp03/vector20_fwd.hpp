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
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
*/