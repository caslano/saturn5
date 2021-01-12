
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
IvbFkyzBp1iPT7Mpn2EnPs8z+QJTuIwX8RU+yde5lKv5FtdwN99i1F5Yy5p8h034Lo/menbhezyTG/gXfsgUfsyp3MT7+CkXcDMX83O+yi/4JbdyK7/hL/yWxbQftnF/bmdVfs/a3MXm3MPW/IVdWaiM9bAIP+d+/IbF+T0PoLq0UEW+xEp8jZW5iofw8OLafWzFauzIWjyBtdmddZnKerya9TmXDTiPDcNxrw4J7/GR5nDc
*/