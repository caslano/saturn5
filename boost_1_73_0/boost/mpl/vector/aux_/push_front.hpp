
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
a5GIc3BvxEGrxJzrMcfVJjkhT7tvGXFYi6TpN3+riOdqMkrvpzHH1WbE+ee+iONmrShPn751xKlj1CTPxvWU2xgeR6DqDIYq+754f+D4cxRl6hg5djvh0FYu6+92cdtrv7h8ezOG1RdmGnwb79Zlv00Z7vniQ0fT/Srf+31vR5DjXAz69Q8+lRpI928/0zC41Qrv9vwTXsEKGcz739gK7LvbXTjvU2doDOlQVqBsXByJK7/o
*/