
#ifndef BOOST_MPL_AUX_CONFIG_BIND_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_BIND_HPP_INCLUDED

// Copyright David Abrahams 2002
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

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_NO_BIND_TEMPLATE) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        )

#   define BOOST_MPL_CFG_NO_BIND_TEMPLATE

#endif

//#define BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT

#endif // BOOST_MPL_AUX_CONFIG_BIND_HPP_INCLUDED

/* bind.hpp
q5CNOFslf3F16GxlBGHSllUllUW4zfBjK4nW1KEVmF++8FzrzQpcIKaji3EhKJVWwxoSjAg/Hq74R3NPdAj+n2sV5N251ikNX4jO8o8OnS+l2JkHZekNmJ9IrXZu0YLQ0HBpMBD8iZREu0JDA8Eyf/n5Uks0OBZc+PG2QOiN86IY2+VZJSF/OFR2vsQSNY9aB45bVXlg9rmOVXLgz7USmoTw2SoZE07YnJ/cW/TZLwQdKVSD4Dn1PFRS7qe38M8=
*/