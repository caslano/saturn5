
#ifndef BOOST_MPL_AUX_CONFIG_FORWARDING_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_FORWARDING_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))

#   define BOOST_MPL_CFG_NO_NESTED_FORWARDING

#endif

#endif // BOOST_MPL_AUX_CONFIG_FORWARDING_HPP_INCLUDED

/* forwarding.hpp
bg8siqsFOSWFZpPZ1nEKoVutzkfmnKf7TEFYjUzj1rnJ7gAWI423we6bs+5PW4ZlDy3XTBdKhl2dXB/zbngTrpf1EjnZS6sLdvUfi2bBVZFkM+C//HxQXq/SnvuP5HMcqkC0OY729awedhCtc3A5fJHvY1Y5QgazZkzL5pwtqlWFG3LnV1JeoTOOi3LAY6916DpLhW1e296s+1DKzq+XR2jNhw0TFH4GaiogejDffWg8ZGacOd1JiAftz96xAfAaWo5I2okzzJEyfGwS6jPxJ0n0ljs03UiFIXAFwWwRX0C5a8piUV7E7IN4Sney8oIkqA6NC/Xp0ETui5bN2AGIrcz7Akyaw/JJWEJUSVSS4UUvq3gExOzxzJ/DLThXm7utIBqfNh/lTwam/FnGBU4aFZYjyzcpNRF/tRU43nNlEUVgCSbxe4cThp1aB/GqaSuQlZYd6yXaF8TP3hYeAm53WEBH5rPn3i6NXWJs83QgLLunctjjR/F7+OfEidgpq5hxsnkycQPbKbjUR0TCNqP3iHePtECRGhsB0ExosHheQXrvcx2oTu1B+4XIj7Akj+YC+4MlMPc9rlvMpLinLFhMCR5MJRMOCCDqtjvGpdhIB2m9cPgYltbN6hzngfKOTUAmyG+bK1+T0XRL8BwBITOSCS+ILyqgF6XJAtuN1OljjZcUtgPBU8FsJfujOw88jMyTcerdih9YT02dEUfI
*/