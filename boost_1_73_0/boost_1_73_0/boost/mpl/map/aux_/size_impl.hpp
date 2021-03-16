
#ifndef BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::map_tag >
{
    template< typename Map > struct apply
        : Map::size
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED

/* size_impl.hpp
QnynNzGk1oeV7GEj81kKbNpeLTI3DGaaFQ+p2fNHFA6Ld3OfQC8ItcXbbvBFPt5soo/znooU8AwXkdRx1shdsaGMkp9YEOoRy9HB7vG+Tl4sX17YN9sCQ5tf0E1OBXCeT0lSGfBxzSdok7/J+X0k9X4v2eIi/Z/T4pki2eKcfDH6ATn5wny0DwS9IIhL9TijZtJc/uJTbc4Y5Vfuuinz5d9cWQ6DknldAfYBG2l4gitDynXkDhCKT/wGfBC8M6Q=
*/