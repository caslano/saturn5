/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_NEXT_IMPL_SEP_24_2009_0116PM)
#define BOOST_FUSION_NVIEW_NEXT_IMPL_SEP_24_2009_0116PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<nview_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef nview_iterator<sequence_type,
                    typename result_of::next<first_type>::type> type;

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

/* next_impl.hpp
X3Bm/nYnmuujZS9jZZP5aWyxomtaQg+UHweLQOoWIt3SoUsyMzTLMEYwlPsuY56FKrIWNBKezf344uAb6kM2hmHAHvIjwTigWfr1xcHngwMeDRckjQ0y5FuLlR1VhIYOHz0cX+lcRohHdR9YAAQ1JAfJDmKWvea0QxlgHtx4seK72ibYsLAZTelb2tWV1jeH7zQLWs45oywN0IcIL/Dk39EuyPljseG8JXi3Dw8vOIF5RO2PFzWsbjTI6YNzLk5e/nXKEMJAF7Tzq2FOAURY/Zlh6jdT7aeZZpgfBB932Xq2bksq/HEzFRCT5QfWPHAe26n6kPrhW603AEFhi33cYxTPGgyN3mvYsremOZGjKcSflHSqRskAtpR20SnBnduZUXzBSAQEtSa6YZ5Xd1lX+vSmrv9meKOdZ7aeS489Us3ikyq7jMzM3CYwq50PKrETLz7HuMjhrcQGPoVgCkg4hMAuYmAJvzfaNj9o21le3JotAnK/Kil8PlB/UzdUjQVLXuOkz3Um2tfHpjY2LfN2otU4A4dsmRhaa/aT6fBdzywnpzwnY/MQ+O7BuixsqaV7ZU4skHV6a0165ltBHjZtKkIQohuQLnoM7XiF2AFh0TKSoH4dcBi0wCSt8CMgJKVTDsvCwPUxjD5AwcNr
*/