/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_END_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<map_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    map_iterator_tag
                  , typename Seq::category
                  , Seq
                  , Seq::size::value
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* end_impl.hpp
TYMKhWww8QiFfObDLQ8l4fHVkOYmC+uzs6OvHUyX9o3WHyjxikQzdrGILZ2cnCYu3zFW7iLn8hh3pTgsi3ibp/czEfo5p7PsZ2NueCd37moVenRk8NGhd4uOjgyqF6LdJaejwGBGnPihaZZpRdGZfJjMjGKhf1KUQeBLo3hpXS6gQPlqWlpkGY2WocML1IxcQ4zlTbbt0FElTolcwBdF0cAh9yRkT/eH7Om5SDEnWSVKKdYgPLWXnIRn2qLJpjXW+cqDKFUCPGiyGUZTBL5oz456xIULR73nrE1Rr0Jy1EtOXopYU2oJWeuzUw04eLVIUEa2CJS+EUG5OAIo9NawVUTjCPNmNeo8nbUeIjkIZIXbZJhuz7f2UIN0ZmNXtj7S2NXJq+mse+k60n2nIHAdxX7DqV9wOOnaWIu+KuNNq9Itjs3brqVMPqrDS8EArupaCCFbH85WwnV25QznUf5zKIinIIYT/+mHn4cp+J2Cn/uF+Q8IsQ17+FmDi56jHOOd32tS6W7Xscm+X3ISddM9tFBRsiC9BvZcv8td+4II1TY30bH8HDAT27lrX4TI4z6KnIFILzYjb6UdGX7y1FAsphtuGplQDKAT8Dc74H1pWEePdMqOoiq8Bvpjhbb0RPJNR9ud4ul4dH9W5zp3Sd0evBgJMNUTw2hqfJprSIc4NMmLOrabjklvcZrrUpEQ7BclEcxZPssiN/zALF+I
*/