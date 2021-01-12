/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ERASE_10022005_1835)
#define FUSION_ERASE_10022005_1835

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/erase.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct erase_impl;

    template <>
    struct erase_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename First, typename Last>
        struct apply
        {
            typedef typename
                fusion::result_of::erase<Sequence, First, Last>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* erase.hpp
YgCBs2k7EpGOHOShCBWoQyNa0Ike9GMIo4j9NO1HMjIRQi4KUYIq1KIBzehANwYxgmAC44B4pCIDYeSjGJWoQRNa0Y4u9GIAgVn0PxKRgnRkIQ9FKEU1GtGCNnQi+jO0G2kIIReFKEEVatGAZkTQjT5MPYf+RioykI0wilGGStSjCe3owgACibQTcUhHFnKQh1JUoA6NaEEnejCEUSTMpq3IRSHKUYVaNCCCDnRjECOY+lna
*/