
#ifndef BOOST_MPL_FIXED_C_HPP_INCLUDED
#define BOOST_MPL_FIXED_C_HPP_INCLUDED

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
      long IntegerPart
    , unsigned long FractionPart
    >
struct fixed_c
{
    BOOST_STATIC_CONSTANT(long, integer_part = IntegerPart);
    BOOST_STATIC_CONSTANT(unsigned long, fraction_part = FractionPart);
    typedef fixed_c<IntegerPart, FractionPart> type;
    
    fixed_c() {}
};

}}

#endif // BOOST_MPL_FIXED_C_HPP_INCLUDED

/* fixed_c.hpp
h9NGJedGpRkOp6ns7JyZJN7vlrbqeth9XXfOKK+7rzMynKbToqFUrFpt8Y6EebFffXsvWhDNt1Gt5QHvrhk23DSUHNiRMSHSw8kWzOK9K5yv6yu2Cl1MfEfMPADW8tPt+Q+2CqcyBT5R6UZz6BFORh37/HsfTjmU4D9LLwueLdArd29l0jTgttY0zCsUH10eTS3VbWbnk8YbfZ7Jiwut5xQ2R5AP73OKRzelXf2DdPNJ+1lS
*/