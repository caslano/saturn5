
#ifndef BOOST_MPL_AUX_CONFIG_CTPS_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_CTPS_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/config.hpp>

#if    !defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, < 0x582)

#   define BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC

#endif

// BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION is defined in <boost/config.hpp>

#endif // BOOST_MPL_AUX_CONFIG_CTPS_HPP_INCLUDED

/* ctps.hpp
XfK/dbuiMtvOvsi0TSuj9/dF2xDrKwntmZSUC7VXsuYtbb7FQhszXX9g7rybw7Wm00O6JGZ/r/kWCp+Y/nSYt0Z0PIVjIeoKyBgyND1p2IhRwzP0soS26YbwedLAjFFJqaljo/lC+Yl7DjglfGdzeyWKn1ouO/5mwnXgkDDI2IfhGmx1znXgQbH9lZLmmdZkSTk/NeU/cg22PqQhoqjQUthPxbqmfFYafE3GyBGp/TXhLJ3+
*/