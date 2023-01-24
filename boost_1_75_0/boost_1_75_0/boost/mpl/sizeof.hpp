
#ifndef BOOST_MPL_SIZEOF_HPP_INCLUDED
#define BOOST_MPL_SIZEOF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct sizeof_
    : mpl::size_t< sizeof(T) >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,sizeof_,(T))
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, sizeof_)

}}

#endif // BOOST_MPL_SIZEOF_HPP_INCLUDED

/* sizeof.hpp
gvK6x8ftAMPSZThJGev0lgvE1H21GhYKUCOTjcisGULAPb3/w6uHxEZ+qosoF5j66CTxC7TaSmjXx9vhRNGm60jlqO15CgiBrwpoDefnpsHI5oCtvSt3uhOHzYnI2Ko4DDE/aX3jvjA+culjfgTHNleNdgHAZZ3s5wh+E6+0FQticCZNzLBs+Y3Z2Rex+ftfEigxw8brnyu2u8hnoli3uyCE0NiGK+MGGNq3U5ZXygUVa1zvw56FGwLVmS6dC98ncOTyrxNJ9B1GVPI/5JT2A7dVdjBK+2Fjn43eaVMZRTQj9TK8s5Vu/8PVdywA3JYeFifcN9Kdu3C+H+1C9v3X9P0Z2A4S63nPKTtZy0DCHeWfos58OyLhDzS8PUU+R6Z9RA2+vAckHfMWM5uLHZVOlSz+vxoUT/kbmzrannR+tbXt67gAPABRBJCTTVKIiNQ5rqhID3Lztj6rdXZN2aFQedp0L5ej7xp3HWs4xklBwOB69JCLmTy6fnq2r5Wrlae56x95c8fYdcVQTCg9UjNn+XjyOfINLO9NjQIVOE1jbZx9ElcoML+s3ZVKA86df7o8ooVZBr1qxJH4pyPxANKIBe2RZfVAyLKrscheB3g6joX7VjxEhfGzKj5fVFv3bSd8MxUR+A7bqrdLm8gKAidu/F0l2vtow5DjUWTLhiLSRSblpEl2uFCecJeuo8qY4uU+yvvUhyyzDqBVcaf4
*/