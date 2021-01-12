
#ifndef BOOST_MPL_MAP_AUX_INSERT_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_INSERT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/insert_fwd.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/map/aux_/contains_impl.hpp>
#include <boost/mpl/map/aux_/item.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

namespace boost { namespace mpl {

namespace aux {
template< typename Map, typename Pair > 
struct map_insert_impl
    : if_< 
          contains_impl<aux::map_tag>::apply<Map,Pair>
        , Map
#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
        , m_item<
              typename Pair::first
            , typename Pair::second
            , Map
            >
#else
        , m_item<
              Map::order::value
            , typename Pair::first
            , typename Pair::second
            , Map
            >
#endif
        >
{
};
}

template<>
struct insert_impl< aux::map_tag >
{
    template< 
          typename Map
        , typename PosOrKey
        , typename KeyOrNA
        > 
    struct apply
        : aux::map_insert_impl<
              Map
            , typename if_na<KeyOrNA,PosOrKey>::type
            >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_INSERT_IMPL_HPP_INCLUDED

/* insert_impl.hpp
5un3Sb0vOUvvRT5G7/tqn55btd/MHa16j7FJ77dq/472S7Q/m/a3KPiG3ps+I3qR7H2d5HmE7L5acsle3ZLnr1V6D3qzypOdd+i9yTrtj/PUi/X+tPaj+/5cvT+7V+/zyh5/kj98X8cCvQe8SnZ9rur9cXulp/e+sviv1vum37lP+eu94vsX6n3oBu1zNia/fJZ+R1RvhSpf74luqpYeR6X/vXpPtFP2Un1e/T7Z5aD2F/iE
*/