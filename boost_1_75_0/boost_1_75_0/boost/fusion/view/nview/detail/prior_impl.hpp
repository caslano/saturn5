/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_PRIOR_IMPL_SEP_24_2009_0142PM)
#define BOOST_FUSION_NVIEW_PRIOR_IMPL_SEP_24_2009_0142PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template <typename Tag>
        struct prior_impl;

        template <>
        struct prior_impl<nview_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef nview_iterator<sequence_type,
                    typename result_of::prior<first_type>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.seq);
                }
            };
        };
    }

}}

#endif

/* prior_impl.hpp
yqlzmSN7VhRh6SKPuzJz1mHOBmuXodnIlYVgo+geRl8si857cU3Mj/H2Unfja3lxSipO3zeGp1S1MHcFYHP+pn/JXS4CwV8YmD/hMP1o0PyrrHw8G9Uv6ZhqNRZaN/cVssHSFinbFKWcHVWD+7G863JD/8Yg/yY5fQcQBAwTybuJP0xzQxvO7Z77ngohfD/g5MxTLxP2qoS/BNmyFxOFGkhSxRpI0IzgHPxxpSQEmtDfHZPNOzJdcS1KNasje5eIb9alMqIWyRhVxdY79VXi7/64Ja8CI48tnmDPh0Dm0vXzbcW2Jj30KeEyP/ke37P3TfQH/jjIbCPtiZeDcfXqZxWNV2rTf3ir5LAB1vjQZx1YK/XjgpdyH0QaLS4VbZY3LiLww4yum2wK7MjK1j+vfuW99AXCoVBvap95ufXBKqzlb3MWpcipZFV4kbdLrQcpkopBJJB+9Ul75m1A9nVRlx9lzIeXmQlH6Kpstb/S2WOp0fIz2fbgMOf2vdF1pPcex/5dBKPJz2UNM0HPPuNYVcVancty++RSeIztfl9Orun9/anDu9Gf0Mq8sQupqHfA4KtXNBKImZsoqVcaEAnWRa0o8Ff2UUq49JMeV4pXpje8eLWf864HzUswIqjqu+VcLvUyM0pRpKNbCt0s0+Ez2mZBXFZkRPAIk7If2iWPXTol3uddovwmUQbrRS5J/5YCSff3wnhjutXkUvVb
*/