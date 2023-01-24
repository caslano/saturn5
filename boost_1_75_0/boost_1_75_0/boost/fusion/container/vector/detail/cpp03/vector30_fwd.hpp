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
HumVRhko4mcI4frozVxwANl/ZbXWYYnh9Qmhl+5jXd4HAA0s8tO92JBtFP1T5X9Yqa3Yy6z0Uyj/bzahMXw9vHR696jofs0mIxcNiPM4Mc+59GR215NCjORsehxw2LXIYdk6jkY2jeL+cmTT47plePqx6rA9rDAEHNppBM8EzXHEMrujLQvGEBwmxP8MTaATl32riamymbyrFbHQPD3n4vxULa8N8NCBdyMPTb3byEObnteMXeeZ14nDmpjXR5qa10f+y3l95/zz+khz8/rOeef14RsvZF4dCeeb11/vwnmtu6sZ2YTk3MCHuipD15lRKqlks1oJPWpxo1HOzZBPgYN7ikteJijXFS652tWz1r4BqHjjdBg48ZB3Jcf/svCzD3g0mTQZ74juUea4o9iSfKqikAi3Fonb+VEq5cui5nQ9y+dVMkql1Tit1S6+LMig1nKpVPLkcKl3j3KHG6RSbW2kEKk0tBK2NiX6yeNfkpAd+2hml4BkNYYFOCAJvaSxZUXXS8a1PI9M2Xs6rlvSdOO6hdDDtJ3N0sNbpPPRwxU6PbxcuhB6+Er8uejhkckXQA8rdpxn374ytIl9u6Kpfbviv9y3Nefftyua27c15923Xw25kH07Pu58+7b3HbT+d5zTHpK2vVl7yC1DGtlDvNuA85s8CZJ/eB2ubh4m+JgiycuFmNBa2A+W0CFhNNjGdK37TNaFIMrC2MbW
*/