/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_05052005_1128)
#define FUSION_VALUE_OF_IMPL_05052005_1128

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef typename value_at_impl<vector_tag>::template apply<vector, index>::type type;
            };
        };
    }
}}

#endif

/* value_of_impl.hpp
faiEs2y5QOXel7tk87oJugZoFFFWp24WnuiLZutkHsL5citZAkZ7dqWspFayd1jk6ZqpU4M3LImuZAyor13cvPKNdXbbXWZhu+GAWJCbkSbg21dBn/456V1A56eWq5CuzaLYIkc+CKLyaJrWNHbuPNvxMc20rTsbvWsf//xznb1SxvNsXmVpUAc/1vS0LSlsZ9ErEAyj+BWRaV3Dxg5kGyjks6s/rmymTHpTGDCrkSnn+KkwWr1spTdg+CGtYAuhh/KBihYH6gJ0m6TJ3FGT8IzFR0VxoZpPNVUoJTk+tLOaTlcl9rBQXeysc8rYSqkHSTp3Xo611XA2A025zxoqdQJvNTxVhn8w4l3GsD0gXnwByYsO+aGRu4rSsIW9lvAB/mGeRA4MS9hhyd+1O/vGMdfaW6/iDn6nTDcvK+mmcIaL7W27hBVo6mHpS1qhg6Qulpqviyh6XG5ShZ5PgkR9LW/5BXVdKyuyHguisPLiosIDTDVLWIVhi0kCZ8NtGuVsGAIEztDjoMILgI1aSJFpBHtU0jXGoNBD1F11KkvGliNup3tTshnKgaHt71rGhFBaDOTIb7txyj6dg3raNCvxLI4P6WIVGtgjdC8ErRMTqWBJ/kuyQeN5cw1LjRtIKws8XmDTYLh5CEowHPbo
*/