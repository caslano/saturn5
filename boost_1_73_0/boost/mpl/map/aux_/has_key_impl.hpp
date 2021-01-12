
#ifndef BOOST_MPL_MAP_AUX_HAS_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_HAS_KEY_IMPL_HPP_INCLUDED

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

#include <boost/mpl/has_key_fwd.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/map/aux_/at_impl.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

namespace boost { namespace mpl {

template<>
struct has_key_impl< aux::map_tag >
{
    template< typename Map, typename Key > struct apply
#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
        : is_not_void_< 
              typename at_impl<aux::map_tag>
                ::apply<Map,Key>::type
            >
#else
        : bool_< ( x_order_impl<Map,Key>::value > 1 ) >
#endif
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_HAS_KEY_IMPL_HPP_INCLUDED

/* has_key_impl.hpp
yiB2ThwiL9plGXlNvMHYgHxMuybN+A3ED+o99kbqd7rQmRqlj/kYZa7G9m30/8g0NUHeZqz2AvzxY6THx8eu4xz/qDhCvIFnZFm+U0TdpKiv8SeSRzl8Q7TVw9TrCxm7fYcyorSPWmzyE/R6IrbHPmPE8Yp7yYO+pmInYwBT5gfmMG4hj378xZRv6vvjyApSnFe8GRu81qE/cIhfhfgo9j6KboM03XH6zUls+BXsndk/7F//
*/