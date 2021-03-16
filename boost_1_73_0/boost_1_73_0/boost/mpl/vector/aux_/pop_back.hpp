
#ifndef BOOST_MPL_VECTOR_AUX_POP_BACK_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_POP_BACK_HPP_INCLUDED

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

#include <boost/mpl/pop_back_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct pop_back_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_mask<Vector,0> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_POP_BACK_HPP_INCLUDED

/* pop_back.hpp
nY7HNmHz0L3O/vD4PiNsFtxX3N+dwqb9Pmd/uH8PC5ur9hX3t1rYbNlX3N/9wmbW/cX9rRA2zfc7+8N4O4VN8oHi/qqEzaoHnP3h/m0QNsH9xf1dJ2yW7y/u70vC5pQLf3O6xDzvcvaH8X5B2Pymq7i/mQ+Kef6gsz/cvxph84sHnf3h/IgeELfpB9TzQvPjhHhcKmz+oO2c5tv8hwA++5CzvyHxWCpsLjhY3F+DsGk86OxvUDzWC5vLDhX3t04=
*/