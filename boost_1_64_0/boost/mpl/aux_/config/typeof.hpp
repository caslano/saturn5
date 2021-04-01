
#ifndef BOOST_MPL_AUX_CONFIG_TYPEOF_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_TYPEOF_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/gcc.hpp>

#if !defined(BOOST_MPL_CFG_HAS_TYPEOF) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   defined(BOOST_MPL_CFG_GCC) && BOOST_MPL_CFG_GCC >= 0x0302 \
        || defined(__MWERKS__) && __MWERKS__ >= 0x3000 \
        )

#   define BOOST_MPL_CFG_HAS_TYPEOF

#endif


#if !defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && defined(BOOST_MPL_CFG_HAS_TYPEOF)

#   define BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif

#endif // BOOST_MPL_AUX_CONFIG_TYPEOF_HPP_INCLUDED

/* typeof.hpp
MK8vc96xIPhJxDB5Vw6f2geS4jSdDpmnPL7ZEq3VUPPkmv3sJSWEX0epXGAhqbmvIDM25c1H3U9DJV2Vd6Quh+giHT5KtGSFZDRHXaGRtHwdtEGuKqrpjAgN0eq4HLkxMciM+D3SZQjlaciotZSOgr6l/BnX/vVnTj8z0JhvN7fWHN789L5ipwfl4CZM725ACJBQo2sBzOlMHUA8ObqRxV4C1cpT8GlEilzNqORiu4CFpQFuwDd2dP5HON/sfW1H9AaiFpdlUm4lSSbdq7MWHeNWWWfmm827XgifdmeLYCjIXp9wJ+uZZ+0zDmsyOEf5+gTCWj5ya9pSobcLXb2aORBOGFoLQdRTyuwQirgs3tVsLwS44Wk+dJQqGHCkyiy140MADMavPkxzdJ4jGpJWZd8EXAbda6UbGcGPy6N21PKTpDtWR2hd4eLNAFTiAZz07VGQkCK/9oRb7bAmSmHH8LrjNDn5bh6o1Um1X0vujQsEU/idRRc4Rnu7G4CKh2gbgMTmLgrPNQp4LPj4MDsHFbGYro6v67UpsLUIP8RqCVOtJJ0UyVm/me3iOA==
*/