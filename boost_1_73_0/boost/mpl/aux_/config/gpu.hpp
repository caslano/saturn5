
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
B4jnPKtbyr9zfivVLkzb2j53Wtsw7d0809qEacvyTGsdpk3OM+3IMG1wnmktw7QT8kxrEaYdnmda85z0xaa1b18oTBvbLjatTc605LY509q1y5l2YO602DPHq9rEpsWeOa7VOmda29jzysNb5kxr0zo2X+40SQ7b1iJnWuvY88oH505rmTPtl+axabFlP8id1jxn2gGxaa1i8y1tljPtSNP20T9o35aulDXGhnKoeCWNyhiS
*/