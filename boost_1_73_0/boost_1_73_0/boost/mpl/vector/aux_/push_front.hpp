
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
VQm7pTn+ysdzhX9LPJrPSq5wy4LMBJOF435eMmc6V/ifMVf4pyCWGqmncbT21jV75slU0nJ8XZLnxSIvzx9/+dNZLy/N8X1pvlct73ZIYo4/dL9ypbgj293RuXN7k7jEN6kxKH/hf0X2K7ja2rRhvXzTrOyXWjZuxFcwH/IbF4p9qJMpEd6vp0I/ujiOTg/wmugXw31B0/rdmzerfMuYBOHqlTJ0zBmx+FZxSDHzxrUrx2sFdba37OjYvqVT/vo=
*/