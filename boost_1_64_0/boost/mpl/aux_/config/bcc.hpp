
#ifndef BOOST_MPL_AUX_CONFIG_BCC_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_BCC_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date: 2004-09-02 10:41:37 -0500 (Thu, 02 Sep 2004) $
// $Revision: 24874 $

#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_BCC590_WORKAROUNDS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, >= 0x590) \
    && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))

#   define BOOST_MPL_CFG_BCC590_WORKAROUNDS

#endif

#endif // BOOST_MPL_AUX_CONFIG_BCC_HPP_INCLUDED

/* bcc.hpp
aMqEDSo0p9pvEt3pvyHhQsPx5qwg99evdt+iy9epY9znB7If8YbA4UQiatA7xWi9w/vQ2d/tDLWLC+gcXVpjgH/lZxRl62XCzmQECNpb8uT8aXXD3woyAegspmQCqsZhxBUUjaZAdhOLO7OW9CyqayUlAXQpMsY8STgJVsHKwvE3RjceUp0u2mldEVlQs8Jb0sf1nbiz5+8PNGhGOVN2VmjSx0OVUb8xGotmgenXws1YytCO0Y88h60w1CYUVUp6nmt6Kc9Og4JqEUA7UUw+CJJWqdliw4gi3wJNumf1Mwpqn/TCwDLVhFNe3LaWWMNV/c2j5p8iinSRed+9w9KZ+Wg8EKSEwA/ce2oWAIJ5GsAEAGiS+rEb/6PsXT46T8CcDGY9bf4qg2XB3XZpDflYerBd1oRKrZt1uPhOJmW1KqyqnVGsWjeCsXeuvLU0UxkWlU++saY1rCOJOO2WzbzetpaHlHj6HWIhTjLfdiCsLgad2sEyP8IeMElmh2t9KvrMevCF9mOb6bzNkZM1vmN4NncJV7mHGRIVnng+WeDqqzJWIqoussrCyf3/hw==
*/