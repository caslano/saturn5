
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
3S2ymQ68MFWJi8GXGMYIboX1xxJKCbtj4v5IVHtnmtra4o/FKqixqkP7h4fH5GiE+H+HA/ithPFAAfLmWF/X9vcPfAC6Oe3ocpH0LeLTzRDKfBHrymyfifSrxHbL5VpGEAQGmf9gtWe3mVXRzaMoUUv/TX2OC/y8fPcnKlL9QXP67N6dTCcxskF+iTRvB8/NFJZ+CwHGL8nsqXBK7aia8p28mU7nQko3Z5QiszRXxt+kgAysfIESOWOF3lQzlvtT2Cr0TahvUjwfJzKI39W53rkLhoxpoywi6xBtdj+mPR3iagFK+mKf9yPQZ/3PJdqg38WwIg4L2NG9ms6JLY/JdS0GW4FnUQp+VsRsxSMHnoSko9Xd3PdPQbcM9WQ1rM5fjPnlOX77mOqockTp2OL1Yrocvj6Hhm0jUroizwPrJh8vozcoVQ1OXpjNIb4ysn6xyJVKBLms1tt/klsky5BDFb6D7A4zDV4ku71uTQQOxpuLkx2IXoYtYXCO5WSqzE6U8LbI75rjD5AQ371v0z1sZdgCJLTcnOpHl7s8uDRTUNZ1wx3TrmRFWVJ0Eg==
*/