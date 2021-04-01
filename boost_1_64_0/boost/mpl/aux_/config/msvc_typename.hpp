
#ifndef BOOST_MPL_AUX_CONFIG_MSVC_TYPENAME_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_MSVC_TYPENAME_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
#   define BOOST_MSVC_TYPENAME
#else
#   define BOOST_MSVC_TYPENAME typename
#endif

#endif // BOOST_MPL_AUX_CONFIG_MSVC_TYPENAME_HPP_INCLUDED

/* msvc_typename.hpp
sdK6VVJTSr8dzasgpg/RmiKxZnfurbHUu25QQNoCmpzY8cv3jnvhRXGhdS1E5FUqIZbuRcHl2nEejP8BOTXDzzZoeJH0JXWEAV+BBsq7BUQWm/FlJgVP/0EK95ffHvDBfJgI/ZwE/6zABmhF28P4jGEOjZH0JKZ20cqQrl/WwBiAF/F6oGpvjbSrTNB5PKscbnoTmZFhQqoLx6tdKao72bQ2V2j5S0DEzpDi6PerNNYOjTRkfGlkKXfRSY7aycsM1Ltn9EBKHBiHuMVeMSQevsKKKHMtN8lg6mSuSnwpGfUWZsX0FtPx6FQzI4NXvoDpSu9ic+LD99wtCkdUTn4aaHoZdnS28J4uq4c27pjSS+17/7kJtVlKtDp5Y2kQFeyk8xt08gDCraAAaJdbjfjlr6ejoor+POCCVqj1WkYj/W16kjiW6HDtW7kW6Jo5JtiygWAK2Te+huTx1LSy+i2hXP75Yn6J/kE0Q/GY4kOHcJgrDvW+1sVt3usEUIva+Ixs01p0xfz5VXruGZf1Ik19mwEuaxOWJBBxo2A2ZRfskXL0+JUWbWhXKEe6gQ==
*/