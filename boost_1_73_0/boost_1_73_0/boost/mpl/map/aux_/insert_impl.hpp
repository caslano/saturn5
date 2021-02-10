
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
hOXVRtrjG08/UmXaI+Hcj0lQoFDA8WhIEMUrEiwTHs0X0/flNOGE0Zuc0SaBdEgHElQHVH2dZ0iYwl1xqgWXwimCIsfKXBSpa6xEO59H8lLsrOG3BVaJEhskqDmgRK3FF4KRUIq8WMsj3P1ju7cm2riApbIsRZU1uRNKu69RwsN40q0D42jBob+Hvd020ZgqNND/hJ7bMxyN4Wn42LMw1xBbXnjdTT5Q5ZsTZMIIEBuDCszWgtmXha3QsEasoK230rQJOzitjdgpaWQqC4/4g8EQAj/2n8NZyFetejCCWfQSvjkkaJDcfAx/odzooZZGS96yWLdQRq+b6O2Pz1BLAwQKAAAACAAtZ0pSV9M1jFoBAAAlAgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDgxOFVUBQABtkgkYFVSW2vCMBR+D/gfDoqgA6m3JwmFrqtacG1n0+HAl6w9YlkvkkY3//2S1Cl76vnCd75LUiqxkSlv0CY0rw61+nzh9bsWWWMT/9WJiFsgF8DwR5IgDBVOYha+br23xIsZodaDTq1WgfRID2IUFxSjJs+QUIGn4qoIGZfcJk8wnYK3i5Jg5XU0minkxyzWYAZbz/UCpufJHJYec9cwWG6cVQyDfYxYwf4FC5SY
*/