
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
FRxHQS04bq6Ds2BnPtc5pri+j/MWwP0+80PuHnhHQDUTZ6dfjT/kkwYcB4c6kB9ZD5dgf+o4Tb3sA23vMOVTD1w/C5xebEB9xr299dDhADgODpm6HCE9OAROgxrKLU9je/K5azHXwQlwDuyjvtLbqUtwBJwCxfhhhcGt1A8YAWXPRa4e/AefnC4nv6+TF79jHCfI4wD8J/k9yTHNtX3gSD7y8vv0PuzK72JkL+1FNq6VUE7Z
*/