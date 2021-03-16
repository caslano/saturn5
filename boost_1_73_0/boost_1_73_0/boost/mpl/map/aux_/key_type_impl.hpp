
#ifndef BOOST_MPL_MAP_AUX_KEY_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/key_type_fwd.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost {
namespace mpl {

template<>
struct key_type_impl< aux::map_tag >
{
    template< typename Map, typename T > struct apply
        : first<T>
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

/* key_type_impl.hpp
solOF2ofJSS/A6csEu4+qoV0LtXOlKGl5iwtD7UsfrvQe5YPmLNPCm3NcK1J2TCDTChm6b3NNSZEr9PrZOhhS99ll6Xv8mcje9vS6bYa2edG9p2l89IHo2euDA0O6HiXBPT9SoxsYkBfO8vI4kbGL8Cq+/HB+xn+PSe4o+i1sfiC6p+Aa8A/umws9doa9TYZ5x01NLSiIu3fqM7SBCkRSWOqi2O6tEgbRf2Kv7tj3jhmSfWMeXxpvDQihosf3V4=
*/