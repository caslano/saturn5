
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
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
*/