
#ifndef BOOST_MPL_AUX_CONFIG_HAS_XXX_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_HAS_XXX_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
// Copyright David Abrahams 2002-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/overload_resolution.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// agurt, 11/jan/03: signals a stub-only 'has_xxx' implementation

#if !defined(BOOST_MPL_CFG_NO_HAS_XXX) \
    && (   defined(BOOST_MPL_CFG_BROKEN_OVERLOAD_RESOLUTION) \
        || BOOST_WORKAROUND(__GNUC__, <= 2) \
        || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840)) \
        )

#   define BOOST_MPL_CFG_NO_HAS_XXX
#   define BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE

#endif

#endif // BOOST_MPL_AUX_CONFIG_HAS_XXX_HPP_INCLUDED

/* has_xxx.hpp
8U3hLjngg8cFiLmvEpYsHpvWMg0/MYTIAM/6F73wWqiugBIQajSrnMs6qkXC9HPvRxi6sSXfwnWhpzWRVqcopJxW8WmGK0PZkJq5Jj2f66YpR071UWNokfw3aT5Bjvi21h2jbcsZHUlmcVhiZElvXUxfh/Zng/RH6zm1q65f+zn+qLGRaP7COQ6/U97IZtEABdpsFs2NxqxTmkh3Da8LzwRb8xp+JtbNiZtY10cu1OnorVm85G3CMSD2/Wkin02jEUgfa9ERIJay0Dr/ujgxerok/UtT3g7aHlU4d96GeSwm3QQitarcJ8kCCy4Pn7nDVQpLyo2e+C4iyhXBMGs4saGsy5zSVk9KJ6WS7fibYO9HIDElyWLXbeBI4qSG8cQtS0GgYdq78wNIIkK9A+IJZkEFEuj600hbwYh+GjU3J8TW9IO2/MjYQ0u4mpxpMow8D1QVqIz1kk4u9m9DjAGA5RsBy1H6y8T6hv7Mk56oseJ5r/NHkt/LNUYk9MJQMThX/ab2ZjJs2UWqkrC/IZAeuVz05RoypGUHFYyE/lwT3Xh3XOXNs1mtKncTqg==
*/