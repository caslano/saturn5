
#ifndef BOOST_MPL_AUX_CONFIG_DTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_DTP_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/workaround.hpp>

// MWCW 7.x-8.0 "losts" default template parameters of nested class 
// templates when their owner classes are passed as arguments to other 
// templates; Borland 5.5.1 "forgets" them from the very beginning (if 
// the owner class is a class template), and Borland 5.6 isn't even
// able to compile a definition of nested class template with DTP

#if    !defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, >= 0x560) \
    && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))

#   define BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES

#endif


#if    !defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(__MWERKS__, <= 0x3001) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES) \
        )
        
#   define BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES

#endif

#endif // BOOST_MPL_AUX_CONFIG_DTP_HPP_INCLUDED

/* dtp.hpp
eB4q3BuJO+dltJMm+yLr3czVc9MyJ3bOk5rk0Hcdpg1TSQ/Jc2yaJi1jY89xiivjo2J1yeYwbWxKUpiWe0zqVhmVkRKe3ewgv4UTo/KQk5Zw3JSolN1/G36zEJu/gbQfbMav8sy/yu8bTi2X2w9TybRCvqN51KfiHJoy0ic5fcPmzbm37ftj/a3LTb9PfmYMi9UPceV3Ryi/a0Of6ivCAdK4sVY+7bas8vvn+1UTykB+z+cX
*/