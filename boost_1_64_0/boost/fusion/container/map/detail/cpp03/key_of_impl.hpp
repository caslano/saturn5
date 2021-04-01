/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/value_of_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                value_of_impl<map_iterator_tag>::
                    template apply<It>::type::first_type
            type;
        };
    };
}}}

#endif

/* key_of_impl.hpp
cfJp8z/5CRrQgRbhjtop7hArJY3y78DGjXm0kTKH7x22U7+GY1KZHc2JoT6s4qA2bv75L4Dn6qit7IGS9t5cUzQNVUaATSut2aBvhJEnAPvzM3pFU3yjwYxZUyF5zk7Br3buTkGL9C3zx5vb87LUTsPQBS20hDIG0cmWpm94pctDBrLdigRgZwB1zaJNQkuOa/tZRdeOSEWqrToOYmLubCIaXIqPmExH221q8NHdQYlEYkYBZ07kGL+AKJznNU0lFFpo3VRT+90c1yQONp6vDmEsc+p+Owwy0dC9fOrm6gwWZQRMFmauLAqtJwcWkGPmNofsfpEvdZomGcuAApAYjXAci6cBzv7L5NrPW7nEUNVORw2VLOA0U8h953dsyVvwFKhuL/lRAmt9HcogePmbJUQW5iJZy65LVvMfAkB5dF01w5Kv22Fm3Drx6yisiXTL6Khq/t9RHVbKbNSjcvVYTRK0JN5RqW9dekbqH5fTrRU3nuVtgIewqfQ5gis0o80+LA78fI1K8J66c2/chTnkiF3MGL0k6vIMisnGYFNS7wMT0owaYgktY2kpKw==
*/