/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR40_11052014_2316
#define FUSION_VECTOR40_11052014_2316

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   include <boost/fusion/container/vector/detail/cpp03/vector40.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#endif
#endif


/* vector40.hpp
Q0X5rT9i5eI9OL7L8Xw3AHPsOlZe18B3Dv39g5i3PsjKRf1xfA/gvgGYietZ+aQGvn/AvQOYd/wxK7+1gW8H3lcD5q4/YeUzGvjo+3+3X6lcTe1xL3CH/5SVm9qDwganfmg43wL4esA9c+NwvrEPD+dbAt9fAHfyTe18/wPc+4C55AArjzTwTaABvgXMaX/Oyuc08N2C+wD+c9bHWLnQBxzfbfhgKzCP38rKTe3h4n4Sg/iMv2Tlpv5CPzw+Acw=
*/