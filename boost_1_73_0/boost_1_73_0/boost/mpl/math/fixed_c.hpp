
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
Dt4PPgE+D6Lv26+DTzIdsAm8HApnJzgefAasBp8FG8HnwAfBXeBW8HmwGXwBfAP8E/g+iLFkfwfuAU+CDt4LDgL/i/kF9zGf4MvgBHA/WJEr/dXtxeB7YB34d7ABPA5SlwfoFw4GwZ0gZvz2B2AG/c1hiXUA+4IdwfNATPvsa8AssBzMBieDOeBMEJNxezXYCbwdzAfvAruCvwdhHdtPgT3Al8Ce4D6wD/gaeAr4P2AB+CF4OshHyNngIHAQGAU=
*/