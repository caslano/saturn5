
#ifndef BOOST_MPL_MAP_AUX_KEY_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/key_type_fwd.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost {
namespace mpl {

template<>
struct key_type_impl< aux::map_tag >
{
    template< typename Map, typename T > struct apply
        : first<T>
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

/* key_type_impl.hpp
Stnvr4+UfRT/htQPLXiW4uIStbsnSW5vf5xfql4Vl+5bpvim8l5wo8pXf/rN0+rHT6m93SG7yQ+T4vvsxap/+cnc96le7lTckn5r5K8fOKx2Jfs2P0lxXHZcJT1ukD/8VfHmzpT8W/1ic6P2iZBeebLTP7z9rtQfRpX+dYvVP4j/1U2S35H/96gdS44/yY7d71e9dUp+1cP390tfpfvEiPxH/eQNF6ke9btOdrnV2wdL/fTS
*/