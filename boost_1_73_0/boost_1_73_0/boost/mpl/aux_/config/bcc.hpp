
#ifndef BOOST_MPL_AUX_CONFIG_BCC_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_BCC_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date: 2004-09-02 10:41:37 -0500 (Thu, 02 Sep 2004) $
// $Revision: 24874 $

#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_BCC590_WORKAROUNDS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, >= 0x590) \
    && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))

#   define BOOST_MPL_CFG_BCC590_WORKAROUNDS

#endif

#endif // BOOST_MPL_AUX_CONFIG_BCC_HPP_INCLUDED

/* bcc.hpp
Y3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjA1MFVUBQABtkgkYL1UXWvbMBR9F+Q/XFoCW5mjpOseakQgZKEp7WKTuGV7Kqp8U4valrGVD//7XVtOAt0YedqLLF0dnXt07pWFxcoqWeGYCZ2vDX3esd6ZMq7GbB5FYTvA3Sxyk2mwWMym3aIozb5m7Wg3eY4pmz4tH4MweulgL1HABD8RCu5ysEt2CSsst1h6lY6RiRKLtCaAMsSjrMvNR4MRXA+HMHVRbXIgufI11VWCMSO+I56JWFr54VzwwL5Liz5EG/wCw1tYmC1tjIYwuvFvbn2C3P2IGNFbzK33iPmbTXz4eoxEdUGnLe4tL1Kpc8aIUnCXyqVUCar3M/X+N3GdKME7X1vDp6lujjnDVbsgSNWWYcwSa4t28FxZBT/sgMhlRg3S3QqsgapApddaQWIqC1st4dQQ8KnaaauSBufaAjITI8iNNZm0Wsk0rT8TK3e0NFMmy2QeOxE+57vdboB7mRUpDmhvcD38NuTNAJ7XVdwjdt/vFn+A/X6jJwyWEXh76M+DVXQf+v1wGfz81UTbzulyijVKuymR+vNw81OEcJ1RrYXPWOp1DY3FINcWS7AJQvOGIJEVvCLmcFElxl4wsW2xRNGykn3uTcAZ
*/