
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
iqMaZ49ftWZ3nud25KWykJWXOfXkgpC/Q7Pq5uz9NzdMi77TNUBazn5dmDuv4ytnfcpS3vnDJ47XWFqGSEvrwpb7Nbc9PscyxaN8KRQ/b6Z5DzPT4P1zy/oA8xa27b5Z529oh4Z1po8YNXJgyIu+YVpyivKbp2266uf4537a7MmOPxnaqjP3xH9e/JfseLvQt3FmQvy2X+Pbuk+H+K/ls+PvWHPe+D2Fs+NpYf7MhPhXIf5o
*/