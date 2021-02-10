
#ifndef BOOST_MPL_AUX_CONFIG_LAMBDA_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_LAMBDA_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/ttp.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

// agurt, 15/jan/02: full-fledged implementation requires both 
// template template parameters _and_ partial specialization

#if    !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT) \
    && (   defined(BOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS) \
        || defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
        )

#   define BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#endif

#endif // BOOST_MPL_AUX_CONFIG_LAMBDA_HPP_INCLUDED

/* lambda.hpp
JGLKEHy/DdAZXrxbrNb3y+iijr1cPK4PCn5JedC6ybIqKtBYIs/hJmkp0YndvqwJ2WGiz640VLKPaOS2aiYd+NaRT2IX1Hgh5RY2SEPh0WpwHoufGl1yQI6dFjqbsUMdXkoQDtQhEmnroheVe+wDJebPdwSQKFKaLLj4ePe4ul88HAbgnEPvEQt/nsknrLn8P6A5zdxxSo9DV7eg7vi11/SBJu6/x/ASSiOvvZeCNn5soZUlqzAc4WiSoNiMk812MppMNiMSpps3V2I4RuF9U8FoW8O/+ffdejUXAgs6fh28riP9fnu/6trzBzHwxKA4ONIqOP1F+AdQSwMECgAAAAgALWdKUohGamxRAwAAnggAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDYwVVQFAAG2SCRg7VZNb9tGEL0vwP8wZeFLoDU/JFI2SwlQHSEWUkeKKce5rsihSJjiEuTSsvrrO0vKloPEvbRFLr1Iu7OzM2/fmxkpVNioWDQ4ZWFeppK+HvCwl3XSTNn1er3qPmB1t+4XVS2fDv3yfb6luyBalbFbbNodsitZKiwVvxXllnZ30Xp5czv/fDeP1iy0ToFDq8/FfoUI60eseZMnyMIaq+JAx4lQok9vOecOOLYNOnRe
*/