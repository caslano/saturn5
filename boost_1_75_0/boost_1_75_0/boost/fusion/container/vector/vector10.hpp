/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR10_11052014_2316
#define FUSION_VECTOR10_11052014_2316

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   include <boost/fusion/container/vector/detail/cpp03/vector10.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#endif
#endif


/* vector10.hpp
e6s7NKvPd2T1GYnNnbXOmiMBk3fMYNVTbAHV8cPXRiuONdyKM4xbcZaBFecdLSDBddjBl7/GDl4peSOtlEAaLEdKOw7zEBhM5qGV5myk/b5qFDqh/bPHoP1IbH/S1yRQvopfI5naGcmaLk1Ncl9Zyu1A9xF91y0y67ng+Cw0cDE0gJiJksemr7XZ6AJWoPUxTAsCKYQ+P0Vd/k03AnmOwVC++spoBHqfjEAGy5OQVSdDky83ZQTS7T9vt2nG/vMt2X8uFvaf17g5YV6bZuw/BLRcAO19VTeRDGrTjP2H4MYIuMcMcDHNwB34huw/Am7Cq9z+83nrZuw/BHS0vbD/GBp7phm4qQT3roA7vkaHm9oM3NUEN0/AbQQ4JaUZiH++JvuPgFiyhs/92VbN2H8IqI0AGmno3q5W5zYBLSO4r9pxuEvWhNiHizRfAIxFmBdqAXoVFat+jFI8Z4J9DjvxczLrlKIBaKtuACoo5fYfM0fVAiqYojJS456EsvdLR7RN8bww/5hDzT9zyPyz1Fa22+2g/VR6+ipPTNALjcf9iXafeKd3YTcTN/x0O+cpDMaiYtvBOUFYfp5OOJflp/ArnKf32gq6evxlbvkpSmjG8tObwBZoYJteNpyLaHeSyKXtlxxN+c8wKP+Hudnnn/d0s89qssR4SxpMaPa59SjZPTZssJgCi8js88+jLRjFOL0XjQPH2A8yDkzZZBF3
*/