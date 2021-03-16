
#ifndef BOOST_MPL_AUX_CONFIG_ARRAYS_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_ARRAYS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && ( BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        )

#   define BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES

#endif

#endif // BOOST_MPL_AUX_CONFIG_ARRAYS_HPP_INCLUDED

/* arrays.hpp
+eXmfYPuGs5YgPC3Tijtd2D60cHdghn7lgw7AXQ2E/6Vm31HT904/MM1B/e3lmqlf2Tskq6IX/riEx9/1ep217dOqQs0vXAIZgDhL2nr0Vh+9f6bvtuW/WrvufkVjNURft3etJEPpIz/17hr0l7/r2v272FsHeHnXTnI+Ye+q3//w8Itje9Hjkxm7BDhJ25ZP+EvZ36X/48N/742deOA3zA2+iLEb3l43qrBy5rL9/f910vHBl6VDXwg/L5dg8Y=
*/