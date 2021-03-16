
#ifndef BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED

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
#include <boost/mpl/not.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::list_tag >
{
    template< typename List > struct apply
        : not_<typename List::size>
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED

/* empty.hpp
pmvtGrBJMg3c3wZg4sLTeV6oug6vo92DtQiHLqWQ+DUkRjwON3ehzElwBTpaoQVDy7h7ArgnYmB8UPRwf2wTaiP9K8AuC0XaOQ4L9AW6oAL1KCWc6/JEolq43bOCEuedRcjyhprFAApFPKQCXDfClpzo16jXF2wJ0XOkq0cGu2llTpxIU8Ptro6FRsokrJEJMIh1BGuhH0F/wN7ipuUoLuchPMujniD2CtgE7aXH5sC+nCtKQ2Lra6kan4yD1Ak=
*/