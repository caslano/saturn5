
#ifndef BOOST_MPL_LIST_AUX_SIZE_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_SIZE_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::list_tag >
{
    template< typename List > struct apply
        : List::size
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_SIZE_HPP_INCLUDED

/* size.hpp
g8+TsgtJ3puDaJ88CWv+98MsGnrnlFvpPmRxtlFoT1XVPHjtsmIyTZWeAi8LOZJihAtsQ1Wol5N+lY64/Zv0cbNDRLZmS0Vd7m/guSaMV4irTSGQpzklzDXI6w0AXveMaSwMv1AaUuUprSDToRVFBrqOzYGCKjcvf7M1fGqmzHsop4iUt3JZRz62jbUVLFzzU5iEy8qKfBQrsWV9RVssO9YR4+mbkd1DFfbk3hK2fyRa1ZARqO0XOj+QKQOYDA8=
*/