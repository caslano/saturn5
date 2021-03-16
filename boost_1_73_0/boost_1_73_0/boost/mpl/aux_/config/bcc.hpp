
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
7418VPvG0g0nXz/81SzGniX84TETM2oHLl/2Rvqo5d32nf4rYwcJ32/H4mWnrp7++kN1t/3+wW3/8R5j38G4HYrPKpUlfGBIOQ49WFI6x0+zrzKzovPigarSytoyiS6iR4cqWOmNRcGa6tk1JXOduN0fcg6syxk+qAhff6heEHLOCYRDRUPcsvYQd6Y7c0h21sisTHdRqKKkxl9WBLampBJMxbm2gIepz7cNw9zDsQ21oH2gBWWB6nO9vb+m5lw=
*/