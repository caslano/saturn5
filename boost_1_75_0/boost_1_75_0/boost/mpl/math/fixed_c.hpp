
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
VeoS/Hep60WnRLAnsuAMPqDgDIGq4AyO9FXtaoc+oF+7fr//wSs1Aoye8wE/FZzhilK4VmmcK7vb355XVcIOsmFx7YchDSzFFXMGXkzGB+VI8eejf5O6fsnxxHKBFdymZIixnLlSyfbLqcSf/zToRw4ejw38u9Sljk6ATTgbs0jzlWVgyD1JsgJOMFNa3yXCYZlMvpzxne7kY3QENZJ8NBlryEpeufSpLaal1tgLUH70peCU1Z7v7gp9SK9zawnESwLo4CWpotP28T56GhGGPRiDPQnnrrfXV/6KcVGS4XNuWLxiXGRts5qCpvyDOansemk+dc701oT5ZknnPRFAVxscQsF4hUJsacZr1A+S03MfNkXTfIP42eIEmbnJZ7iehBot73l5Gg5anqgqJvUtn30Lny3C70IClsmNQvUL1S2RS+PjjQdNEzqoZTfyaGnOdhYCrMSOucNW3eESy1JK/hhSdCYtgfHdF5e0/CkrOqk7Qu3co4PiYgde7Q8K6+7nlzfGyV1NUSglO3aK3idLZKcK3ZBJLeu/rokpmXFMvbjkdGY/H9wJ6zC9ZxrjN/z58qNxNv/G9hEJnOy30dfyIO+FU1o1i34ibfnLFcFaOERX7PQP3hrtjmAfA+y2XqrwKWuLQ3FA0m4jK5Va5MqkN7BawJsWmj9ltLxOrHb1PNR84QtzoHm0NOFbfpy7MnXePLdfWlyqSmIAfinh
*/