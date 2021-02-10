/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_VALUE_AT_IMPL_08122006_0756)
#define BOOST_FUSION_DEQUE_VALUE_AT_IMPL_08122006_0756

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/assert.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template<>
        struct value_at_impl<deque_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename Sequence::next_up next_up;
                typedef typename Sequence::next_down next_down;
                BOOST_MPL_ASSERT_RELATION(next_down::value, !=, next_up::value);

                static int const offset = next_down::value + 1;
                typedef mpl::int_<(N::value + offset)> adjusted_index;
                typedef typename
                    detail::keyed_element_value_at<Sequence, adjusted_index>::type
                type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
1jXU3tuT0uKoM0BTJUH3frmW61cK9KnEY6sw4cTzcHWzZjvu9yfd5tiXey1LSZL5RI+M6Yl6aFZ3lrOusScZExSXm6UNLv+gzChtttv7U+ry796n3Fs9r9zjXl+3H5Xr6Lk2APGldsYLo4gX+kUDzvMA8sJF64oLV3TAe9a1KN/mF3Vvb4/RzXU/MsWfiELuSRdK0fDoelKZEi9CY2LBb85qnaRlGK+NzyQzjzDoHBilkeSzf+Ava0rpJeNxCq+O66o4EUej56xjdjl5K8rXjnkpumMqVu9GdJYFBWUKpUovmevGMbcStSTynW6htcMGIDK/5qWZkwqZFzWDzCH8CgfEthsttCpavEC04lpclbm90WVrUVdU3BkPZvEJYBEXdNXwXaoCJ0hpcZHW7FqZnbC9a0t9nlTDPelF8VcR28uvcarz1Wbo82hR80zRBZXnpuZ9WGw4RHgEKroI5zWPrnygFkb9YfQpUo4BJBk1k+9K3s+EmCAVA/L7e4f8CL+mz3I82//b3LU+tZEj8e/5K+ZyVQsOj+AXj2KzVcYeYA7j8XlskuwX12AGcMXYXo+d4FTufz91t6SRRtJgcrmro2o3oFG3Xi2pJXX/GqsEtYR1D+4f2Bo4nN1jenqqCSv4vQgQTbUpHDQEuCye
*/