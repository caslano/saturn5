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
SnEE3yiO4JU0Fz88KA7xi4VKCy9v6cDgqE3piC1DyQrX16aYGMn46Ww9Y3C5ek8GU6tcpMCIoxXhkcoG3cvjlAf83jkHceQokWQFyW6YRlJpHY8uV1L1BZglmxHJQ/2f3+I7WvmgCxxiKAa4NzgzGZsHpkDfgyQCkIP9UGhl1OpVvsP1Wk7uLwMx86ayOg0mXFBCPKQXavBCuxyenIajRNRoEI63yNDWv0wtxPyTWJG2y1U5bqwJduxQh7Q8Rw7rOBm7vDHQU9X6gsm0q2oMfje1KPj4NnHMWIN69HW/p1yYIM42Sl7HrmXpHH0I/1WiLNa6uR/pMep80qSz3sg0s7z2ggk45ZLu6k1LVTg5NEclWrvqE7BIo2c8+SeNdsDnM0Z7EMhhCRwlXbuSxsCtF3jMaaz+ZwtmShXxYqGt9FCm9FTdeoSBlIr4Bq5WisMMaalLpk2PZI/1w/h878+FyvdFhxuY+pv6oVSwT31/O4kvNwKVqKAvF/jrvi0uJMmr28mfAMYu2LABXoLEDO2y+hwd0iO/SiLIq9w2vBFVyVlnFzNDx3ZZmnRABymv2i1LHjF1I+l5vtzvfWFuoi+3wx+ZYpatB9VH/4ScvFPXjD7xNLrlmfhp1BboL4dK00yxeaT+4w0TTSNj4pwnLVNPpPsQzTZhvxmTNCg9NZtjP87cAzThPrRSzqdD+kzWpzHT/NrNtCE+LULovs9c
*/