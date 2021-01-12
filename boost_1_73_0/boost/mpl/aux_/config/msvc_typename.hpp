
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
WkgN2/ez+apyD2vzFzbir2zDwvsbf4n7MYPFeQlL8AaW5E0sxZksw/tYltu5pnB4f014r00VthUUway/0earxDGszrGsy0vYgpfyaF7G43hlSM8EpvAqDuY1TOe1HMXJHM9pnMzpvJW3cTZn8K+8g0/zbr7Ce7iaM7me9/J9zuJm3setvJ/RRj3AkpzNSnyQVfgw6/IRHs1H2ZmP8RTO5QA+zmQ+wTQ+xal8hvfyWc7mc3yc
*/