/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/value_of_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                value_of_impl<map_iterator_tag>::
                    template apply<It>::type::second_type
            type;
        };
    };
}}}

#endif

/* value_of_data_impl.hpp
r5Lf77lC1KW65JFUFR/vN9Ytqsn6jZB65JFUVaS855R3l+xg12HzeuSRVDUfvw4br53MnnyH1iOPpKqL9zX94scLiHq+HnkkFSfOtbVHrptEfVSPPJKqgZT3DNs9+f07RAXHk0dSNcW5pjV4L5RdG/HkkVQtpPK6vlmzlyUTNTWePJKqjVSs6xt0NYk9BayLJ4+k6ojPK/LiXz2I+jyePJKqi5S3KnJovV8GUXfjySOpekh569jzT867SFTN+uQ=
*/