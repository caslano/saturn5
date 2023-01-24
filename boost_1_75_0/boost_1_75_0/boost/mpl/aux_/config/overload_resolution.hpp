
#ifndef BOOST_MPL_AUX_CONFIG_OVERLOAD_RESOLUTION_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_OVERLOAD_RESOLUTION_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_BROKEN_OVERLOAD_RESOLUTION) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(__BORLANDC__, < 0x590) \
        || BOOST_WORKAROUND(__MWERKS__, < 0x3001) \
        )

#   define BOOST_MPL_CFG_BROKEN_OVERLOAD_RESOLUTION

#endif

#endif // BOOST_MPL_AUX_CONFIG_OVERLOAD_RESOLUTION_HPP_INCLUDED

/* overload_resolution.hpp
9q0bi/4Uf/Z5zJqQDccayjeRn3ERTuHtDUBOox2slTmclRQm7chMRaES9ayJg5RB6lQyudpNFkYBTXK5yl+3VfMLVb7HNMRxXLTDW//EM0ESgi7Z0r70rto6A1q4HnkxRQGLS/fLyyEl3joppxPyfUstkbBZb2+tQtKy0s/PfX3ugYGD2/6K1HcPaFk1h+ru+GVA7ooihoqGEBPfwo0MVRO65B++vnJ/lZgi4r4mVbYiRj/iWgxqubVz2xq+J1K9pOF5e0P8CRfU0XLAhoGBvRfzJfKtq0u3iwuP4Dy5g2vkFDXcbw1efnWeLKZ9r3CnQSvCBoKZbNQjlm+Y2deGwDnmCw43QYF5wax2pYO38UEvJQtZILMgneS4CkNMHJsgsUGDYIGfud/ack4OFWyF3JBQLtAg/k9yYM4RtG0MtE49HpWH966iCszmdPCGPZL9Dp93FODKHhglvcDjcEpEeEbWkMmGps+mzwJNU2oc2i27WZDo0YyUZQ+T+vvlG/bPT6bipnFS/RNy/Fo+Qq1cfK1mBgH3HYpDmK42oKvZhH/r6vfxNyDaOx8Rcbvy4nsSJAkzQutz0lmVNiMnDch9ZXN5SqxOgIw+6E8Az6+FKlifHbUsd1cbR0vtMC15yLec/9ZObZPXrvhh67ynqXVoZWFlcZWE2+AqTUGXChzypUiq/xzd9+uilOrPiVAf4+tvYHCeu1Q6y422Sxrl
*/