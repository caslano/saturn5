
#ifndef BOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED

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

// MSVC 6.5 ICE-s on the code as simple as this (see "aux_/nttp_decl.hpp"
// for a workaround):
//
//    namespace std {
//    template< typename Char > struct string;
//    }
//
//    void foo(std::string<char>);
//
//    namespace boost { namespace mpl {
//    template< int > struct arg;
//    }}

#if    !defined(BOOST_MPL_CFG_NTTP_BUG) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(BOOST_MSVC, < 1300)

#   define BOOST_MPL_CFG_NTTP_BUG

#endif

#endif // BOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED

/* nttp.hpp
GiB24/8YX38dBIjU/8r4FG8H+EtGJ3zpdYzO7NKx7383pLySCSljKhWnloHbJXG+BFJGedhRHoDz8iu4cPIYhL0VX0zlQiMZQh3bTiEW0BZsRJxYxjE+AG+F/+MTi6WavsrbefAel7Y2SP6KuF3mD4VJR2MNLoDqEJXBeWpIDpWsCF9fzVTXGsXhVehjG1Ecaqx6NrAR2w1i0/sDhEWKjrtPwHIdd43mAMQ+VRrsRtvN2Y2pVNrz4rjtEnf2+RQ=
*/