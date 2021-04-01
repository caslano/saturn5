/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/value_of_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                value_of_impl<map_iterator_tag>::
                    template apply<It>::type::second_type
            type;
        };
    };
}}}

#endif

/* value_of_data_impl.hpp
NX7P47YpRV1HtS89ZFp4Lu3nxVDF5HIx7tmVNMX+pr7D53mHZZawFuYy3W8s8h+2Bg8tCN7xKWy7NPej2auVhAV9bzDf+azbJPvCtsJxNGReUpWgNbgaKOYAvVW470lFMS2x9fKalxkRfmAM3cGtCMfdRv6LdAKlqZ+nQr6S3tVSFRX1iSBUpBelz2DLciKC9wJv15U4wUFCFVS03g68OvDtSJPERv32+Sc31tWBOLTZhjB9Pe41xUpfZnFH/Av8UAE7T8q9PaW06sQNytYks49ppV2T+STl2IADN8zQWtMHiSCtURJkC4KW918e0wwSfS4guvdVfQMkvX2BaQld3Vd3CQqCvTNZbu/spVXxfgxcNzNsirJjIx8Lh7dlndP0MCMiQ4jC4zOfvMJ0YcIsgSOjGiAoBS3QygazedhJL0twm5gyHryrjg5fO4SqPfjhA+n39Kxxc/FoB0dmgUf5YrEHNAEEn4Xzt/wdVMjIJLxwTbphFh9/Pymzres1aeUFsgwbWUwZ2+GFS3ewOtP5YpwLz4vCSMa7cQxkpKf8bZNpqewrn2WRmu2VCA==
*/