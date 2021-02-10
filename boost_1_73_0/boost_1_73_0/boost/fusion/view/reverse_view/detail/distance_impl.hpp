/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_14122005_2104)
#define FUSION_DISTANCE_IMPL_14122005_2104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion {

    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<reverse_view_iterator_tag>
        {
            template<typename First, typename Last>
            struct apply
            {
                typedef typename First::first_type first_type;
                typedef typename Last::first_type last_type;
                typedef typename result_of::distance<last_type, first_type>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(First const& first, Last const& last)
                {
                    return boost::fusion::distance(last.first, first.first);
                }
            };
        };
    }
}}

#endif

/* distance_impl.hpp
YYuCHmluymIn3aKDPoLXh+7d9fvo6PSm8+f7t1H3+v7q9jLq3N2ezLAeEqtLmvTNksh0yGKSuPB6yIdSjecPEPo8Q8+tAa2GTdmMaQMTElsSPvl7fB/QhSk7ikx4rxx4dkL4Hc+5EjGcnHe6mPADqTAmwwp/cFHHjC1RbCyHBUZbO+JEDLg2moJdJcAY602nmGh57Erqiik25JharqYwXZ0MimKhZMyTEiNviw2B3S4LSMY5G2I0s2xMBWc1OZ4qwPgzN3xksAkIIxjWjj0hkzFcmuhiokFUylyLQY7WxSlTQDhHomAJvIbd0S+/HTxJLCvil92DWo2EqzJ2RkWVFY1al6Jl35FFgZM2S1oQChoaBI57DmsLDXaVCY3/+HiJcEIicgNIkPG8XvuMVFp84hGCckDPq+yMzcjQ4YKSFIUsv+6hvzhfsLcrzrAh+ThYUTsENIBAZEip7AdWdh2a0MbwTL3cfmNRpEMihKZ1ZukcM6DMDDpCZhAxCh5iAsg4EHVrh+gHP1kVVoDCElQ5OH88ixdl0+/1jIqD5XP6uYdEwYMUCTTqEFidTdirr6Fuz1EHDrf6arlNH7C1KNQrZE9dq0X4qZkaKSGTOU5IxYuMxdhhDfTwCCvMeuXKrcK+H7jYw5tlTUM28okB
*/