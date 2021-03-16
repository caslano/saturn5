
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
AK8E+D3AqwCeAgi09AHQ1wEAcTvqWoDDAQ4COAbgdQCnARyMdAFmAqwF+HNsv4W2zvTHAGYB3AAwG+CbAIcBfA/gCID/BDgS4GmAowDiAy03ARwC8Ga8H8AxAKcCHAvwLoB5ABcBvAWgjnYW4CqA+QCfAngbwGaAMPf0NoA+gPsBjgd4AOAEgN8BnATwDMDJAC+GQT8F7wuwEO8LcCreD+A0gDMAwoJJrwQ4AyC6OncDXAmwBOCLAEsBbgXox/4=
*/