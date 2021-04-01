
#ifndef BOOST_MPL_AUX_CONFIG_LAMBDA_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_LAMBDA_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/ttp.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

// agurt, 15/jan/02: full-fledged implementation requires both 
// template template parameters _and_ partial specialization

#if    !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT) \
    && (   defined(BOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS) \
        || defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
        )

#   define BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#endif

#endif // BOOST_MPL_AUX_CONFIG_LAMBDA_HPP_INCLUDED

/* lambda.hpp
g9y0ehKXln9OjvEtmoAmJooPuGIRAMF9sdogFFN6wMsiS/ni0V5MubCcTTrH5bYh+TQo3BRWcz13k4DKHQzpeZQZQt//W+siXZ+b+L/DjdGL3we+sGRxFWb9awM/d/FAdmg89/iF0ngdC6m99JCjt0o5wguRXxIa9sXuPN5G1Y8fbQoARwb8T4Xm/F3obCr/5fqBlYyHOxWAC5jLtOoP6wF1uHSnFf9iyY9apQ3Xrioo9HV4XEk3LyJmdJlLktHCScDbQxNkcBTnTPKD9MOYqqHa4001DYH2P9QYyoCFJbFcmGSysRd8UQWjRePdVR5HlXj40OjzhjHsbvJonJF8hkf9f1/VSWSqy49szcAxV6pcW4OTG4uYqHYET+hViqufrXFa6+b1d8ov0+EGyb9SriIbEafahdfZHfzs9gB9nsF73YKmkx2V28unwRg9DV2CdG9UbllKJVG/A8nx1ZUxlY8JW17R4MhO3roNPgCVnqbWyHp4PVmJf8epARND27n5Vlcd5KrOmPV3fSGMiW3T2jkEZx0niIEOe1+bKNGBbP5Txdm0//88/l8Jkw==
*/