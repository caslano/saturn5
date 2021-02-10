/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_DEQUE_DETAIL_IS_SEQUENCE_IMPL_HPP
#define BOOST_FUSION_CONTAINER_DEQUE_DETAIL_IS_SEQUENCE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<deque_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
CJvp4nFNUHk8bTVDJOuKpoTG0yjSU1ROVfra0z6uVSPUXWJzXEOCoWISJtOgUlXrcwOuOafGgszrcCVbrbkuG53+NYcIpJFkiguSQFYdAh0x2/r/fP1qnGR383mpV2YJYGQwjJxZg5XH7HIklWP2FC8TTzkR/KxyMezJip1GLBJb0bqMXY3HstVnIAZCzJUBTgLF5IDpVXhXNWgZ7/O7z/bs3vnN4sm9v1JNZPdNyQfEBjoxAZsL/iHdcu/NdbQGqN9lz2XDAc7ec3FsFIfCXrwO33n9BafQb45anQ7cCtcix2L55Vk60GAVClHgaTCvrixaXGtOz/lp3DLL+Wzs+mX8svf5GR/sxZv1k2hZMV0z018Zdv5M5K6u6mtroBO3gcmbhfuW5Kb81LjuKttr5vJ8s4gUIz2LZtrCm353gKrLIqFp0vr6oH5UdcFhiHJzL5032Ty+DuZPWauLTa2k/CIPzFARl/OGxwulRQghLdgVmKRuC6tZEjMB2F11+ouFlErE9SHpQnUjff6Yh3mhvRXNqVQiOgIEgtl+EtyEvz2hmLUng8B772Ye3CZPrNDkPrx/3ipp7r4A5In1A7jSJcysHxeot9dCOR9tUpbRql9nLzqcHDmjj47aUUa1+2BB7AfzoWlJhT1rC9gP
*/