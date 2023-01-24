
#ifndef BOOST_MPL_AUX_CONFIG_ARRAYS_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_ARRAYS_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && ( BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        )

#   define BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES

#endif

#endif // BOOST_MPL_AUX_CONFIG_ARRAYS_HPP_INCLUDED

/* arrays.hpp
tFS7mBiX+HZggLT/kDosieq/Lypg2f+ScrWO8oe79iZZ0S4kRiuvd/9QaUAP5Yr45757Ltvg/FcKM1SILLmzih26/iRqlabLjzhuPNXnTqXh4s2sweiBYcKyO+lICNdI8+eY1WJoK9uJGNS9VF/yftVH8YLu1PQzTNDxTTILLdLym41lpzzJ3jOkRX7UUEQPhvuWwFmYDaLoWN8LQS8AIz2fmDbcVz9aHWSv2bqabqlJlDLoCmIyeTEGeq0dNI0zFKuvsq/ndEVwuwImmyAfciUpsv6oDiOo7mFsx0otp2eehAC+Fndi7S/ZNmw83DRgFs1P9WO6gmw98Pzi2w4sPRW4Hxs+4z02ztJbv0vdABvkJ/Ef7MNyYW8Wd/jzLtl2p859LtBj2Hp+Ke+MeIc3bufYGy0nzcTuz+Q00NuBF/JYep1/5RRHCwPBF94+fGm816vcy/Kq7oXZCbUlU2xA6Si70kjeKVeCj3ixCA7IZKzBce/FDMWQ1EbSa8OZFnnCW62T67ncswR8ebDvCHqQkVT2NrcbUoBmBgj4NYyGmlQs8UGQrJEQWK4oOUouIULrZEOx/kdu9pES3t0RfQ1DdcZmNO/86N1QNFXV1KlwLjBuRHXPXeudX1hO9+suY4SApAjHvU0DJIWMtRrS2vu6e4WvDl9oEWI65XCfsS6wUS6upNVGB5GUo6m/YJmim6JkgvcQq83dm+ST9+qL
*/