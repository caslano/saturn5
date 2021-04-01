
#ifndef BOOST_MPL_MAP_AUX_BEGIN_END_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_BEGIN_END_IMPL_HPP_INCLUDED

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

#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/map/aux_/iterator.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::map_tag >
{
    template< typename Map > struct apply
    {
        typedef typename next< typename Map::order >::type max_order_;
        typedef m_iter<
              Map
            , next_order<Map,1,max_order_::value>::value
            , max_order_::value
            > type;
    };
};

template<>
struct end_impl< aux::map_tag >
{
    template< typename Map > struct apply
    {
        typedef typename next< typename Map::order >::type max_order_;
        typedef m_iter< Map,max_order_::value,max_order_::value > type;
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_BEGIN_END_IMPL_HPP_INCLUDED

/* begin_end_impl.hpp
pOkmcYW4P07u8S4c/v3AkqwsYJAKSDQofNxzwRPhYxaVzIXnI/bzJU2cNbWTRxBDs4JPd3+BZxLsm2RUcn6e4xVviNcmF5+OyqGaFGdvUxe8v7IQcAj34lLzQPR2tABqiVGuvgGaSi8H3h1122bg50XOllmuLCQGhjw2GGIrt7/1nwFN/NGrHdiJ0pk/v2PfG5fDL+aedKdV+f/J0DBvtMNM1Ew0t6jMBSE7WbK5TQwRwiSE4ypwIpJFyd9RCLjV+v8gjT0UhvdRTArE92g7Oko1UzbJ3DYXP9izZ6uJsgb4Z1mejVZMBeBL4xgeBQULfFOqADTqEBorCWtTOF51r/Tot4ilgZrYdZfSjmE8XI9/7QjO1P0V50YxXpcnqbd31W7CGHNmv1UeCa9t/RkyVwKvyzjEip82grVMRbmFL2y2LfHBU644FdrCvQyapynrbMkqLGxIQWcksuoTQhVzsUqCDoXugs4SLZZhw86UK3SAbPO0EkoX9XpzVAPG2p1ooDi9/Neo4AympTZKp4H1YIfLxRi4ZlWfXMsz8Brj69ftv/XS7zZ63vTvMQ==
*/