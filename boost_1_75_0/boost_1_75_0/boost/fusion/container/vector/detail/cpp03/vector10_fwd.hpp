#ifndef BOOST_PP_IS_ITERATING
/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VECTOR10_FWD_HPP_INCLUDED)
#define BOOST_FUSION_VECTOR10_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace boost { namespace fusion
{
    template <typename Dummy = void>
    struct vector0;
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector10_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector10_fwd.hpp")
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
    // expand vector1 to vector10
    #define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector10_fwd.hpp>
    #define BOOST_PP_ITERATION_LIMITS (1, 10)
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

/* vector10_fwd.hpp
Nzab2Mnntdkcvq05m43wfW3eZvPipP+NzWb0bf9HNpuOk5q32XxaEGKz2VsQZrN5qaCRzea1gpBVeKogxGbzQEGIzebegvPZbG4tCLPZXFvQtM3mkoJz2mzUiRdos7n/8mZsNu/P5zkV+XMEku9aK9lsHudv+3rpuWQ+soFS/rqEP4v58yJO3Qvmh8eLBRosoheJyLDOPPZfAfuvWPIthgGmnPTNhHf57D8mezhLMirewYH73qmgxwp6EHI/gXKHL4W9IPfxd0ihfgfRavF2WDllagkydcs7Y7TkGks4sqQqpY+TTy4YLpSHfVEm34Z3cUttAMyoHto+hh+5pSppGVhPNY/bCISQx1kyxGU6AmHlYSAYb6cFLMYKYvhyFV+4Jl/GS77NVZowwT5UGj5U6h/8Mo5pbInlv4GWZeE0E8/o2HhArM0kwsmr9A9r6MMq+rBS/7CcPqykDysMbawwtlFh+FChffDNby/5h+VnpM5NcsdmVMxNUh2v3Goli4qIWBUSb8blm0+5dQvY4v10qJW4hJ4vgs5o986t443cHu+dZ2T71+PhJKBetj9++g8tTJn+wZFKmwPHVPTw4L5Jycr+nSCo4OVHK7kmZ/stZScgrVZbSfPN/AMRC6/1W+kypt9xz/fA0mqJpX2JFKslhrW6uVuezhZqOKTEmSH4Yb0Ppm3BDN8OgZToEIB0iKc46UOi1X4cJxkSJypY
*/