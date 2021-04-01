
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
s/z6VuI8mVQWpwtBnaRvLbFhIPnds9UJ3qSdPcn1rQIEqzSskjZZx+iHIwBh0FwizjNC2hZimeIHFkRERiFLWShQ6e3+VocWBw6lX/y++9bGTikxsMqXcBOTIZEJ2OjoM46X6vY3OhfUioHCWt9QHCH2hsEMCiIrBa4B216InwMaNeWITM7vlTWu4yzHWk/Tr5bRxfa2TWslghi6b9zJMbmxzmoxT3qJOgjm5p1+MZLibOaZ3z4inpOWKaEwMp098cc0ETZtCuwZpEFVGS8WDlWnsHfKm+hNeFN7hEd0NTjdeE6vvXcIkssX/c1w/M+7GdDgjF5v/sZJKiQZMSR+VArbfApTHKqSOk2DAP+pmhIPPtfsEX43gO116tmr5wWajq6JZIIY1+1Jm8hHICffgOaGuMJigvOz6tRggNhz+AOgcEssrxuXQBa4rDHw3sUnemfmU/80+ZlDjFw1d+RKaiMfrR89iqRcbjaAK7mM2JmfGgcK7KrefNatm5LeQhMPuNBnxpKUJqC99y4shrVc/Lbl3JNlTWTD9j4sjIcwrQtAc3YLx0xqLTBPgQ==
*/