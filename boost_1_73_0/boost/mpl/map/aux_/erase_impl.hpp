
#ifndef BOOST_MPL_MAP_AUX_ERASE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_ERASE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/erase_fwd.hpp>
#include <boost/mpl/map/aux_/erase_key_impl.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct erase_impl< aux::map_tag >
{
    template< 
          typename Map
        , typename Pos
        , typename unused_
        > 
    struct apply
        : erase_key_impl<aux::map_tag>
            ::apply<Map,typename Pos::type::first>
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_ERASE_IMPL_HPP_INCLUDED

/* erase_impl.hpp
oL+J8/j2xJvRp4z8FuNn+7HDIL79LNKSbsro+0Jkgr8Um4zXYcNZ6PIDdKf+p7Bz2zbq83nYEnmJwzznpUx8YdrErXbahvHtCfA5ZLsVX8Buk7eQ/78uor9Gp4XY+UnoXoP9P0Odf4JyH8/5D+nH0N30eRXIMnmQvMm3DdmmGWOknof8xrcMvRy/pL5LE8Rf2mTRk9H3Nsq+jzRf43cv/QryT9B/TQ5gt9XIgB3K0H+M8enl
*/