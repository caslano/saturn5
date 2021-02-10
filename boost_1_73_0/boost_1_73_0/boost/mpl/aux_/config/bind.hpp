
#ifndef BOOST_MPL_AUX_CONFIG_BIND_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_BIND_HPP_INCLUDED

// Copyright David Abrahams 2002
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

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_NO_BIND_TEMPLATE) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        )

#   define BOOST_MPL_CFG_NO_BIND_TEMPLATE

#endif

//#define BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT

#endif // BOOST_MPL_AUX_CONFIG_BIND_HPP_INCLUDED

/* bind.hpp
mg990mNz8tc/40iPPVG5vMkbaSX8pkx5/3m2XN0Hix4LGwHeqSl9eEAsvEmqt9hjPbpkJ7GRao0y6ZjRiwdn+UcxfyvOP9NPlMKCwlf86pity0KLo0389Cv6DVBLAwQKAAAACAAtZ0pSPdr0YNMBAABXBAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwNTFVVAUAAbZIJGDVVE1r20AQvS/4PwwKvoSqK6XpIUI1BNfEoallbCWnglHWI2uJvCu0Yyem9L939BH7kFsChV72YzTz3tu3s4oJHanM4UjE2uSWpyc8PNt67UZimqbzdoCbSSrG94u7ZJ6uxslsNhmnqzQRsTwlx7KrF2fiDJZY77H2nV6jiGusygMnrDPKwFhVoHr65h3QeR2FDD+HcBEEkPwQ3zPCCNIdfoLgCmZ2zx/CAMLL6PIq4pSbnyzEGkJD/h2aDRURfDlG0kPF1YQvJKsy00YIhoxlQ9wI7IW0Cselbio6hardcIprdY9EQVRxwesWYpNt2SLmMagIyIKrUOlcKyisowgW6O8cAr5oR9psQHWZ2hoHOofKOqcfS2Qk2UHxStntNjPrji2ScjhNluntPBo2psyTRSovgq8h+M/gDX+b3XbVg7o/v4wHvm/4nDz1
*/