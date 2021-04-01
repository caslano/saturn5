/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PUSH_FRONT_10022005_1720)
#define FUSION_PUSH_FRONT_10022005_1720

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/push_front.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct push_front_impl;

    template <>
    struct push_front_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename T>
        struct apply
        {
            typedef typename
                fusion::result_of::push_front<Sequence, T>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* push_front.hpp
6z5lrjjUo+KzRwbLxUJ1GWr/McJ9K4B/VEB4rvO8SqieUijGQNq0cVWs1IfKoyubX07ODv9XmgrPNoqBEy418DYYaB4EjrIAhbj9xXS9zWScRGmMpeOavM2t1kYRQeqPACP7UlVF6Viak+S6//lHbhv3ckGE2zGXDdpW1i9R/8bf3mpUg1waa99Ae6rVxjJaaKcO36IVau6OhDywrLVKOOgyatV+ckS/qCUexnjTd/nIVJfapKvjvxd/RDAbOoQ+PfDv3qmB7C7+REXqx8Ans1IJIy35GxXyKS++iE0M6kyUdnsL059oyWBI8zd0AGJ5kJtD8LzohAS5+umm2bSwXcjgzSar/bggWc+TgOhJf7lc4UVXtICnI39shE+oTpFz8mZYNTAHGwRbXJ6pEcXEaSVo73uhd+c3L41IfTA2ajpICbcYjLyuJoxLzi4M7dNDHPW8LN62Ffc64qhm/HVChf0WuynPO5TwtXZ7B4VX/KdLRmbSOajuC48A0h0x7fIwRojJZ57tsSnUk3Sia+nDepttFnadCpcohggGXF6Aqkcfmpt3pvBrgYktWg==
*/