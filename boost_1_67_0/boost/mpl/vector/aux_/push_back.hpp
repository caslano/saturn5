
#ifndef BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED

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

#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct push_back_impl< aux::vector_tag >
{
    template< typename Vector, typename T > struct apply
    {
        typedef v_item<T,Vector,0> type;
    };
};

}}

#endif 

#endif // BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED

/* push_back.hpp
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
*/