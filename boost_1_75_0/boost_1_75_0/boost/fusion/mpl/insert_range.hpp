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
aZAyPb+WrvUfPQcX/3pO6uU/D1e/1GxfbMPR9PdHQvz2EWaszcxYsZmGjza2vSXW9ifG6m1PVfwP+pRD0OTl1btlaLhStwX7ILm3S56Div8ObCweFUJ70jizjWc6dUlv9a8VzxToKTYcrSSeewlEFroFm/EYr7JHyoQ5DZ1XoMd/DXuegnbXQG+wZ3+FHjVgj36NPfoS7hyVw/P/pdkyuVep2Ksda7vq1TvxvueMhqMxGg6fE/55o4GGQwouNLoKTTA0G//kUUpcCtlxR5xwyJsDa9Pfqm7djorC8cGfWkFgWtUK11/ko9Obu/HGsNfuxxt3Z5cqEoobbXVpgVRlSl+oZ0xbnTlgV+baUfdvFYeyX7yLMpuHkuAUKPRAJjKqKeQJQjmC7Tjh0nuJ7fTZt8wmhLQO9tBsFZvNppa/mCg/nx1r9yF3KaB2vgjtxGBYZT6syjlpcu4H8sGLwIv6O5qkoiY3ZbnAyEv1TjicQUFH09LuiNg6JQvhsLlCCzTdne0OT8luq7PTdwzTaqtLwhaS0XVKHncQ6BWekinaTuLRlLS2Oifd8YWnjCAIICILd9uym3z/kH7Y1jpo6y5EuRHbw5k1PKitZt4mWGQkp3TDB4FzxF82su+NSRxZ3N0okVk2kZjwo+LH86ta2uj+XI4bXTBuPKMNOJ4/OXmflTwcS5UenLOziEdGKcqkCV1EQ6sUZcOHmwPMocwI
*/