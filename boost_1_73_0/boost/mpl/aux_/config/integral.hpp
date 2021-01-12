
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
3sg5fISPcB4f5ROcyxc5j6/xKb7Jp/kRn+WnfI5fchG/5mJuzzoswzuNOEqoIuwv5DwP+Y35SvFbVuKPrMOfeA5/4WD+Gr5vY6Hw7qHwLqIqPCT0S/gzToXvYXvWYgfW51FsyqPZlsewMzvxFB7HHuzMM9iNF/AUprM7R7MHb2JP3spefIG9uZZ9+T5P58c8k9vYj9F+Ootl+RdW5nmsxgGswSRmjz8d3vPDN4XE8aenHCjf
*/