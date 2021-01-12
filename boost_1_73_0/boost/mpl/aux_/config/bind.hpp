
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
iBcpEr/8beJx60v4/Kui8Z8fUCz+874hXqxSdjw94fOk/eLTMzEWj693V4R6991wT2NlOEfNL1Ekn3rX0z+F/vw9jfzuX+wIx01U+kcMGpT/8RWOkx2x4yT+HOc3h1l/M8M9y6lZ28CSCdvgC//svb+CPsuS0A8bl84qR2Sv5IGQzltDOpsfkJDO6GLvf5jOSaHDrEH2NQ5DmyExnalD5WfB7zcamDb+mYDS8fGtUfwPPl+U
*/