
#ifndef BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/set/aux_/set0.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::set_tag >
{
    template< typename Set > struct apply
    {
        typedef set0<> type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED

/* clear_impl.hpp
/mSAXSR46ubl8Sd8MT3pHWFdgrxhXnKquz4c8o4k2GbgeNHeAljsVWpAn6BdMB9tIgmV94aiEU3fEw2NhTW2FtheJTaY/PU9WjwRjEagnbvxqoethOJfkaljsFwojkFIDKcOZWcgRV7BXC0XRBgbny2V8zM6PipwJlOeyqeBydXSYS3B5Esfv4yY1luLcHkKJYug5Pll4IgB1gqnW4AIk5JEcMQbAlOsBeyiiPp1WrEQoIUNWwXF51vlFlLFEuk=
*/