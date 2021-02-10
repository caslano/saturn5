/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_05042005_1058)
#define FUSION_NEXT_IMPL_05042005_1058

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector_iterator.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;
    template <typename Vector, int N>
    struct vector_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef vector_iterator<vector, index::value+1> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.vec);
                }
            };
        };
    }
}}

#endif

/* next_impl.hpp
sbzxWgPo/tYfXIJYF5y2P3ZO2n8cq77JSmp2rHMRvOt0T4PW6ellu98Pur3gonc50Ha1mA08dkv2/ynPGAJ5V/TJzg9nx02EPEpBhgkRPlKjf87/pg43gAkaTBFohi8B3yFIii84KBADDo5bcQv8Cd0DIAhZ5qiYELKbdtD7jRjTXM4BwjXAVTLYKEVwHbWjJUUdFTwlbA1Eih/rvzz/y1/qQh9LtJvz+ymcGH97/pdXfwD8t7aU+gobMkaE0eS8d0jKDG1oQ/AHzRAmIBmbVZAsGmUBWbQm4Qi7ILH82PsaB/W/UdzWRbRoEixSOYnucGbRZHNrZUvszmmLH7G1UcXzNB7NFzXTYQMxoiEUaMxj0K1fe/YvhOHPr8vtjrXy7S90cHnV1io1/kt2UWd8Z5r+DJwvHpiD29KZhYKnOwGNhXaCjjCmXqmz1Raps98j6hz0mIatfNYBVZcEpmyJsQPAdBLybvf6dMjG4hy9tHzewrl9E40V45vIEDBammNxl0QvaIVnwkyiw6cDYm5MqhaQQlPs7b2TsWlu3xs43bFynRE7Q4aHAQqze8XxsGOiOEPhIrTdYIxENFrOAGMMUJqCe78FJR6xGsAkb0DrU+RJTJXWa7vhEUwP1OQaWi15ZfIOvojdFs3ykmxv
*/