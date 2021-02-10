
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
LW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4MzdVVAUAAbZIJGBdUtFu2jAUfbeUf7hqVfVhQgbKtImaiDQNI1pKEHEn0LQHN7mMqEmM7NAufz/HBFj3EsfHx+eec69ZjbpOhUaXsLzaSrO8YvMuVaZdEj55S5J4SWQ/4D3zOQRrHqwWXkRWM380Gg4Jo5cLjB41yDW5hgTVG6qezjMkTOG+aAxBWzAtM5f8Jxcso40tESx46Hs8gE8dmK0XRfp7MgGv3x9C/P0jK5XlvsAaM1P9H3WWiVq4ZKZkOYYSp1qW+L5DhQ7hcgxb8YrTSnaIQ15k1rRrr+cQgEYelAadV6k5LswBo0c5RrsgNqFf5FjVXcLUbs4RXZKXYn/25BJglSjx2FTAPzWqShQgDvXOXMtTUeeyMiR6ZAEzuUpRmSS3rdCY0oNRum+jT05Nm97M44SHy/FNK7qMV5x+vftC75+8MAoXj8F6Mrg1Ds5K5rczae3/QJVvG2iTgdgaQ2C8QPsgYCc0vCBWcKV3sr4i7M1yjcReyVqmsjDz6/cH4HtL78FU4xuH2PF8mM3JqENOM7SsO0iCKPA5GLcWGMEs4P4cBvAQP25+/rLgZ4jib/Ezb7t/qcro2Qq9vN2/UEsDBAoAAAAIAC1nSlJHEiZd
*/