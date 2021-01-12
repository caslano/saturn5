
#ifndef BOOST_MPL_LIST_AUX_FRONT_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_FRONT_HPP_INCLUDED

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

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct front_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef typename List::item type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_FRONT_HPP_INCLUDED

/* front.hpp
t0JeUK3yOqgPqFnecYW65eG96RvEBNQwz1Qd86Kr1DJvgBbVMz/Um35Bz39R09zzH+qad6q2+Yf/ob55tmqcF6vO+XLVOG+EZtU671C98+5Q+go83PTVPg+qe25X7fOqgNrnDUH1z49dof65OagGug08UN2X/vWlb0G10Lv60q+AeugRqokeF1QXvRjcJvoEdQG10TtUG70bDKqLHhNQF90eRj8C6qPXqD56g2qktwTUSe8J
*/