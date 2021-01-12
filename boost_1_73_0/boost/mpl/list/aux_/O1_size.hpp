
#ifndef BOOST_MPL_LIST_AUX_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_O1_SIZE_HPP_INCLUDED

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

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct O1_size_impl< aux::list_tag >
{
    template< typename List > struct apply
        : List::size
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_O1_SIZE_HPP_INCLUDED

/* O1_size.hpp
6dKum3S6LutSUrq1pki7dLopkia3zbX8uE1uuoTNTZrcNtH8uJKbLaUIio4i6Bg6gqGjCDqKjqAoiqAoiqCj6AiKon68n3s+55znntza/OE/eeXzOuee7/d5nu/3+3yf7/Oc5zznOdYe/YfAETAJToLT4CxwrP36w3v1D1v79e8HB8EEOAZOXGDP/mpr3/4ukAYjYI+3h39o//6p/2IP/06QAjvBbrA3tKf/EXASnAZngben
*/