
#ifndef BOOST_MPL_VECTOR_AUX_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_PUSH_FRONT_HPP_INCLUDED

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

#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct push_front_impl< aux::vector_tag >
{
    template< typename Vector, typename T > struct apply
    {
        typedef v_item<T,Vector,1> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_PUSH_FRONT_HPP_INCLUDED

/* push_front.hpp
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
*/