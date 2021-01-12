
#ifndef BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::map_tag >
{
    template< typename Map > struct apply
        : Map::size
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED

/* size_impl.hpp
1f4lx5UtOmrc86Mfyi6K9w+ondwg/hd4csmuV0vvXrX7T0jeD6s+fvoexUXpH8mTnX4leR8tv5JeT/Di8zvUTr4i+8meV6tf/Y7qY5PkukP9+5clT1LtrF3Xv/Av1V9cfpXWON/bh8hrRxHpka96l7/cWZ2nfk/1Jf+75HK1V2+f52LVq9K9OCL/1fEdnh/sU7uTnm/+kcYrPYr/6he+/EyV6+1Xpnh190/UzovVbk8o/TPV
*/