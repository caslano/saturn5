/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_DEREF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_DEREF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::at<
                    typename mpl::if_<
                        is_const<typename It::seq_type>
                      , typename It::seq_type::storage_type const
                      , typename It::seq_type::storage_type
                    >::type
                  , typename It::index
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return fusion::at<typename It::index>(it.seq->get_data());
            }
        };
    };
}}}

#endif

/* deref_impl.hpp
MbrZLF/9zWcgBqO8GJuC10urhJBC8d3YaG5tjvYMXfM0crWZqdzSxhlt/ERBqlhYogQm2Z2eX/QzCBx9RPb+BZpP/xUiXx6gRLSYA24CxgfEb+qjo+QBSo2pkP79jUB3hL4/20UqSFa0aU9MVD7u+CBai0u5CdLeOyx/TrpmJJo1hvxm0aWbUqRSl3yhXLfeg3OqjfrLQIpeOQeHDDes3Y+pxVK7n4qN4ZurwMJUmOOpl3BLZQnAmWiKO13YU/4Mb858rO0pnqEafEjS3JcryrZcynAz3MQk1TpzI2AwgGyUrM9rHJF4GYzx/+pT7V+7NacyJEq+jIrPE3qZdGP5IaZLFjs/8jVl/p2kG/wPMunx4z1Sn1eKsG+C9RCjlQ9vpwxlgt+RkhDiS+knDy8XlIUgjhKmZvW36yGb04ZxUdg8BpJWR3bQk7eET+xDLZbkveNuQMBalF60J+eAIqUlchhzuCGuLbIc6zt57yFckcYQXWorgPdgvt2kFJs+J8nQiPJb+Mw97graI+jGJJB7yDBJVOH4uc2GL/uKTAKOiM38+wtcLQRHwOG/Gw==
*/