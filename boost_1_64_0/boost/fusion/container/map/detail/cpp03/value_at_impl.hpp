/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Brandon Kohn

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_HPP)
#define BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::at<typename Sequence::storage_type::types, N>::type type;
            };
        };
    }
}}

#endif //BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_HPP

/* value_at_impl.hpp
f5b3+MzCw8ZH93Xc4QmLSEA1XHEUImKJUz5KWsZli8sASImP+L/oV+l2RydEkdNyQPUOVi4cf97VKUuzSCkFDJg370Hlz6tjHin7WOZKDfwTVqp5QipHlQXCkvg1UYiYeXDDjfaEZu6t4t7iQp6kfEmLk5mJyKdSRpbjnc2A8JM5HMlbLOaGrjvus7kf5kBv+ZsQNOWpmcpC1IXIomh83g/w48UwncbsQPt3+ihWHUZhq5GMu4hju/r4i/JauVHTeU5+eI0H8cnQqzw+QhfNJdx3VsVhatD2qnP7qs7kZBiXaZrhzCXxDwmNdg/4bBz+6trNpjx3qZqtwLKNwwppA/19W4u0AeGjlTAB2DNkXXmCxLdeVvQPlrMkTTm5hJfkLEBkI4pYKxLCjL2/MNU+wt+zJTCr4pMiKPMLW7cnaoV+DeOwooLiiXLkP62zGiPYB8Be08ZrBq1Cn0JlsFsub8m/HRBHtmL16Jyn2XmM10QTJr0SkbJg9lXLANvhLfFcVCZEma3pa9l1dj3wGf/ZSwnEYODvbEBgMlRgDOECdwU9K4BzBHr9Le4aUQ==
*/