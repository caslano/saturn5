
#ifndef BOOST_MPL_AUX_CONFIG_GPU_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_GPU_HPP_INCLUDED

// Copyright Eric Niebler 2014
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/config.hpp>

#if !defined(BOOST_MPL_CFG_GPU_ENABLED) \

#   define BOOST_MPL_CFG_GPU_ENABLED BOOST_GPU_ENABLED

#endif

#if defined __CUDACC__

#    define BOOST_MPL_CFG_GPU 1

#else

#    define BOOST_MPL_CFG_GPU 0

#endif

#endif // BOOST_MPL_AUX_CONFIG_GPU_HPP_INCLUDED

/* gpu.hpp
Kxls8gC+GsKMDAo0zd2oaCrxqU6MZ9DXtGO8GS0xVHTd/ys9PQAszaOTo15Ss+g0v2zDa3faHLuu75X1adUspwsuENJ1VLIZ1xJcLbehtNEM09KIS8/eAtZX9Tc8na90kRAuF87fklngN/5wqpEVNGlu1b3g6pJ9NZ7J2/xAT4Nhg89DNWSPrcvCu/mIDtR8+oiSlayLzDOZDVbx0R/9MPGCMsma6llAdURphd+afXtaSR5+Wt87vdJ/3pFxQ6ff/9idNgpdwfsnqpioexl/KvyDNenjZ8IbvsANh1a46JEBD/o7CfVK+34P7dXPK/wB58nbYN52TeT3AKOXw768kQum27eDt2Cuu7hejdDk3YndMoma2wQLmqfbrtSp8GCisa6WhI+T3Ojdh6/+MwHWv+6RMz6E4Oo0nz9g/y68A1S5T2n/b+FN/18Lb/7/iV/SOHoeQV+ubXn0eqw5b6wxANauR697nb/b4zZ3LNdW1Wwte7IslXsgsHxd0q+afq3xOSgM2dz/JHGBgUBN/uiCHiFInRCBkSQGRc+Y9XF7mAMR1gpaLlk4yn70drvJvTWe8Q86miIS0Tfy7KH99oHNwh0qqgpQTSfmLL+Mic6Gu3EJbIsP4wTNpBOjjbTZjIe+zbhgStWeOk56duJuj3H3/HwWgt6+hNhC7ED24AWRznZNuia9Q65+sIL88y/DgyBeKECy+WThQVAvDCDx
*/