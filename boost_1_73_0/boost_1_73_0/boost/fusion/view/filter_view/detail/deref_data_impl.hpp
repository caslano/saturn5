/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<filter_view_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::deref_data<typename It::first_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return fusion::deref_data(it.first);
            }
        };
    };
}}}

#endif

/* deref_data_impl.hpp
qdFZviK0PUMnO3JX4Nhv1RKkMPQaHKnYDszgw14kU+6T14DZd1E5DbwRRotLLUVfhY4m8oPj4/5v3dPzN7/xt0rwFHwCr6C/swqsRw85Ej+5vET12r2obf1zHY0uJX7EzTpHTnIhZhswcxNFYDEZcGz+CzteplZRn0eciYC5TctgMs85UEZr8H3PVe9nOKfE5YRAWjq9trPG4DK1MmDiI6rxYbNBfFR0ghfhSLZu6JRyF5zGwPJMb/pcshcoYoILM83VoK4Q4BX0BcZ7NAyzEWUCrcywNbyaJ5+Q6VKJMqWajFaQqZKewIoMhgJWQtABsRuFR0WXMoyaxNZwnhcAhoVxaVrQOYBwrnr/Zp04JecflKoJqtU7licr8TMMtDmKcOOw5F94ve54XLlcIvzhV42iB5OyIRRgHmihNPCbkJbFwkO3/b/bh/3BYb977GVqcSqBozPaJJ7O4LhT8kMlB4OGdVMohVUqeoDriJLIK9jA5JG6pADVIiRAIYe4ZdcJJzANs09V1xhL6Zpys1UAvq88yOFapdnNvfWm6XCcZnZn2NRCPZbzBl5Ry3nP/VKRdEk8SF+pW6xvn8l35niRYJUEfMeEg3hzyqK5yWuD5h3X7otwJm68rAwRkoRGEspIKMCAjrIv2FFWIXZa
*/