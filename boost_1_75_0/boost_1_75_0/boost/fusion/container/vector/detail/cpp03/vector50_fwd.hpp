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
IUnYhEJCTijCqqI6BkB1upOJ9R+LKTwfI01Y2ggc87UjmojpSGhkOfq2NswSxrwhxhSEdYS7vRDoo86EzpaoA/n5ufKp62jgkq4nShhzaho/FGNEZ1gVRyH2t+OxjwWu5/ESjMAMq+MUIZ/v4v64i0FABUcCwhx+QBtO/CnkOiYwwtMbfsrOK/qHMyzwTGms7+VpBz4GfS+P0uewwvfxarm+F7gDkl02cbybSmbWx/nmJWvttyaTOBPVjkOp3D0GJky+BlwtTuXtmYX33OpfbeKYkZTiPE0pzjMqxXk6tJNrxa2dXC1ukQUyUizXi7vBhWdMN2nfgOv7EebJ+kQbBLrZhB1s6/LCAkFYQpwLjl5rpC5xfIo0qpSvvc1v9tAO1Zbkpr0QSgC5r2ywgG81YGtj3+qxudynmj9duU3z6SPwhNs2n93E776PaiovENmyDr+h7YiCLLSVsL0Qbiv545qmbSWSAfXBpeipaoH6/TnqZxhQP4NjbBJH/YymUV8KQ32J6/Z0RY5zVazoV476qU2ifqounOmon0oSmkD91Maon0990HYrxxovR+l8ROmDHPXzDJuRyk3m5fKw3ONhFqFUg2fXyz+FoX6qhvqpRtRP1aHPgfqnOEZfzOYxC1xtDuFsZlCPfmgS3/M0fM8LxXdc8L97GzNYNcLsDO1tRrhcG8ctSDq+ZzStpmPKq35/0cX7SmH1M1hi7hjG
*/