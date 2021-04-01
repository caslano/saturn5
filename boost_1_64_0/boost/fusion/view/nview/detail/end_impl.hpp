/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_END_IMPL_SEP_24_2009_0140PM)
#define BOOST_FUSION_NVIEW_END_IMPL_SEP_24_2009_0140PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct nview_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        // Unary Version
        template <>
        struct end_impl<nview_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::index_type index_type;

                typedef nview_iterator<Sequence,
                    typename result_of::end<index_type>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& s)
                {
                    return type(s);
                }
            };
        };
    }

}}

#endif



/* end_impl.hpp
zse+DFhiAh+UTio+C+4Z/rdH3b+IXC3WB2dH06ecoHr36WSY8iJdHey6KecykaipH2FZJ3fJkx6bJ1CHMZOCKZ5gAjsRuqgoukJ0xZ7LIikkikUbFrzqD0dIDM0Ipb8QV5QmpCu1+21pvvW07ptgFS5kXnAYQKRh2cXPZ+dQGC1/2qj1YRU+ysnrG18EYp7wj0598001Pj3ygPIEQ3TEGy7i/zQJQ5YKphyrIeVrdO7BQDG2G0moZHrTpUW9azJ3FboGlA19lLHBXyOISiAaVADKFj6slEl/GFG+GfD8GjMlR5Tzq9x+Tjc1vEadC/DBjuJ9sFz3lNnjp7yI38d/WSz+W/vJAYwKR9nYqdDVRJMjceo5p6YlQZgS4TygJSQHGSEFAZ5RmcjVM0yF4/g7iwnta+fS/yIX49jZOYhpwNBHW9mSEKkyN9lrmXRdPO05u61+pjryrJhKsROks5f0zKCDTk5MYhvANQ2GrRTyLgfsJWnG+aLr2XvBAbWHM+hmTcCG/QMtN7HafokzCc1YgfKqOidNYhI4Gio2uAmyibUnPfEpdJ96Nhjouw==
*/