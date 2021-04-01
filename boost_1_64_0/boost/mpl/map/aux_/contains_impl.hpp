
#ifndef BOOST_MPL_MAP_AUX_CONTAINS_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_CONTAINS_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/contains_fwd.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/map/aux_/at_impl.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template<>
struct contains_impl< aux::map_tag >
{
    template< typename Map, typename Pair > struct apply
        : is_same< 
              typename at_impl<aux::map_tag>::apply<
                  Map
                , typename Pair::first
                >::type
            , typename Pair::second
            >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_CONTAINS_IMPL_HPP_INCLUDED

/* contains_impl.hpp
YNSKdPaPnjuJiMyH9zCIjlKaDMCI7euBUUSx6DI8Ohzw7vIvPC0hbZj0fZvN0RUBsVpMrkBaqay1/bZuaFvX4MruKIIpcTr6rTkVEI/Jb1/50I3wk5clN2Nysyvb77myNmVYjaswsST/PjR/WjCYHIuD0xTZ+LtdsRWBQcfl2LRuRVQi0l+aAsZJ6YAC6CNOWTTQ7rnAHCEVs/92yqKNU8xW72tR8QLfKlfhiUaLbqWO3s8zqfFf7gy2I9jnz6D0aBjnUdy+6bJm1/D2BqRzi58dzhtyrQbAm6UP2bwjZY6VQeYMQTGXBzlRkwhuF85FDfNmWk+wXDqtGEZbXUFWa9uZ2+iIWMyCiWYNXHn1iEah0VPYxL48ARnppJP9W09RFxPZz6sE6obCSQwEaOAE5subSC3905HJH/18Qu4jwzBCwWPfdYODFeTnch1/bUu6MDss8xbp/+TrUGq+2/kTQPbo/32g08fE2wc5iDuammcy3i2w4aC2e5SSfQMk3PTYT/51GvLb1eucMtl+ZRAQZdf1JdiUrepEpVy3BTaacMXOAnPfxuDMj7GZcg==
*/