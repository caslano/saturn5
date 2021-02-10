/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<set_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::value_at<
                    typename It::seq_type::storage_type
                  , typename It::index
                >::type
            type;
        };
    };
}}}

#endif

/* value_of_impl.hpp
iYiflju0GB5XxFiqeXt1PzdMm5soxWKXDWisUhm6LLP1GkOaEOw5GSrhanFtab+r7MMvny4rLfSuNHgZUqIkx3fiLURVgZvHj0fcG+UWGmWqmLOasdc5n8ErwCT8dvNPthEOxmMy7GrgTQ2Yf29IyDhyzuHjtJ9qzhWugS8dAE7XadQEPniNAxp9Lr+p+I4WdgL9RNDYgj6jqfsAkahAE3552k8VRa8US0WDbtFyGYIDh4AXItzDagBHS123K8OYcpugmQtd/o2DaaYeeNxSOTmqwSWHaRhABISfxU0Kj8ASvnCwXlubqXxm6IZt6NqI0soPIDkRucvvbhUQYqmNrr8ZXIRhri+cIIs4WDUX3/nKSZ2XHaOkKDWaqoq+mKORwyzIx4qtUMwxjxgJtliIoRniyl+7Qa8djqfXI502akQcB41angBV09QNMpBQaQDSagzVTf2OToKK2lOKXhLUW1GJ662ow55h8YRxSq6ewXVDv0LL79OUHz1KcBIw1X3rMtFrw6Rw1rEQGBngdNlFM1VVGY9NnD2JVG+N3KQHql0j1qIwIZQJIJ4XXUTbXOgjxVbJvQTOjFB9cFoDav8AUJF5q25PBUx1oY0plg68TZiky52M4TrVvDEs++oelSUoesLlZDIv2ZXyr16z
*/