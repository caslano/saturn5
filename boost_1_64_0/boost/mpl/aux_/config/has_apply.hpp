
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
WHY5SUWIBdReOXG3MaO48Jo1LDrs6xWErh2/3Nt7gftMHTtEHDqDzIe50w3xkbw1PDfo5Rm1Zj1vpop7KBVuiRRfNzgfHv5IW8mA4zdgXZUS3EYuYk0XESsoR3bNNRLkLY9puUcYiOAKJDRLsg4IR9E8MGGKZekEdhgzykV7vPmUuOu+O1fwb7IdxXXn/n/LDrN4a5OOlCfNVptF7ccBGBYXGc+DrvS0IShvELarR6ZVsbGgSIgiBTeo/VaWyxdEhBlhOVCLKCNRG1JvtGLGHKY89nKdNrg3Kj5Mzl2bQzxPvQRBmM2pkrx2vD3TeY9aNR2+XpUqhQ6RLsaAocqGBNagxDZzU3m8A+fZuSa4vkeWLvjFmiMMDhAAVxmvUnHL0hDF7FtiKSJqNqJ9pPXDVsI6biqRX+IfUQ/yE3BgH4OIfhhMG2qdZPb+Ipv9leBeKiB7jgpU2FJwx28ZU0gR6G1Q0lhv0hF2UXZDfY3CEXKDCCttQeJiSYdKBuUn1k+XHmhYinIXUdmSm0EQgBWCTIAFa5FEKvIX1tHwmSmhnmFfApTUsilfUOP4xw==
*/