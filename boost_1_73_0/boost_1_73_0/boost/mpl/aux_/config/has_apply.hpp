
#ifndef BOOST_MPL_AUX_CONFIG_HAS_APPLY_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_HAS_APPLY_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/has_xxx.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if !defined(BOOST_MPL_CFG_NO_HAS_APPLY) \
    && (   defined(BOOST_MPL_CFG_NO_HAS_XXX) \
        || BOOST_WORKAROUND(__EDG_VERSION__, < 300) \
        || BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        || BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3202)) \
        )

#   define BOOST_MPL_CFG_NO_HAS_APPLY

#endif

#endif // BOOST_MPL_AUX_CONFIG_HAS_APPLY_HPP_INCLUDED

/* has_apply.hpp
wHnc8X8gos3o6pMSZj7F0JS5EnEf9irOkowMe9SpikEUMZz0oIB2FxECqfZ7OurQ+bZ9cUPxl2v/wiRbrzaRPXC8CfCG6oeQ+6IUdX2Izwh4BLnanbyeAF6LA/waBsC/wPuFmZQveYMkyxEMnKvec6DejJmKMiTQoRmmz3wSoZ+xypIjGBlAJBoroLoE4w+pqGGLWECvTpXuseCx9aUARKpWUuUzRulfxdi94rmqqL5UrX34zs369lfAh+2R0sOAj2zPYndEE5/v6NgH2VS5ffF5sQmXq48Wm0uJJZnf2G8stjY6c4pUoDQd6cMHxJLP8+wRX6n3n4Ld9DE16FfRJT01shG3E6HVudf/UWt/38V9aKrsqtep1hZhqYqafJItxuNpMk2GSTx0RnKSuEJuXTEa4nY4GE8m2+lwKB0cTBzPk+54Ox2M5VaidN46AjH+ZpCc6vZX8E59v3gqydM3Q5vLl6FtsbZAz4UV2C/VZp//cvwNUEsDBAoAAAAIAC1nSlLZKzAvgwMAAAUJAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjA1OVVUBQABtkgkYO1WTW/jNhC9E/B/mLrIZRFGH5ZsWZUNuFljE2yzdiNns1eKGllCZFGQ6CTur+/QcuIE
*/