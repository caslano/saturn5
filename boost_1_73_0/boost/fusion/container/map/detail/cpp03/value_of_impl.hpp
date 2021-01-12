/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::value_at<
                    typename mpl::if_<
                        is_const<typename It::seq_type>
                      , typename It::seq_type::storage_type const
                      , typename It::seq_type::storage_type
                    >::type
                  , typename It::index
                >::type
            type;
        };
    };
}}}

#endif

/* value_of_impl.hpp
Tgrf0PLVAMM3uRy3UB8d3goT4W0wGd4Jj4Wb4CC4GQ6FT8BRcAucDu+DS+H9cDncBtfDh+ETcDv8JXwcvqLh98EuZgwQmWq6/JijNV2/1HQ9B1vC5zVcf8douLc89JK3snkfg63hYNgWroDt4COwvda7MjNWQtuk8YTkFYlD9+W0XftylsLWsAx2gzPgybAcjoQVcCKshDNgFVwIZ8JVcBaM5HuHXvdmj3w/re81z+j7wBv6
*/