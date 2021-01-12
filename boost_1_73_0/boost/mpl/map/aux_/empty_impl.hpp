
#ifndef BOOST_MPL_MAP_AUX_EMPTY_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_EMPTY_IMPL_HPP_INCLUDED

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

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::map_tag >
{
    template< typename Map > struct apply
        : not_< typename Map::size >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_EMPTY_IMPL_HPP_INCLUDED

/* empty_impl.hpp
eccG6buJ0WOmPXajxyHKfBM69qLPE9HD1AO+OUK+bdTHJOlTFdiatCZuOh/neD919yVkRJ+iryL3xgLnjrdC20lciNFuya+U2DuaV+iUHSFP4s7I9/ORG3mfg85/pH3RBsfx86nL4HkEseZ25FxKPXZAvw0Q+5wC8t+KHb+BHo83+y6iP229DR+ZejSybUHOEnzmAGV9Cj1MH/Fd6up62hQ+UEr+ZXfBcye2Q7bUELrjW6kP
*/