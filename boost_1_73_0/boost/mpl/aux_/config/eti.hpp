
#ifndef BOOST_MPL_AUX_CONFIG_ETI_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_ETI_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
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

// flags for MSVC 6.5's so-called "early template instantiation bug"
#if    !defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(BOOST_MSVC, < 1300)

#   define BOOST_MPL_CFG_MSVC_60_ETI_BUG

#endif

#if    !defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(BOOST_MSVC, == 1300)

#   define BOOST_MPL_CFG_MSVC_70_ETI_BUG

#endif

#if    !defined(BOOST_MPL_CFG_MSVC_ETI_BUG) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && ( defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG) \
        || defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG) \
        )

#   define BOOST_MPL_CFG_MSVC_ETI_BUG

#endif

#endif // BOOST_MPL_AUX_CONFIG_ETI_HPP_INCLUDED

/* eti.hpp
+Jog7zbMOjocg0Ucg8FoGzJr53MNlmcb5v/Be1W76yRc6yTENyTE19b548dEYn4kHid5+wvjnmVI+J2AkrHP52R22uep8my8ZaodnpvGDWHZ0DVkWu45dlDy0MFDQ77nfMfdvuNk863L8x19Q/kcmJpdNhPL25pjsjO5rQVqBaN9Va5uPtf1efZV8z/YjulUL35ftEqIN6n379s3v11fhd8dy6tVx2S/I79ftK25+atOyD3G
*/