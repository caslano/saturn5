
#ifndef BOOST_MPL_RATIONAL_C_HPP_INCLUDED
#define BOOST_MPL_RATIONAL_C_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl {

template<
      typename IntegerType
    , IntegerType N
    , IntegerType D = 1
    >
struct rational_c
{
    BOOST_STATIC_CONSTANT(IntegerType, numerator = N);
    BOOST_STATIC_CONSTANT(IntegerType, denominator = D);
    
    typedef rational_c<IntegerType,N,D> type;
    rational_c() {}
};

}}

#endif // BOOST_MPL_RATIONAL_C_HPP_INCLUDED

/* rational_c.hpp
vXuRz8PH27a1lfENDY117jDDUV/wlRLicLw20dxUuTGia8e4FqtiFB+t39Cga9/iGpfc+6eWOPnSz7h8rTEGLfF4Y8KMpr2+6jsZmp1Cfc8CrlsDtsWeDGjOTVkNt1KSxaX9zOQzg+j2M6e9dPR90XoYNkbrI6a8DdGNnhy/ceWI23Jcy/VC1t1uao40tnITQw2YoVaMuyLyzmid2FDP0EsyP5jJI+7aQ/lefLk7ZtvIbRVi
*/