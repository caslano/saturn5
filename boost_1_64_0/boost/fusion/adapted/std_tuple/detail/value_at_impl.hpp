/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_09242011_1744)
#define BOOST_FUSION_VALUE_AT_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <tuple>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<std_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply : std::tuple_element<N::value, Sequence> {};
        };
    }
}}

#endif

/* value_at_impl.hpp
f6fpesDsAGG5KhNKx4GKpfJwkOJhHg5WLJWHWYpLHvjZ2Y5h8Q5WRZtjgqlf67O8PFJovBml2pgyv2KxdIvDmRPb8acfpOGQBJ+u87NzY4ZM8LOHBly/0w/zGRUSjj6kOjkvwTt5xzuD5HDfxp0/ekSg63eYjf/IyEbeYwcZ/iqf/8932atje/2uojJ5TWwjnzIqdOcfn2Mb2+F9YYxgc1Rso98bFF9/2kbeHQhrftoO7w+2GYht8DGCioTe/YPrt6kUIx/r/1Joi+8lJofEFwjHGN+dlkhteKHidZzftkg0r64NKX3STxPV06MD3mmtzux7/xhhYR2kdCwW7r6VLREtGs8NCwv9Q3yp5n58xEeE4/uo8wvvgYx4fMbmaGTjskzpLzPnWxRouZGMBcYiRq6m8l8WM0xj634H+x7TtvAH9j2mbfjXPdK6IrKR8cPKiElxuP2OsY0UC+I4nmzc8kjvTocTAiYDAu6jTnTcOZLnKn1dBgaIsxJwvY/ipIBNJsbo1chG7oIYj1h8F0QtsonvgqhHNum7ILLYTg8gyB8TSRvZrzeZ5m5/+6qY65cxhdEIbeSFzHObMZdxPmxWxzby4kZepkKbYLw/neCdhozFmymeV+nZVsiCb8kzPne/ZU9xetAQkK+2z/13JmzyyCb2cSe0CXzcjXjs4zWRTezjU0ObwMdrQx74eF3ExcenhUx8TPwNxGXEVZbRA/HTAy6jKuZnhNydQoo5zIjLXoAzI9Zwa+XOipjs3zk7ZJRm2fP5phTnNPO5uf9l70rAo6qu8CQsoiKyKYgIEQFBFsMqsockkEhIYhJoUDSEzARGksmQmWFRqlg3rIhoca8VqyIuKC6tuFVURFSs1BUttbjWtlpRUalrzz33f+8u7w5Ll6/t92U+Ljfv/8+727vruZuTx5f37vJ0yiRoKjXC/AXM43CGokklmraDw38h81zsA33wiwRXWVGVNwHdAXmhGLfBS31OjaMuVhiUnCzPZeSnisMZnpjn9HFWLrPsMoWxMthr9y8lfKp3MSmw5cCGD1XYZYx5i/cwdymxqRWFRbhXWpbRy4M4Znowh8k8ZyY+6xgkcz9THPe1QLG7K3UunqLUaGgQGc5L2ystXnf3KsWxulTfX3u14tCNMOelrpE8dfsIT9UkcUs1c9dKDt8Ss92Ym7iOOd78w7LXy+dwhJxpWOQLM/dzcKl4ME1uUFwgTX6hOGea3GjxeJnfXaU4K964+5N5pSP5JT9jZRyr7vwXmL9Z4xtSSfYNvJzf1PjGSIIv0+R7QQM43kMcViue5/T1tLlNcerDIjxrwAWWNSA8t4NXyxqkf3conNMM1Yec4/Q5uAW/7lI4R4EPRudFCZJfG+SjMeYxv+nziJ02h3sPc/CPRHgEx1Mdkl9n8xTgVELtLbo3wDdQMWaa+7v32TwyuMrxDb5f99uyXMJVWB6wea5uFP8rg08E4vJrkw/E5UGTD8RlfYBPH5eHTNlAXB4O8IgLyscjzKszDB71n/EO6s7HGOejQiPeuQa/kVgiXd58HLzKmzhfV+GG/BMKR9HC+boCp33H8t5NtV/mKROPevIbdVy7r/5pgVdM5K1HNYjXJg+Lp3zsGcJ+VFBYVlRaUuKt8d6sY1UToknMqPKdoDqnraN/Tse1dfTPGzgcwvfaQpxolKcNEdtKxLlIok7nI9C57X/BzcdYAG781pSBzlS58aKbhxs4e9eUIV66/bsAXkUrIqp93fpLFg9/mXs5yNH8TFLuazS4YJxeTcNXJebKeVyTRydOxuV1g1Ph2RbEeVUJz+kanNKfvmnilJOwtzGAs1NyHtfkooPD2Ndo4GZ833Jw0kXM55q87Po=
*/