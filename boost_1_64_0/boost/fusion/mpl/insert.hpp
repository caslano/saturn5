/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INSERT_10022005_1837)
#define FUSION_INSERT_10022005_1837

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/insert.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct insert_impl;

    template <>
    struct insert_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Pos, typename T>
        struct apply
        {
            typedef typename
                fusion::result_of::insert<Sequence, Pos, T>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* insert.hpp
RKdRnbZFuByTcctQNEtLgtm8tWSoDOjORWuM5qiCKRwIGCqnMSoyeWZ2c69k3DYkp3Xr6bsDrTw8HdaQ9fnQS0mmTcZ4eoW8E75fes1A76wvi/GwK/sy9SFrf8m4Lc413FamlVafyH+TPmT3gdcQevsU9XO15tAd5bWBwYM1k/WFyPNDonq5Kd5LbG6EDDUfsjmk86Fa984I7HYQ04P3l3MP00z2pjHaaKD7fpDnX48I9bb5FsZWwIQ+ef+RVvd3AjiMgPHvaa/yvcNAbzaaTofvEtHD9Ybco0NmnToV8XZnqPvzpphzR3Tn+w8/5yjSWnhMyJ1cWerw2LNhdCpQvpNI+1OBvl4fhkBSHWkNGH9guIO+K9TvX2s1EtaLt5M2QAa9WiGnUfTjVqfmz/rg9oFeJ09J1vnzhM3zR72o0jgPGzeTfTj132PUj4s+oXfzUF/vLO1nvbhH6aSNEcR9UnH3dZw+R59ZwOF0tDet+abCv+1dRuvyvEj+ikrT66Q/GfZD9P4spclNP9p0Gkv2yT+N6K6xi3Lp//j8xNA7r2Ol8Znxu/q08Vnd5Cdal2nLaU2dZcl/32scLLR5rVGQCbSm1ihIse7r46OPLMrUrqOOhc5Bs95lnVMs8rp56MpOn7xr+tlQ14y4DteNpvcRJpR+pkV+TyLXcCatHp7t6z/dM+K9i0zbfobQ/HvD6AOeKTUco+R2sNfr6WcQ3WJtmjnx1s+WZTiTYn8xuYPlODPcR24fzbhF9402GdYK6uuYZ2jAokva5J8vLlROsV2U7sb6qXRpZAHtchZaw28O8br8iUxzDvnkCXz/xKWW0oizWPfKOJrMVtK3VnBW996Z5lIu7oc/9pL4e/qdVq6H/qPkb+gpnOAtn94urc+Ol9KHfOj7dXJ8yV8u5Mql4wfdszh8zr5rGB8ZMairyytm8lDpLiU89yPHs5DjZLGPETJIEs/xSldQTPyQpJjj9SXvv0EqfZL8GaPvdzr8sIheLs1MnShTwtLKPgQb2S1ZJH4KvumjlS4rZhJr6zqMmaD+pjGmXtFww4eYZHluGIYLFO3zmYpxBsfn6J9ttPL48XtA376i1elgBv/+SlanzcUEtncfpZPlcr0UH3fJQEvtAHl7TPhbtgW8SX0lywTleYjfpLWstAnYV5Rju8Cey1UMp21DxN2NspxM2NpVLSdtZCyzNcONtJMV2J75DdsK+vizIcP2cvMsbsPEbQZz46uFPNsN5uqPswyXI9tO6QmWkzaG9TETp7UzxH11y0pbg91GOeSFbeaZIZfaHOZAzw51tjvY/jXiDNke24dh2P5wh2TFM96VgK9Itif+PjQ8jLkUrtDY6OTdhWuGzFlAOIOhGWOYGIPyAceFWkN5XMswWXw12JhmjDFiD+LahpPJ4nmk4bivyGyhcB3NxI2Qx4+e5r0BinP8Z62+X7T/+XMRnZOPfjG5/45cuS7WITY1GzVmjH/X1awvkBmUWVfrIml3Qf+qwwgNcwq2fj3DsVGKMXdguSxd5zBOPUszzlDoz3fB+cjnKJ0NUvhKpetHGDJIyQw0wwZJDPJ1gzhDjefuLl/w4+8LDp4x2sHy+UMtnRG0O9QZrHF9PV7ZOQZZ1EVcz4IBN9Bp1oOxPMtyQ8PJvoHH7Rgn24HcC7qRZWUfgf4mynE/kcXdvLHiogM39v3jrEwm77PcxLKyz8jG7txNNTd68Oaxu2t/g74D+XrZVeJMVpvEYm7wgHh41Nd00C+MYjj78NmLD/yfrOtzwG9ZPtbv8Hh4M8Oj78H4/BTLcJ1y/9N/quVkP5XVU+9pO3HlTmuBDgLQUghNr1cwl7DpDPo3Zgs3j7Kyj1uBnUZZ7uc=
*/