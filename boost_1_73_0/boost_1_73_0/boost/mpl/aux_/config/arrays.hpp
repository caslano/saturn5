
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
qFLnL5jc1FpCFKXzzrh8yGiQoanrcw47bEJ+CjhrWoc90kQEty9UgADzWub86mk8X9wn0w67NQYLOr7m1x3W+Te67eK3oduWfhu67dX/oCU/9p02Bzf48Z/zDlBLAwQKAAAACAAtZ0pSCaVX/S4BAADkAQAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwNVVUBQABtkgkYGWRT2sCMRDF7/kUw5YebYrSS4kLxa4gCC1brceSbmbd0JiRZPz37Zu4ioWewpt5L7/MRDFGbnTEUijrW0rHD54OFEwsxXQ2r8T0ZTZf1pVQ8tZQsveKO/AEHxj2GAbRGsyVibPouZeqOYuUiGdTKVrrUlleJSivNwle7LaOtCngYLmDbHqWMnVl31YNbTbaG6AtW/LjwtPA+sbtDBb9ncnuqNGuo8jy/n31muRaevJ4tJGtX8uAced4+Pj0wEeGwQKyocdeiuldF04i5ksh08fFP2NiGs1aWN/PwyQOwXIeLOu8oOvgaSGfGGx7gpwA3TIG4A4hLx46HeEb0UMRO+JCqP3ZW6bUcATjEibLel59rerZovqq6vqtFgpDoNCQSZjhKJH+aCWveSVvH/sLUEsDBAoAAAAIAC1nSlKCdoJ3HwIAAJYEAAAfAAkA
*/