
#ifndef BOOST_MPL_MAP_AUX_HAS_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_HAS_KEY_IMPL_HPP_INCLUDED

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

#include <boost/mpl/has_key_fwd.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/map/aux_/at_impl.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

namespace boost { namespace mpl {

template<>
struct has_key_impl< aux::map_tag >
{
    template< typename Map, typename Key > struct apply
#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
        : is_not_void_< 
              typename at_impl<aux::map_tag>
                ::apply<Map,Key>::type
            >
#else
        : bool_< ( x_order_impl<Map,Key>::value > 1 ) >
#endif
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_HAS_KEY_IMPL_HPP_INCLUDED

/* has_key_impl.hpp
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
*/