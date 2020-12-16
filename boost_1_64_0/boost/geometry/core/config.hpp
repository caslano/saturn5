// Boost.Geometry

// Copyright (c) 2019 Barend Gehrels, Amsterdam, the Netherlands.

// Copyright (c) 2018-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_CONFIG_HPP
#define BOOST_GEOMETRY_CORE_CONFIG_HPP

#include <boost/config.hpp>

// NOTE: workaround for VC++ 12 (aka 2013): cannot specify explicit initializer for arrays
#if !defined(BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX) && (!defined(_MSC_VER) || (_MSC_VER >= 1900))
#define BOOST_GEOMETRY_CXX11_ARRAY_UNIFIED_INITIALIZATION
#endif

#if !defined(BOOST_NO_CXX11_HDR_TUPLE) && !defined(BOOST_NO_VARIADIC_TEMPLATES)
#define BOOST_GEOMETRY_CXX11_TUPLE
#endif

// Defining this selects Kramer rule for segment-intersection
// That is default behaviour.
#define BOOST_GEOMETRY_USE_KRAMER_RULE

// Rescaling is turned on, unless NO_ROBUSTNESS is defined
// In future versions of Boost.Geometry, it will be turned off by default
#if ! defined(BOOST_GEOMETRY_NO_ROBUSTNESS)
#define BOOST_GEOMETRY_USE_RESCALING
#endif

#endif // BOOST_GEOMETRY_CORE_CONFIG_HPP

/* config.hpp
E4ltiUnEDsRkYidiF2JXYirxdGIPYi9iGrE3MZ3YjziAOIh4FnEoMYM4nDiCeC4xiziSOIo4Bhi96ovIZ3UHPkj2VnVJ98q6uBCUnyAbS/UO3lbozNtR7DV69E2Wq+ucHXvmd5vlqnjbsruw+qcWUL65Ntnp7P/YayC2gdhYhybvOdY6FL8FBhNXFs7aPMZ2s/SSCJfSAImn9s8FRioYMlyBd0C1s9m11+KAAAMISzFyEwtnFDn27fTatws/Sp/tnhn144wuolEl2XAnuu3jE/e67E6fSEuyB3bt9tobvZn4oc2XN625orXLndbrI6e9C/oV9/g7uevqkmftqwsG9/hteyCFfXNy097JLdM5gv5BahMcrnFdkYTNQuKAuHg88/TnvnzR872l4pMZrsL8ij3Fc32zjeaCzDcqPnf5fTgW2N3ufVfFJ7PnFnvaNbkq9sz1Fc/Jh3IR8B9Ad07F7guK5/qd9xW0217lSC9otw2/68g34nYOslmMT4z9osYFhK1J/onuQPsV/fHRXYFGR9/d54HavCpuDUKNro0HT9OA0dPjbRBxNbpUrNPjHv3iS9CTp13b3Y0jKvyTKnD+om5+O0S3IuZCxIR2lNMq/m5x7nZWBC3O6ZYy8XTA83J41iRQysfuxf0zNzvvQ97yjTckb6EMUTycRLAhwiBEcK57r8v8uQ1xH/VTddQQZ+IJHMHi033+ZGCP+ROQmHWbu+7tNHc7EI6KHg8hakyPHxXvH27ErUOMQGNiQ9yv8SDnUFVxv8KTa299mq9zoDGtIW4lXuPosQJP5ApQDAi50kxPuRqDEzK5k9A+0qgLKZjyixU2bgVTbsNDMOVuvjaua+OwqKtFN8ZvuB3Rh6RekUzW2m4WuesgiYIvgcdjzw8EUcz3Btos5p363DfLXRU3EXXursazSGXB+9sIgCPCHDjj7WG0TgmZi+dH4dMQdzNckAu03HLVcuG2TD/VUOHQ92qF+uYmidngsNpauBvtbX0lYa8jLeRohePf0rUjIm4/w4qjMXT+4xJXH2csobARc8nlSCk8gujqGaCqJ60zqydR2o7RyPoZj2ybH1m1SEGUerjURzWedf1sHMD66Q5nvC3vL3VS1j9UJ3P6h+pkQf8j62Qu3AxprFVdrHj9ey+UdP3FB4MnJ6WH4mdF+mzLbz2pU7gwubowN+D3zDOtkY9dPKDlx/68PwszYQAL83Q/Kcwvgaow9+JJihAA25YF8mGpes8PYWB41c4dFrQ18BpsrALyqbYq7kbEiy72tXhHsXOl2CFi02aJl4bQQImXDXt+b0PevHCvM0Qs/hhE9AoZMajOcUPr2NK8Bck92hPVtnTyv9ZAWhrNx47KzEX/C6bEGVIvT4mGTcqyxvETTq2DKZ8vgzsqebg7MDM9Sw6r5WgKAbxycCk86kYDqcblZUDmZiYbTNkk0YypSmjZsc5i5Hw4kosbGe33kovMYIhqHSdgwZRrdD6yw/lA2gZ8I/nYJI6lLfMxBtGCDWBUWfyY5OQE6KGlr+CqLDvwvtU3QKAr5G752kbmZbOwEELq48w/ew9CQ1At3TzGNrGb+sjagIRLfJ2DSK39RksZgWmcJtMUs33mZvOyKQeD4MkSzstt0syvRH9ZtrMSjTz3SWtg9MZBIrm37doE8Vsx8WCwIe5hOFnJxXmpRPVdaJZOOhg00wSuG3dQiPLPmUpRjL0ul/M5J8/nBprv85d8afD//Nv0f2sK/G91Sne+dJCajnKHB5dtNfsgmdwlkMY7C0T+5qAJinw+kAX5R3L7ds94poSFSnc5zKy48GAQH4SS0ERO6o5g3HMYPliJEWkjp5w7MlyvqdKk0nKXfWLETcY=
*/