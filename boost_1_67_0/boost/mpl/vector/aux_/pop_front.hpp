
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
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
*/