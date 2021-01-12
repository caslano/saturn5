/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INSERT_RANGE_10022005_1838)
#define FUSION_INSERT_RANGE_10022005_1838

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/insert_range.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct insert_range_impl;

    template <>
    struct insert_range_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Pos, typename Range>
        struct apply
        {
            typedef typename
                fusion::result_of::insert_range<Sequence, Pos, Range>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* insert_range.hpp
ZCAb+ShDJWrQhFa0owu9GEYgizYjDolIRxbyUIpq1KEF/RhF9GLaiWRkIoRcFKIcVWhAMyLoQDf6MIgRBL9GuxGPVGQgG2EUoxL1aEI7ujCMwOW0F4lIQQ7yUIQK1KERLehED4Ywiuhs2o1kpCETIRSiBOWoQi0i6EA3BjGC4BLajCRkIBv5KEYZKlGDerSiHV3oxQCGEbiC9iMOiUhBOrKQgzyUog4taEMn+jGEUURfyX0g
*/