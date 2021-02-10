// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/debug/static_error.hpp
/// \brief Formatted compile time error

#ifndef BOOST_BIMAP_DETAIL_DEBUG_STATIC_ERROR_HPP
#define BOOST_BIMAP_DETAIL_DEBUG_STATIC_ERROR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/preprocessor/cat.hpp>

// Easier way to call BOOST_MPL_ASSERT_MSG in class scope to generate
// a static error.
/*===========================================================================*/
#define BOOST_BIMAP_STATIC_ERROR(MESSAGE,VARIABLES)                           \
        BOOST_MPL_ASSERT_MSG(false,                                           \
                             BOOST_PP_CAT(BIMAP_STATIC_ERROR__,MESSAGE),      \
                             VARIABLES)
/*===========================================================================*/



#endif // BOOST_BIMAP_DETAIL_DEBUG_STATIC_ERROR_HPP

/* static_error.hpp
b3AuY1VUBQABtkgkYK1Vf4/aRhD9359iShQVkIPvLlLb5MipiKPtKQlQDDqddJK12OPzprbX3V3DoV6+e2fWuBClEVEU82PtZee9NzNvl6D//S4P+nDyitwnootGFzHX6gPG9v9XR9ETNC+KuqfxFEkAh5CnqAenQ56g60KiPcuQ76PoFNE9a+OvgCPvI76lGQrjyLGqdlo+ZBa64x6cv3r1C7yAi7OLMx+uRSkxh9BiuUb94MMwcTO/ZuLxcWDwyge0IPLBHmqZSQNGpXYrNALd5zLG0mACwkCCJtZyTQ+yBJshpDJHGM/mdzfT333YZjLOGGSnajCZqvMEMrFB0Bij3DQYldAWVErhBJ5IYwmwtlKVA+JGsKgLwxhML3KjQGyEzMWaiISFzNrKvA6CuNY5qQ8SFZsgbtMfZLb4L5M7ElGIHajKglVQG/SBV/pQqESmPFJBaLKq17k0mX9QQ1RlEigNBvOcsShOomlkI4T78vi8DCpSLC0PRpWGqbaZKj5ZSHVklLTWJRFRHWhRoqjMPtRlgtotdpm3FPuaugJ/sTUHvQmoksRAZxTCTdiBtTDS+HB7s/xjtlrC7WixGE2XdzD7DUbTOwZ7ezO9ptZLItOAj5VGQ+QaZFHlEpM95/e7As8L+jC8noTj
*/