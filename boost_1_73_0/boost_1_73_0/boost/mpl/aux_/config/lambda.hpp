
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
AzjR1F6BoWUdHBvsTYIfKC5UVMgS7pKAokIEcmO/w/Bk0gGBwsVndsDhUOJBmOMCMlvHY47xmA99QqQXRhRknRCGqcJ17GfoJElsx5AU+kwtTOQbobHLALnWJKWGnlDpoko2dCoww+E4LOsrgTRszicmYSOMJVyrt4WvlYFKO76nMoSG1G1mQ8yI3WVG+MTJFOqcD5ilJ+yx4rQ5FeGgTHFsXMXIGaLfQtD+KGcYiRRBWcV4BGWN4ZyBw6WXMzo=
*/