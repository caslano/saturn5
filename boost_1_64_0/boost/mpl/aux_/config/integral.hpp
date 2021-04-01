
#ifndef BOOST_MPL_AUX_CONFIG_INTEGRAL_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_INTEGRAL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
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

#if    !defined(BOOST_MPL_CFG_BCC_INTEGRAL_CONSTANTS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))

#   define BOOST_MPL_CFG_BCC_INTEGRAL_CONSTANTS

#endif

#if    !defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && ( BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        || BOOST_WORKAROUND(__EDG_VERSION__, <= 238) \
        )

#   define BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC

#endif

#endif // BOOST_MPL_AUX_CONFIG_INTEGRAL_HPP_INCLUDED

/* integral.hpp
mzad7SlPjQqAiZEvOM4SJI3Mmfhgtt6DcHArD7QpsMcJpj8nTvFWr7T+cHgEZkdyWo0TdzQ60qbtKZtiZ5xtAvjX6hM7ExLnp3M9Fz1vbK8+cf3zRdnu+7BasER0wCBx30Sy0fzx9AVJzcTK7oyADpov066+GdcWWfCCYlZ+I1VXS1YiQ/6abzBO4Wj4p8ZcanblJnqgHBtcGWtNh6+i5Szoaof5/5yVi03ddsptXl0jIZrJZO06WN3hBh+pkA8ZSGgfnWkTt5jKk7NLInX8D4NieXLOPu8UDHlZ5J9/KnGrxMCWWih6KCedxXR6C49PR9kUfa/bcn9sI3xqgRQboLkaNnT5fctzjMS//as4H5Gsu9GtyvqaExol/BTlq4tW/cG5pgbSIT5k20IsU46e9svvjCWZ7v9/tsqTOHPUKZsxhBdgEt8bIaK/o7TduIsR5A4z5tGBE0Eyl/+YXa3SVDEuLEh4Ch5d5RpAtUjXA0Rt/IeKHfHGwuCGiDrfQcB1mF40ZEgHF73I+M0O939LM9fKUDwFy+klUK/xzH0hVdImbbsbBWW3saoeBg==
*/