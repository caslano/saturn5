
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
QgHckm8+SeIQds9+N+H1BDPqqs5T0PF6XdCrDjy8Kr0MnioLE8mWJ1WrNr/Ofb7kruOe4OZKA1j5crefAC9dEWCbZd+agsW09X+uQTQtunDLbt0+ck9L0SATCxJpHMv0WsFmtz1ktZVS+kP5Pzl6P1SnoCzMbjGyt32EdVJICRoX2jwfNVthVRAVGO7mkikZDOfxjh5fTEnfvmC7aEwaVg0sL1mu0xeEbZXE4w6iHYdJ53lQH9mjjPelCA7Iut9naEvfRV0XKEaMBkriOJS/v4Lja1vs/5mO1t6yVbhtCtdxANkpMZ/9DhgK8avakC1czI4oGmkAFzbNQngZCoA79XMHt/Vwsh1awR5Go2N3R7Kz+5jgVsUfUSy88xDn01eb0Rp7NvOu4PY0AOeSLYJXrrUQSfD+7yjAR0DXOtJMVBYGU0/JRc5l5slR6Xqy1S5A/LstKcHA5j+zC9pzBAjkzBWTUFjRZ5v7RfgruR2msvpZlsu34R0owpsF8apippwZFNZlWLeAFlW5uPZL0bbkw9xg2wcIpfEOBAuJNgo2SIJ+hAeSua+l6/U0NA==
*/