/*==============================================================================
    Copyright (c) 2013 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_ALGORITHM_FLATTEN_HPP_INCLUDED
#define BOOST_FUSION_ALGORITHM_FLATTEN_HPP_INCLUDED


#include <boost/fusion/view/flatten_view.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>


namespace boost { namespace fusion { namespace result_of
{
    template<typename Sequence>
    struct flatten
    {
        typedef flatten_view<Sequence> type;
    };
}}}

namespace boost { namespace fusion
{
    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::flatten<Sequence>::type
    flatten(Sequence& view)
    {
        return flatten_view<Sequence>(view);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::flatten<Sequence const>::type
    flatten(Sequence const& view)
    {
        return flatten_view<Sequence const>(view);
    }
}}


#endif


/* flatten.hpp
afNzYOM1USVdBp3KYtLtIcFnkq54LPZjtWT8+ChOw1PUz5X81xZ/Lk3Y9h4a6s1wjC3nIzzPFBWh3CsWIcfnvfTzSpxj/bOTpA02TRsXI/s7reznu6vn63uV+tOdM7g3UNIywqpsS0uZrpCYq+yjdNMOMznmlND1FeTDelZ+lsi55MLic8mz1nnpb0Qutb93tE/1NukDiihzXg91rI+NX5GXg/UfyzS5xARl/B/ddL1s+2DtmHpKoTpNTTm3O6D73aav7in3o/HHZlgVBzDTtK/vLLd81Vau977aHYMa+slA4/mXg2OnhlKX9ud5xu2ZkVs5/dYvW7QU9FvZJxbKPrHwG1k225u773rZjO//8bRp28ZzHwppON6x9FYz+Un6xMvSJzqd15WTaz5q/31vx6Um/beUi21P+oYO2mdcyFWeKXQy7dcNyzorkjmobZWyx/ZW9/9Lz+vuAzM8v2fcBjP6qAvxnIwjtRJbksjrW109WC8Yln7MVY8+d8j3ap+bEKV0Luzk5TpPgnwu1x5Nt9eGNve92dx/KvVmf3zs6fjagdmxsOEYelayWZsmR9vrdn3lnSzUTTNsjwPJyHJBrSPOwMJmcmxlrax7PIcxnoeF4gdNlM9kz6CvJ/U8TMk/MUK5wZMfWWbZB0TEmdSTXNfSn09rszZeX+CmBtvtJl0GXEqTvmsB+int5QetLohIi1oZpfddhmt7ZTgf1RZXe1fLHLUe5Nqc+fXObX3p7yl7mrLN/2B7fWRaXWv7sMj2YXPsFNJP7teQ49k26M8CuV/Rlle7/jbVevpY+vqXYwhZxjA5ptXOi2Tb0PcR9sskZZfviyhCuKx7/WdhtsdaQf3VQuTLtZ0jxFDlfPxHWRZtvSnrsPzn5Fo9ltyejevR0GZpsg6uWYeyLgJZhoHK/K/arsM3rXlP59Kl/XcQdQaohT0n3yOeJYYry63OQ70C0bXs5yO6/lxrgx7Sd8fS68UnyLJqbZO5694j1As9Kst33nbXKpnQcE7VZqA8t1dRvR+mBY5kJtlFWvnVpifr6mYp9xEU6u4jYAZ2/ZCrs/0+y93Z/vrKMO3a+KykFEuUHENp1yvubJ+GupH2bzjPtr9mESpptfqTNhSkfc59DrrPQ7TP4xMiY+LCittctFbfzIcq168HKX9Y4kztWJxpZd66aSO1aeckhk1X+54A43Uj3fPxp+tbP1eys06bZrz+IseiDWibnqzf1cqYR9futOn00vbb0iYmyXHWOGKUskC/3mkTCVF8MVyOc31H38VGDpIxauX618ty/ctyJy/5jrjsfYWuzRn27dZTNFk/9u3Qq4zX75Tj7+duaMffNsvj66cWKEv6wa1KWjJLv2mdXnk1iOwR7355gg33AxuuR5l/D+C4n2c6OZ+SZXP6zfz6fY4MMLpN9s8bcSzLZlGnlwe6pqoX5MpwHq0cu239p/13dOkmy7wWP+tUfEwi28KdzyL50Lp8WYZ6GKxtW9ouvMTrOhbbfYX0RbpjfUnv62BfE23yPWGgyfeEwbpnFvjUWu99rXVBH2yo93x/2cdIvZ/F8co53b909S6FKM8+1Xj9LdjkeFDqyngcJMtq//24RVf/8i5v6l+uGUy1XQce9nWo/15UPpc0hv1W0VC5v1uOmwfhBOqk8HfbOplZpnZ4922unrQ5s3rLvnMcrS6cfJ7joD7ztDbBnBPluyyT9iv3pMnn4VG6745Nv/O0GLaJXg7q3Us+l3nqyyzX27W/kdD0OEzO782P/5tIm3nXZj4ygeyzCmjrl4fyd2Vff/vOPitIfw57pw3LZ9y8ZLIfOyEbQSXZbpxwknJtkt+kjVj7KlpJqecSDq9JSnuQ7V0=
*/