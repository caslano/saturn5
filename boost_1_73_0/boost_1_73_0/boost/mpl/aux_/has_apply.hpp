
#ifndef BOOST_MPL_AUX_HAS_APPLY_HPP_INCLUDED
#define BOOST_MPL_AUX_HAS_APPLY_HPP_INCLUDED

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

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/aux_/config/has_apply.hpp>

namespace boost { namespace mpl { namespace aux {
#if !defined(BOOST_MPL_CFG_NO_HAS_APPLY)
BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_apply, apply, false)
#else
template< typename T, typename fallback_ = false_ >
struct has_apply
    : fallback_
{
};
#endif
}}}

#endif // BOOST_MPL_AUX_HAS_APPLY_HPP_INCLUDED

/* has_apply.hpp
tBZdr9tagg4Wvoah1g0MSpWS1d1U/mFJI9o/mkK5guP/3aOT/dYwWup+v/+TUZ4+Pny9/noFx6UwjZPSIOQ3epvCfqpPfjL454/XN5/mnSShu9KsFlV3+PUfmMK7dyAyOD6mwy/fgf19yMNO4O1b2L0g4ZRm4pVtzbUk04m7G1/E7ebeNYod/v/+BVBLAwQKAAAACAAtZ0pSM4cUUKYDAAAWBwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwMTRVVAUAAbZIJGCdVVFv2zYQftevuKlLmwCxaSmOE7uyiyJu02xJEyTesqcNNEVZRCRSIKk6fulv350k28k2YEABQxKPH+++++6OTrx0XnAnZ0GidGbw9SQ3a2NTNwtupOeF0k/Bl8XirnnA5adFkLA9JGHtqeBN8AYepP0mbc+pVAaJlVWxQUDKPQdtRC7F0zTcSBfOGlcs6kcQDwZw+2sw515O4FGmx2iBX2qNryiGaDgZjicIubxZBK3zCRDhnmsWLONPMrgw2kvte9dSr3w+gdMRmbQUXhk9AVEYtwctNpUkH8+e5b4sdva5cpVxqj2SqUJqXsopPZDJ8D2InFsn/TSrtd68B1MRcuq85Xolg89k7eWSpxPADPEXUE4cfM49uNzU
*/