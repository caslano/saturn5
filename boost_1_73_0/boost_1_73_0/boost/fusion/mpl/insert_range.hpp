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
u4YAABYACQBjdXJsLW1hc3Rlci9saWIvZWFzeS5jVVQFAAG2SCRg7T1rc9tGkt/1K0baWpnUUpLtbG3dWZFzNEXbrEikiqTs9WVTKJAckohAgAuAkrUb72+/fswTACUqt6n7ckpFFoF59PT0e3qap0f/vp89cSSe/Ano/wB+4F/qcZ2lv8hpUd86CH4V/B/0+hv8+9Qkp8J2+TVoiqe7/Coa1CVQs3yPfwfBUxP9DWHDX6fY828B/glPoBv27KTrhyxaLAvR6DTFq//8z/8Qx+L1y9evWuIiTCIZi1Ehk4nMFi3x/Yye/Ncy/Pr1JJdvW0IWIoxP1FDjZZSLPJ0X92EmBfwdR1OZ5HImwlzMZD7Nogl8iBJRLKWYR7EUncH1l17/Q0vcL6PpEgd5SDciX6abeCaW4Z0UmZzK6I7HWIdZIdI5dIfBZ1FewICbIkqTE5hbikJmqxzHwOnDOE9FeBdGcTiBicJCLItinb85PZ1ushigP52l0/x0qpd/sixWZiVfAIhV+CDSdSGKVGxy2RLYsiVW6Sya47+AEHi43kziKF+2LDQwVTI7TTORyzjGsaBfJHMGW4qRQk8Lm4k1QBwV+E+eJjlOdb9MV15DwCOOMt9kCUwEeIBGsxTQ3BKbZCYzakwr11MonBKC
*/