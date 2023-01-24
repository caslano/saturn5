
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
hfjMK6IKI8lVzMoBloYmKksiOs61n0dSFA/pNd4XhCZdPGf36NupE+9WemMozfETW2tq97tdKGlEUVrRpE9e+YrhHHcp1WzawEiE4Qh5RCrqTQCfbGzf5s/T5WV53gz5Zzwm0FsonguUoMS8tZ/2OBLrPQDhClmaJqXFRqcHrLb5Zny2EVuIVf1d29yJlaZ3L/QxAnSari6SrBetKQik6LO7O7dNUGkHN5Ey+Df0gp5Rd54orY5YngVT2FvTsVhY77m3w3Id/gA13LP3odxZ6dzdxX4+IY/afIIJxshZ17s++yCN9G4RL9P9MvwnbPPfsZBJuaFWSCvXOJptT769uVZRhAAgurps/Mncz8eyrHAa9/RA7JqZKAXJ/sUMX5z8H9KLyoj2dXTSMnuiO+GiH9KOyHTzBJy87FhC6K8eW6jtRPvlWHvv50g/nG6c0dt5ld+XlE8RWikraguCvUXeUQApwvrzb4isGYuYM8E2LlSHRol6gpzsBZ9+lp9C7zEVUgThWTa6krJGN36rRiDu6j9jm+8Xtk3FAOXMJeXKeGjKw2h/ECz2MuovmfmFbWgM4tv8s+JfXzzAjeA768Xb6wjiB7g1HGWK1rYs+ohlNmsdNKeoopz+8U71ANp0/TiAaM/QfSOoqMldDL1pJDI/ZLNmz7ebzJvc0z41MsJuNPkxIvZZtsBpOoFC7as556cb7CJ8lwCtRKK40JgW
*/