/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07202005_0851)
#define FUSION_END_IMPL_07202005_0851

namespace boost { namespace fusion
{
    struct reverse_view_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<reverse_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef reverse_view_iterator<typename Sequence::first_type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& s)
                {
                    return type(s.first());
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
cWs+BFwAbXhUk7EG0YfNThvM0fZicVY7grFImaWx/SAKyc0F/XM/nXHgUk6j5q3Dle7YwLSinGARNkVr85ga2fBjFBZtp5YGWth8u/KSBBPO/vkrJJwhqDfQotTf7rMu2jaDZRAuW78kSqxZE0Pv8fvG3j2a/ISyKBtG887sbNiKUgVg8c+vG4j4EsYSxcsebsolQToX2aZ2aqFOFyl99WgBPkhkxfcZfpn46JX7uZnDGAMXh+2TmviO3nqBI1ZWPKCtC+YeYZEriIa4NVq1ZHOsGD5XFUR9MVtR1Esc/lUTgLxL1zVjU8dqGUGcZKFU46cjBgaMAjyTQBuwPh3okadW49X7GTvOjfVx4n/GNNrIw78+4HJd+aOlTc22a8atsPPbq/Arp09v4SdBCfqdhy55XVNNn3zGbn8QusgK+reCyZL0eUhfW7YKEltcMnHObu3ThEv7SaFu6z12W59iEED1+O6NaiYy+lwUb7rIn70md9hASYGnklMZ9xWA/1vV35odAk05tPaRmRUBo5H2e+5o9kYy9PzNTlJTWKOINsnjnuo7/UTnXmxizA==
*/