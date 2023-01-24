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
Ff0O6T8tIKg6AynpqK1frEBsDJ0SGwAKQSiXKKrz2FMOMDmQdW0rBlcdAzVLomYgP7lVsbzmue01gtJJKwZIkEBxBrFefL/4bAST8ty2xWdV1VTqiUg5CflWkEBBeHQItM+DGwctW82hKCdGhnydU6PW2uQgzsF8lJ8kvMN1nDVKhKNLbbSOu4jesXX88xKdgonAKUS99pZQgpOP55zzjiQt8f5aI2thS3w6RWW8p4qtcRV05PjNfI2tGNFTPoW3ISE/fGFaur1sJZoVDhIvGQ9Mjf5svTjKJDpuLwPN0uX9VHXJH4VEJYEjvBz/hlJkAW0h/vx1ELSy5/5M+wYT+y8uIavndhF1eDfGL/a05hYyiXWM0ZDrzGSau7c0Cg2VuH/8GLtir1LAOsQUoekQO3h4MXYF75n7h9ZJpw7nXPpTTtdfOX7mgek9qRBUB+dG4Ek58ocueUyJmtee0PYECLRM28zzTEKhF+o3sfqx5pA6oMFGlaAvHUcXumG15CbO0JL5iObcJHKMTdJL3RZeKo+9EKgiwQoNhRLBjvzzNVolHenRlu6WcTQPwSHkgmvb6zjUZPAk7xyKfTSn2Zh/JIlb7vtUsy8BH8+GPG/HEaNKGUaVQn+fG0nySr5uVcrPKf/NXvYE3jy1DB9GGkbiuaKmoERyD7+mSioMmFJqr4czhyGwstKlX0ld8S6pFJI7AYwsXKUuwKryKMoh
*/