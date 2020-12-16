/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_07162005_1031)
#define FUSION_BEGIN_IMPL_07162005_1031

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/transform_view/transform_view_fwd.hpp>

namespace boost { namespace fusion
{
    template <typename First, typename F>
    struct transform_view_iterator;

    template <typename First1, typename First2, typename F>
    struct transform_view_iterator2;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        // Unary Version
        template <>
        struct begin_impl<transform_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::first_type first_type;
                typedef typename Sequence::transform_type transform_type;
                typedef transform_view_iterator<first_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.first(), s.f);
                }
            };
        };

        // Binary Version
        template <>
        struct begin_impl<transform_view2_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::first1_type first1_type;
                typedef typename Sequence::first2_type first2_type;
                typedef typename Sequence::transform_type transform_type;
                typedef transform_view_iterator2<first1_type, first2_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.first1(), s.first2(), s.f);
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
Bpg/s8IbKwylHoGV4HFeE+ehZbOagYlOd9LP01kBK8Rs8YK1RuotmAcbc1WF21+jiaSCFr5jhx/1VrJ/re1T0PRgPswul8/YSP2T4swN5m9HM4F5Mas+M7AymhmsJLO2B8RFNCuYH7OS7ifD6DyAubHcr46r9Q+aHYzXely3mPd0VsD0zN63GOODlgkWzCwp6eImqqeUQ0i14nQ2RfeCcfe9i2RTzcAqMDt/Oawq5Q5WlFmbQJe9aBYwXuutB6Y1prqAlWb2MWhvH8odjOd+OPrFY8odzMjsn4/tqQ9ZYCHMfjHHBaGJL4QoxWzL9pm7KD+w4sy2x7YpQWcTzJdZoFfyHMpdsr6NDx6gMwbmzezErpBGdMbAeM3iimwrTnsCTMes0oU9FdHSwHj/1rktjkDLkHL4+s+EWDqbYAHMquz8sTadP2m+OmN+185Yj4L9i+3xvjWaDqwis1uPylRDM4HxfV1v2+I6aPHSmBGBPaujJYLxHDp/WFMPzQrmyezNLvN/0Gxg5ZgF7Q7tTvsFrAyz0p1sdMbOgBVh6wwvmjiB9hIYPw/f7WrYAO01WCCzWf+22ooWZBGiLLNi/TsUpbqA8b6/zVnbAs0MxmuW9NXPOvweukSLdk0OgT8p/mxlRzQ7mDezcmcFfa08DSwy30Jh9PKlynxAywLzYRbQvuF/0XIs2jUZTCR+GzMK7bFktSb83B8tF6wws4/NZlRHew3mzuxD8UnxaKIn9IHZqbNbdWgeYHzM/3SeVh5NB+bJcli2euQLtDLSmLMPzD6CZgTjaxn/hf84tCgwrLUB/mRZ/9bj6H0jmFnkPXsb4fdna4efQMtk6wQTgRlnuqBlsTHBRL/SZwLQdL2EqMqsp+W3BvSZOBjGVYDX9T2630KzgVXJt4oC+txrXxG0PcwqwevirkO+ox6BWfNzCIPXC9dbJ6Gl9tZ6CyZ61rd3QRsv2c2qM3vRWsBwL4GJcfUXPUezg0Uw03cJp7WcAsPzXlnA+H0npqFdB8PzACa+qJ+wCi0brDKLa3Su6DI0/z7acw/UQDyr2ZRqFgSGawETVdf41EIzg2HNwuF1393QpWizmEG8cLv+wgvNARaV/34sUsB+/GlLKbSIfloOYCJs/bfN0KLAijCbut84AC0WDD83BRONbxWtjJYI5sEs7ud/dqH1AXNnY1rKBdPZtIJ5s7j9l79ZQv0DK8ZsareKVGs7WFr+fqkKr0WX779NNeuv7XkwsfmLcp1onWDuzPoXGZqAZgHD6yeY8DUd0r7uC4b78zNpf3oka/OBifPTRlP/dJLFRw00UN/B8DoBJtJ2t4lGCwOrwsz9+fMAWieYPr+3UfD7Ez0b3qe+D6A+gEHuX4XVQ8sEK8rs0Owh99CywbyYrT3YPxwtV7JSVR/TfO/B8PyBiamZT3zRxEDoLYt71ejOfqoLWASzmNhuVGszWGZ+ravB65oDpY+TDdL2BJiofjFxA9UFzIvZhyMLT6BZwYKZxT75sxqaXYqbEdi2MlqaNJ/D0fIDWgZYJLNuDZpS33PBsvNzqA6vq+bOuIMmhmg9AhPf/fJ3TzRvMNwvYGJvN/8faL+AFWVxR3f+5wHtFzB/ZsdG/dgIzQSGPYqGV9/dxvVojcHwvMfAa9x1l8toLcHcmR3a8sNSOkdsPjChP72qM9UarAqz3kti/0FLB/Nm9nD5t4XR9kjzlUzZ8BuaAwyfB2vA68tiXyaiZYF5MLv4IbMNWg5YGWZTG91ZjqYbKkRZZp71GsxGiwULYvZsy7skyh2sFLPlr/SxaKlgfC2ljjz6Bs0OZsvfEzUF9Pl6wkq0qBTtPICJWVvtGWjJYB7MovsPb4U2Egz7ByY=
*/