
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
W4BkW3MFduTLLYHMN9ztW6BN0Md2KWZ0d49CV7DkrB77exv91o5sFppi923rx64TKcpBQjMeYorSNUZMbxPdxHTPYpLjvee1y8mK2zvdpGq/V6NtEIY+EjWNBEtV/BrEvtQMPTPfaN+CzsnVaNVv9xBf2zq599qxCSDyPBD3UvMUzDENGnRVDLi5k4T2rQwuuLzQmsNQhVmusOqOXb6Ij0jBzqKnnMuUfJb4FMiwPQWlrqzWgy5CJT/D7poYmQU=
*/