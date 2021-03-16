
#ifndef BOOST_MPL_VECTOR_AUX_POP_FRONT_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_POP_FRONT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct pop_front_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_mask<Vector,1> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_POP_FRONT_HPP_INCLUDED

/* pop_front.hpp
2Gw+5OxvSDzahE3Nw8X97RM2Bx929vemeBwWNl96pLi/p4XNtx5x9vcD8egXNhu7i/vrEzb93c7+cP++K2weeLS4v+8Lm1ceLe7vTWHT+1hxf28Lm3cec/Y3KB7vCZsXv1rc38+Fza+/6uwP9++ksBl8vLi/j4SN74ni/uLC5mdPFPd34WExlw47+xsUjwphM3K4uL8rvibOB19z9of7d72w8fQU9/c5YbO8x9kf6r8GYVP29eL+1gqbL3/d2R8=
*/