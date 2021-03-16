
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
eokTSSr4pZ/+kE+/ToLuKXL8kCsK20JHNOILtkLngr4xgeaZJrZ6gpA3P0s1CjATYH8oobBQGHKJF1g4BrsSxWDtP0fbyTjhRbOfI9VY0BHwGBTMLt7a7YqsCEdDUAOa2xF1gMdeuttPSTQSu9YkMvMDSN4F9ez0tUJVwhGAvfTDcqnaoY9CIfTGGd5ESdhh34IS6NkHtMgGNs+1UhovGhkP/iao3eE+euGB9dNmiDzc351YqMUGu0F/MBkbpHU=
*/