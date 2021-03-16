
#ifndef BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/list/aux_/item.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef l_end type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED

/* clear.hpp
C6UsQAPH5mTCdkQh8w5/KOjRlob8nQEPOR1o71KaKxTRlnoiHb5QEMrZhmt1ZCokv1OG3TM8tCEW70zE4oGujX0DIwNkFiQdo0nRsOZy+P1Oh6tdC0d8oYgvukLzBWlJyBRiLz07SEj3SCI5NKDB3oE2EEv2DvWAtr20Sk1ZHY/FtO5VlDRDTcKrBZBSBCmHYafY7YVNwV56DoDw5GyHr9Xhhxo7DXxnqcThrniCimK86alygj8hZlLJtQkt0bc=
*/