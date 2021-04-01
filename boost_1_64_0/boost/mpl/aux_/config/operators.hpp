
#ifndef BOOST_MPL_AUX_CONFIG_OPERATORS_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_OPERATORS_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if !defined(BOOST_MPL_CFG_USE_OPERATORS_OVERLOADING) \
    && ( BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || BOOST_WORKAROUND(__EDG_VERSION__, <= 245) \
        || BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, <= 0x0295) \
        || BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(600)) \
        || BOOST_WORKAROUND(__NVCC__, BOOST_TESTED_AT(1)) \
        )

#   define BOOST_MPL_CFG_USE_OPERATORS_OVERLOADING

#endif

#endif // BOOST_MPL_AUX_CONFIG_OPERATORS_HPP_INCLUDED

/* operators.hpp
UV7V3zShZUafdeih0BUcpl15nt7FOiWuhkCdIPAi3/znICj8pEzLmXlxGE+hbsIk+fHejCyl4EjXH3tLLPir1qa1SDsGTcBZLcfpYQG2kJL+FxGwF0JD9155cX+/e4lQ4Gj17eynaBbVwnmhWF3iHaixDjI8AhNm0KQzJrEqqWH3ooqu+caKblqGb3F394qqg/UC4cNFfd4mbPo+0LKHdv7HEyIHdw/XfRlV4dN6cPWGVbc+kqobRZzfLr4Iws/spTnd8c1NOTliIddj8WFk9uZdjBtjyYRHrQyeVqRyjVsGlAB+eRHpN7sXU1tP/8E4G53KmF7hfr2z5n4QuXpn3dCCkmD3mavgb4fA4IuLSDXWO1qdsWCOAHrSDW3kRd5sntqksJEko2Rv0j0sAHj9HLqRCiEOf8PqcNgEAggNVE/5sSDYC+HYxnSUx8Hz9wIqGfnPrTGI+IGWBcUt8XunOJ+LhD/RXJbx5RKCuuwjKzz6EWKXZYPMXF0TiZPmxqh121ST0ayVFC4vNtfG3CLAi1yRsgbouqCOv6fWRzktWmmz9JT3axJtDz3rwA==
*/