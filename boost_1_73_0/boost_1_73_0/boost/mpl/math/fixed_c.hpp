
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
z6IxeVWvrbJ0/PkjdOukswjdiR06R6AuvINluV4nRdwiz8Du989h4TVS8SePWf6EwFnOMU0xgnUFPE0wV//kNlU1bZu0Z6tfXx9cm5+vfvBs1a/Zh+B9hj8ucZFtU1QY6Y6POqIRU2xMbqTIRpDhVSEy3MUosUNCMYINe8arXLSRDlmLqKrPXq9DACpRygKKRMuWmOoEtRo6arXDM1OdmFbaqTZ97cc6JknGtntNOr5BpkqJejVvgsB3SYTr8olwWW2V0LhDGmjOMmw8cbwUVqpYl0g4U4nIYZeoGIwRIrHLnyTTKoBazV2gei4Zy/UkTmshI8t6O/OC0PVHb2te31uG1uXwwvp4Z7tzdzF1Hj4NTqFXQqkFjwrkEpVWtWfRr22DpvUVymRTQT0VYBuFErQ2qB0OMStgjZhDt4iF6hL6YrCaYiuFElyk2m/9/gAmtm9f6+LhY4cY4/zHaB1yZgBD+NstOvHKJQb6HgJn7kxC0C2awAXcOOFkBgO49qaP376b4AeYe7fefVjv96CNWnvB1uGX/Q1QSwMECgAAAAgALWdKUkzB/cfaAQAAhAMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4MzZVVAUAAbZIJGCFk1FP2zAQx98t5TucihBP
*/