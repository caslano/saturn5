
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
vY9MtrF1kym1QRVmuVRv6dX1fXdWlOcnEOInqkOmplrej3hiX/1LkG7ZaLIyEUnvY3mfapIkwkniQUtyX5J0O21Fm9cwsOU72GQla5sVyZTrYK+B7nMhqa0rkyuzEimJys8V1KfVNVr7fDM/NX72kDxqyumhaUB8tJPa+QJvEP1LCKWZptnNWbxEjhWmRMxOP1HumDzVQvhQabP9CI4n0JFIJLOEfmwc/eL9G2c1VjBXSIOpAFaFWU+uM2lpU+KSPADCeCxS4qY+2HnCtJqhBur6UG5F//61SvS0c113Oudq7aV5GteOO81zyAsLP78PeEbb0AAW1kbhb2iYeAeiEkOuygM9Df+8vPm+Y23g9pTs2Z82xhnSKxgSXXA/pqszYGiGfYKLocT+OUkzqrFEg7yQI49kTziUr+eJju1Jz39bRI8z4ptyagwHE3wfhj9sBHDwVXQEP0FI8QmXebNAmA82OQQRjqs0Rrngi0Ky0Ay9qP8h52bUYn5GgIYyDcE3ic1ACIZKG5xEUgYq6gyptL8ngvM1QYn19ldzItM2cl32wIUFBuNoVB2xGg==
*/