
#ifndef BOOST_MPL_AUX_RANGE_C_EMPTY_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_EMPTY_HPP_INCLUDED

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

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
        : equal_to<
              typename Range::start
            , typename Range::finish
            >
    {
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_EMPTY_HPP_INCLUDED

/* empty.hpp
1EAtrJ+P/vnYeD59gJ756K9AfwXaIbkC/WCrQH8F2qGpAr0V6K3AnhDhQa8HvR70gtWDVg9awe1BpwfbetAKzdDqQa8HvR70etBbid5K9FaitRKt4KpEYyUaK9EIDZXohJ5K9C1AH5ghHpLBA9WwEtbCJmiCtgVoXYBdwfgYWh9DK8SBFfKgGNyPoRPqoRU64PBj6ANDFfogBiyQCi6ogdoq9EELtMOhKuwIPXAeTAvRCmZI
*/