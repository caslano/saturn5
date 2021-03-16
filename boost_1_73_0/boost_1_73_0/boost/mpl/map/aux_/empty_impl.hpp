
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
Ndl6TZ5LU/zmzuYBoDCaUM86ER9Etwvx3d6JaXsoCae5FlKHheL6vnsSxDN3gPgD6xVxZ7o4h6XOIOu4Lu5FyekaF7jjdnd12t8Tm9cLey35A1bldXW5RHO+hq3qQJllsCo+kYfYJg47hlLALgdwb7GhsNhycEA6FJINesRS3rRxHV9ctXYOcnTV9B2yepVjFWtyUyk2rj/pIXWtIbLVZDSPT9cWOwH0db7rRnAlH6C9E9C+XzP4kg9Ds/dUAPo=
*/