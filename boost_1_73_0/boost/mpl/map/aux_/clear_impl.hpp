
#ifndef BOOST_MPL_MAP_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_CLEAR_IMPL_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/map/aux_/map0.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::map_tag >
{
    template< typename Map > struct apply
    {
        typedef map0<> type;
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_CLEAR_IMPL_HPP_INCLUDED

/* clear_impl.hpp
kW8Vk4QfpNwfUp8D2Os9lN+CDZ5OfDMxAH8svRU5qYPr3wKNdmj2Yxx7GX02+o/3XeSM9VKnF6E/dTn6bPrPTyPPU7D5ItrEvchdBu1i4hP1PEL6yW8iE/GtIk29DhAz6Y9ifcg6F77txM5WfLiL/mkSGx6Cby+6fQ19lxIvP0Xe1G/Fk6ivc4VOkZEBW6aoz7IJjvhR0U5iFrZswyYVH0J3E1tGKT+JTbCVY3z+ZehPfZay
*/