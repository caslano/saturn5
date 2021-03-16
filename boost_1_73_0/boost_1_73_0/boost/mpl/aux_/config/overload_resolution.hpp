
#ifndef BOOST_MPL_AUX_CONFIG_OVERLOAD_RESOLUTION_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_OVERLOAD_RESOLUTION_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_BROKEN_OVERLOAD_RESOLUTION) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(__BORLANDC__, < 0x590) \
        || BOOST_WORKAROUND(__MWERKS__, < 0x3001) \
        )

#   define BOOST_MPL_CFG_BROKEN_OVERLOAD_RESOLUTION

#endif

#endif // BOOST_MPL_AUX_CONFIG_OVERLOAD_RESOLUTION_HPP_INCLUDED

/* overload_resolution.hpp
VKGiLonfMwM3gKwPir8giVDDNVX4kfofJ9Zyu1B90v6Yes8UoqrjsA3xOu5jxt0V4LM+hNFZqDouaj9h3H351NBtuDF0D+MbQxgB/BwgGnHcGMI+/dkQ9gomhI2pVLJfHPdriUsw1WKNvLmPhspjEVOZO4vhPnQsc1FJ92R81gzvKdG0E5ucm7iZ1tPgJh5zP1ErLsQaJvPcSmm8B+4Og4vDXAauj4XvnvW18JmQbuFMWMwEEzCVSrvyHLdY4rQ=
*/