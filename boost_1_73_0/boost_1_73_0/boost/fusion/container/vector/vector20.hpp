/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR20_11052014_2316
#define FUSION_VECTOR20_11052014_2316

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   include <boost/fusion/container/vector/detail/cpp03/vector20.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#endif
#endif


/* vector20.hpp
rgfcv+ZYsitGR9IdItx3gNm0ZzjOB+bWIbhP4/48MDvzv5zSgKNff7kHpTcX2/kC3L/WVZTZLiuf1McJxseBrlK5ROPjZNw3S+Juk8TdIYGjdvtEDSdu3/skcFSvD0jIJT3+oAQf6asjIj6uPWhe/Xfgvpdj6edHRO1GP+zyGjCnL7Xj6HdC3g3MdTmuqX3pJ+buWVIqV9N8flACR+/7SA1Xrz/SV1+p4ep8G3AflcC9E/f3JXDUbif+/nAczR8=
*/