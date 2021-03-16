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
TOO5RI2sQB5JfWv4XRnS5k82P1xWgTySuiSo/kd8rLc5XIE8krqMlDerjOvX8S2iblUgj6SuIBXj+n7b3WMvUeUqkkdS3xl+rqYHyx8iamBF8kjqe6Squ75vn0tZStSzFckjqR+Q8lbMMsdVWU7URxXJI6mrhrfhm7uaNCUqoBJ5JPWj4VfU0L8G/smujUrkkdQ1w6+Nr0LWrCZqWCXySOonw3uAM2/PZp/yokrkkdTPht9fJX1bahJ1tBJ5JPU=
*/