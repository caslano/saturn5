
#ifndef BOOST_MPL_AUX_CONFIG_ARRAYS_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_ARRAYS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
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

#if    !defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && ( BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        )

#   define BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES

#endif

#endif // BOOST_MPL_AUX_CONFIG_ARRAYS_HPP_INCLUDED

/* arrays.hpp
yGXx669dX+Sl757URjzab3MDJIOzxkTDJedKVjDwdKEaJP0aprihlRVs2pmHObyyc5G1ZZMF9ZTzuABwEDER5PYPXRDohVuqGu2bUf1WKTbPI9zHsQpPgZeaLkMfUI9hXbKSBcm94HedGKHNhQ645kXNLTPd3kZ2qGQHHvOTJMlFZ3VspdRSVD2f6CoAcZBtSGDdIyTrXv3GP0QYnx0omHZNcNVbFD3lTkKfaNMDzQ9fv2mUr7NqNzyiMBQqOR0gDmBPa9rfeTWu0Tt2NeYIS+aKlcgNA+bRcgdHxfB2Z6ybya36YONekvZHlZozKA1+6+BOpz3/6CQTANx1huVR44ODC1rHaDMyz4I3Cjv6thLqqTI6wrfIpnAszuv0QvPhX4FEszHj1tEqB/jkoHkWSN7bhbjeI/PrpJVJlfcrGQ/mPiqTR0hFZtgIGMVK6elcgaHGwD74r4klQIMT48QHemhoZguKSSHvbW3tzK1ncnxMZYAHM4sHjB4a4EdLsdbHI88nkxbZIdTMdKw16JRFu1/Ec9BBYrK/Yts6kuCjMHgcgUsrvqnObTEH4A==
*/