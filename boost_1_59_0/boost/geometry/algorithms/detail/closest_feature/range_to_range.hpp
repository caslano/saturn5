// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_RANGE_TO_RANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_RANGE_TO_RANGE_HPP

#include <cstddef>

#include <iterator>
#include <utility>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/algorithms/dispatch/distance.hpp>
#include <boost/geometry/index/rtree.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace closest_feature
{


// returns a pair of a objects where the first is an object of the
// r-tree range and the second an object of the query range that
// realizes the closest feature of the two ranges
class range_to_range_rtree
{
private:
    template
    <
        typename RTreeRangeIterator,
        typename QueryRangeIterator,
        typename Strategies,
        typename RTreeValueType,
        typename Distance
    >
    static inline void apply(RTreeRangeIterator rtree_first,
                             RTreeRangeIterator rtree_last,
                             QueryRangeIterator queries_first,
                             QueryRangeIterator queries_last,
                             Strategies const& strategies,
                             RTreeValueType& rtree_min,
                             QueryRangeIterator& qit_min,
                             Distance& dist_min)
    {
        typedef index::parameters
            <
                index::linear<8>, Strategies
            > index_parameters_type;
        typedef index::rtree<RTreeValueType, index_parameters_type> rtree_type;

        BOOST_GEOMETRY_ASSERT( rtree_first != rtree_last );
        BOOST_GEOMETRY_ASSERT( queries_first != queries_last );

        Distance const zero = Distance(0);
        dist_min = zero;

        // create -- packing algorithm
        rtree_type rt(rtree_first, rtree_last,
                      index_parameters_type(index::linear<8>(), strategies));

        RTreeValueType t_v;
        bool first = true;

        for (QueryRangeIterator qit = queries_first;
             qit != queries_last; ++qit, first = false)
        {
            std::size_t n = rt.query(index::nearest(*qit, 1), &t_v);

            BOOST_GEOMETRY_ASSERT( n > 0 );
            // n above is unused outside BOOST_GEOMETRY_ASSERT,
            // hence the call to boost::ignore_unused below
            //
            // however, t_v (initialized by the call to rt.query(...))
            // is used below, which is why we cannot put the call to
            // rt.query(...) inside BOOST_GEOMETRY_ASSERT
            boost::ignore_unused(n);

            Distance dist = dispatch::distance
                <
                    RTreeValueType,
                    typename std::iterator_traits
                        <
                            QueryRangeIterator
                        >::value_type,
                    Strategies
                >::apply(t_v, *qit, strategies);

            if (first || dist < dist_min)
            {
                dist_min = dist;
                rtree_min = t_v;
                qit_min = qit;
                if ( math::equals(dist_min, zero) )
                {
                    return;
                }
            }
        }
    }

public:
    template <typename RTreeRangeIterator, typename QueryRangeIterator>
    struct return_type
    {
        typedef std::pair
            <
                typename std::iterator_traits<RTreeRangeIterator>::value_type,
                QueryRangeIterator
            > type;
    };


    template
    <
        typename RTreeRangeIterator,
        typename QueryRangeIterator,
        typename Strategy,
        typename Distance
    >
    static inline typename return_type
        <
            RTreeRangeIterator, QueryRangeIterator
        >::type apply(RTreeRangeIterator rtree_first,
                      RTreeRangeIterator rtree_last,
                      QueryRangeIterator queries_first,
                      QueryRangeIterator queries_last,
                      Strategy const& strategy,
                      Distance& dist_min)
    {
        typedef typename std::iterator_traits
            <
                RTreeRangeIterator
            >::value_type rtree_value_type;

        rtree_value_type rtree_min;
        QueryRangeIterator qit_min;

        apply(rtree_first, rtree_last, queries_first, queries_last,
              strategy, rtree_min, qit_min, dist_min);

        return std::make_pair(rtree_min, qit_min);        
    }


    template
    <
        typename RTreeRangeIterator,
        typename QueryRangeIterator,
        typename Strategy
    >
    static inline typename return_type
        <
            RTreeRangeIterator, QueryRangeIterator
        >::type apply(RTreeRangeIterator rtree_first,
                      RTreeRangeIterator rtree_last,
                      QueryRangeIterator queries_first,
                      QueryRangeIterator queries_last,
                      Strategy const& strategy)
    {
        typedef typename std::iterator_traits
            <
                RTreeRangeIterator
            >::value_type rtree_value_type;

        typename strategy::distance::services::return_type
            <
                Strategy,
                typename point_type<rtree_value_type>::type,
                typename point_type
                    <
                        typename std::iterator_traits
                            <
                                QueryRangeIterator
                            >::value_type
                    >::type
            >::type dist_min;

        return apply(rtree_first, rtree_last, queries_first, queries_last,
                     strategy, dist_min);
    }
};


}} // namespace detail::closest_feature
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_RANGE_TO_RANGE_HPP

/* range_to_range.hpp
wuwDpApEu370dE8lZcnaFzM+wS/UZdXuTBhQHn9yomVbdi/mDFUJjaoqzP5dZXwThrtNNzUh/O3EHAa3Fmjwnb325MqfRjx+itcCjMjMNxNsaJq3Nx4U1ggddL3S+n79bUQB9xz1/XXV43u/ooWt1iVKmr9Ou5mcZE6mSxFH0f6u10UjfM+4ccHoouuixiJcKmW/InsqXrs/aW3rimR2hik6IsTscKMuv40f1SH3LRvMQAUULSyonLCYu9qwi7+ho5mvFrnek9GjG3JDMe1VOPGgNlbWfc07aoT9FR9UHR1S7dgOcOw1osrdnYdLZ8H3Ri73Ersa3NaC7OavHWemna8O+EvUZ1HpgYV4S0yk5erun39VMeZZGlz7RlFnvg0D0IS2zy6P9bh90PLpuDxVjeNyaw15nuuSksApG+oeuMg+ILmAkr9nLLmklvAVLi0nW4lxQamvmz6QN6ZID22SMoQaRhbBKHC3aEV7TQWCPaZhK5753+o02jrshV+QFrAX/m1mtH3nIZOfuw/HK9nd7D9kLBSLXeOrMGQPzp2u+7mR/1xb6aulB4k0E8Z8OVi/SzWg8RXKl3QJF1oVfRjogYS8G5iBWRRsdqd9JLHn4OIuqMoD67ftsRFRppFfUnguphhzt3mRy8l8Ukng+moAiH1/y8zMR+uUoy43Z5fUbQ2B546T0xmRdBf0HN/TnXU6LO3R4tH6OGM+nAns41X7BWS1wBVDYr1008OGm8GAwpUzm0TpfTxHYfuWlQzJJPIP02ikzd8GitOI1k9JjPIuFu+We6fPNe5Cl5+ZLxdF0Ed930qbISyjYs3+xJiu68Acu79b5FXeQdrYOZxGwtyXDX1YTL0VfHPAhWQ7mQX+0gt+/jRsDHAIUObh9Wt7vLVrl/Yqx+6x6KaHPc2Pj/t83KCYVAIhSr5CWdK2CjFtfE46moy2NLLntDOSacYmJ1P6u5wyMJ/Y4LqSRcstdncN6vwLWaqWwXTiXQT5V1ob4XVgdQm7FnEkhAYfyoIPfYSfTBUJJ4+8vPnti8kd7MiCmTRE+bz+KMKE2hZWXeiPnr1NtgNrVrWSQDU7ZujYnZ1H9bRyevAU9QDfcMN8H6LUdMPcVFCWOlL5nV54yRSRiiPTyevynA1Dz+WrxJubbUaoYgGPdvwSSbgDxX9x1/tQ63oV4nSVkVTAb2nOYUOJkmyKBEz3UF0YaOPkUv4rYmL7n8RTvRa1ntXkAUUmBE7SeuAFY+rp/kbtA/e+38aFADoLQKnIwF3rE8aZ6pZAE86R6hvPEluuTy09e0lvr1JatCrDwhJbAT/3UMsx1ym6KeL53jXzhn92MKi3BsLBuF4oGh+dtsGhKCB+otuzf9sjh21uRPOuPPUiRcZKPZFfJL8vik5RFSknct0wHTzlAZJ8JFom+zxPs0u5TPXtW8oiZwpR01OnheT0RdeiwCJABDsbhPwt5LmmVc9JInL9u2ItN0Pw0lyjbS9DRZWwjVxDHTdQZerjVLD82+dFDkrZRW1ub+iu2H89mOO1sr0toigqVA6l5pSgvlLgaegc/BLJgn/6IJ9ozTNt0CiSMioH/vagxeor3aHuaVSAknBEEJ47gcujMEXyHPxir5/1n7wiZl1VMOYmRR2Hgs9zeT65pKAUoiFnHhDLgxzRF9zDuzxCRgO7jaIXUoZ+d/yFac/IU7V5tAU+LrfL7FZ8MGjWNe9YOfN7NaalC3rDVMC7+IVKi0lX8Zd7UxmFnoYGU5bapU3wNXQ+xIpjll3gL7tLuKqJcHzd0/gXoWcm0r3OWpOtel5T8WSjnT9oVBQ0i0IWwICKUfXgpEmOO8AKNyKQkFbq8tQtFhP25mfwL7ucEGfGrbp9qfQDlJd6/VIRlc73eM1EYXnQ4b6WsBctj/3PVee7TDPdrtu/E/++70pZLkI3b5zH1EwU6U7y7Ff0F0BPNttRWy7+Vudt39l/fSAgOY8MgvotNVZo13XuRI3xGZVqqgzNVDzhfzdb+E/QR89Te0BeWPj+rG5yTHqHwPNdHC+EYKuv2+zz6O3hH2hqz4qpkmb9Z9D1oEKyS7JqpX8j+fXZFHDD94Ijvi6f1sZc26Z2+apunhaUYRYtWEeca/9oSKD/QqC/QaD/nUA/4cnsqUfT5I+saUr1vL/eIhNdVayI4RriOUbURK8Uo2nBuxMGRD2nKIGhlCCOFm/T/og/Hh62RDcnvLt3zKSePoQPMNVoUNpkhX5TQabv+uuUxlSZW8bc/r7ohn4Wlo0Lce/4enkr2/jH3f08uQaSx2AQer8XOnI68k61NZugXb0orMvcrMTYSPVsVu299RkNgGmHmTCw1lTfN1CYGQWu3s8sHh471SzNnFDvfBdCcORv8v2qIg1eYF4p7D6M809xYQr1fGrJoXifUEOA4WIUX4ewu6D0Sr/xrcKxvoJOJrhJ0XhVaMyxbC3Tl3Bkjaxd9vNO2N/dda8EIbgeR9eJwUg3WvVAWtyrtmDVPHl+V4HOC0PqVRv86N4tcbWS2x+e/23VtcVC/YZmYMPyrQt5Lrz1k0hcNtGND63HwMu4zsJfSJ+4GK+tf3iKoMkBH5hib3bhNU4hqE8Wwl+/y4Ri7S3cPYdw1wcyhdDAsplChGDDUginDZAnTFqM02i0zxniLn8DMdqzibvIKVrpMWrtEJiK/e45PvnCqMu7YXAm+mPfc/JHhCQaDfmbJhYG+H9XvooIWH0lI+ZYWTizyJXXywVr9PeKDmTX6lCW6fEvpLx3uKFxBaoEawKt701h9SePsZNgBHlIx9mCUf29hwT2Q+B/hrn2HiyNiHwzWvj9FOp8+dWJMlRXRNowNzMDqr8eFk1qUUj7fq/4odAwZ+HpnVxAYG0dsbnLo5ss1SyL5Jxg03PNOEEzU4NktOKQQ2AKvJMHzz2xq5ITav64Uhg6r8WfDHp5z0O6mxIvKmVhQGncte5v9edA/cutUeb92U4kU0X8qgH9vo3Wt4uR0caoBb2dw2Cz8QanfXzyMJnc7Cu8BowE1DVOXHITnAbR3QBne1xQtG4wxzWLbDZZe61XPObfrGrlPvveFpZHGq63u+HZyVXT8zuY8s1q6MPDzlvks6Eg7GYPd/90+6AnqlZd4U4PjY6MBnMF6qXQYz7GD67B0XOxj+EhC7m9x1mwyVI6t4xFF2rd25EQFVsdFT5oYwBhQCRvic4btLtmVRxvgfMhEy7sExOywxLyvW3/r5s5v+fpud/qs3q1nxnbgCCKGYpqgf1/vcx5XoVRCG4vmHD45Y2ni7L0BSpcfJHf8z48cfW/Lf1tYlhvAqo5Yn4P5tyWrbjDX4rM6MdMKDDXElTRElER0I72HeNUDvQRZZD1P7te1RwNa7JrY8EYrqzwEO902p9bESgy40NChB7S6VNRee500VxvOlMqAHIHR6URxacL24m/hIWG1hfWJh9E7XconHpHe8hBTORj9d8+FylxM0LG93rGi5xcPaJaeczpYpBufLMtHqY/f998b3gfYEkJcP2kaOUw1WL9h7V2lcc+eawexEW7th0KoFfDdUfc4vpxbwmjIHhhqz8kfitJQ1xA3m0ZzTq+7iJ346+WJDoFpw3f5WnJUcb4eyQZ+FJpgKTJVjUadDxzG+LfAet5dU8yIAhnRtMTD/q8NzarBgLBcS8/aCUFLtqqrIVUGmUr0NYT5wZrL2Vq2sSGM4KDofK0B/42u/5E9zaqtDbSxGPEj38Ealtbnz1lyLI6qldifdj65eiWyfaRRC97VaaqSYKqiWx8XWr/H5zvoOrmK9EgkBoZXg8GBuVc2OBjdY46pngm6SjOs4VdMcOLMRz1BdycCxfBcYk4grihBN8USdYOieJ0CF2JyrruceOJxB8YniDCu8mDiH2IfuHx+MSyDw+NqDPvNJ8ByiAvWVfMAqb9M+stezwVvqUkG40M5132WCqYsVEFn7u6spx7cgFce8rDBJDOK4kSe9tksMUvXFwrXvkXRu72LAK8S0U5/Mh/0kHQUQl7dFgP4x3K7XOPYmNl0jBe/P4GSe9jqQD/D2sUUnrW+Sst47X7joffCxr/VCY5H+Z4ClqK1ZQ5D/IqevZuad+mgwvf592oFuJOzg7EshfKhYp2+dL75114rYhqYWrMdQNMwpLEzN3+UmxzNuafLOePtd0FDk+z1h3r0HcnLZ8+BeYNyP7wvD9YX/+dMLGToF5sN9a2nV5lAgwBqsrJ3XvY7ovWhL1pywh5pxe0SDrC826+b28ogwDRYxldxyPu0srrIrTcKhlOEUfp4kBnbU77HnRXZmjafF3lfn6KKriq8gvQKyhoPupowJF3pj0Tji3wFT+SOTRlbSGZa3ynT1jqIO0pfmwK2u60+aXV6sObdl2VHbDwyyE0BhYqyeM7mHhhEXR6o7nrVCYpGV9jFTg57E22cg8cFctaD9Hp7L0QSADK7S79VjHl6g4UARoXrHeR7lYcTrhv+b/oDpS+uNtJtD8oZCLgmlPDVB3rNrpTzp3/SCnArwp89SEQY+1r/JRa/VFM7W7SiuybqL2EucdlhAzLU4RarmYEfiQm+k4RtssqIE1e6fiWdJZFhaJlsR9fstREnNgZ5rTm3ti9uytRTGq8+TWPT/0+7EPbx5wfzm+Vq5Q0dZqNQr1l09dOzWeKRRr+jY3l5kNXbj85OCzS7xkNIfqDJvUNzEvo536hz9+wxN/rdt9s3FtTlRtcMgyIRr38XPiGZU1RaNK+Lvcp1dETQuGHh/wXDlCoWb0CjqDhlZP55ZIOBImmP95twghIebvdSyNuNtvhzt3tl9vSWXrQ5HD42T1Ts+DbS+ttBTn1Km7hzx92ws6jsgrNhs8AqanHMwuhUmHUhzFI+vaz0zU9jLzIORPHvgrAxXYn5MB54sr7pYmaYrJr74bCKyitAGjsddDTMW+Qa7kB8mbApHAOjblTk0CikZDOvoYdg6yQLX7Ho7ZrzDHCa3a1EIRZ6fj7bL3R3kQP87fjLxUXeY4WPafrpymkXNQGLZNw1yI31L6uIy+CahtmFDJc/eHtBU2UceGntycOLwJT+lQcO6cfZAF2cQlZu6MD/V8cwDY65/0IQ1eengT+6Ks3c+G4DoAU9kmYxW3r2tgJWn8Sqvl94QoXN3te4z8MtNYJFRPuDtv+EknU0DBzbPyEli4+0MWFtbbphYlP1v0xZDq+G0x9itKm49i/B/lPrBesoE++hAhv4MSzl++7/FhFw5+B/Sa6Q4M7F7ssM5EVPaznMp+FH6aFj40BSa4UHkuH2rnx+i3SiARzhXxfNDTj3JJTnYBbBgSRaidCH++LxfRYIz5ucn8Uh8AbFuU5UF9h30ckaXStTBE7zWWU4izLHDOSOpe/wNfQXKFCWPMBmMZEgJvsNRAl2yQXJgwfHU6k+3utS1xLHJIDq4wBvQtN1ht80u9OHVYB46fZ3yDybZ/07JPsJmu1Hrzf9F/fU2/9apB+sijyvDUhgwDqSp82f1ni1XiMKJkuJwl0F3Lo4rxMs++z/uh+gjBUCOYauBza7/nHh27oYirhpx/waorDA3zvOdseNtys+Di5J6Mg5JG5Y+IHamPiP9vI4tGL4YHafTNLsss6E56uyuFLw+veBf8QorWqBv3sGVJFa/RtG30HKyLOvpC5jyarn62OXFYGUZLkZ+7+PsZ70XGSMFLIdgQqozHdC+M0L56Kuh/GPgCuQsICtb7JVuMCUhaof7dXpSetf9Y7c6HKl2cbhZ9q/lm1+hla+mZEsJFSeLJN1Tix9CNGEpt4ngJqC+ks4vVniz0004Zi7xQSqKvZvn69Iqeu4R24rmYg37dU+qBLXwOguWRuPpqVEal+nzaEWf8zKDVL+0CJ9XXujEW89+Aj8MzFBSQHMaW5ff/V+s0G0cuASUXtD5U6Ps+XrnxzPs9ut6nxR/CLz6niXwa+tAg5WY7x5F+OlseXdiSainRM5RRnHV4kdhPUc4GuRfLgU6x2P6UqSXzDZhK1EO73Kmdz7+k3WceNLzH6Hn+P22dfGE19YQoQnvb76SvzqU36y9bCxWBQXRvPHH3b/VP/ItU8tjcqlWpkUg7/vVYj5sG/wHNF3wayCXlSrciGz+vI0nQTTe+W9LOtWQ4VkrOGKiBw8WH0W7l2DaggCctPdBs49QtlPOOsi5PooKBaxB5eDM9tmHZdtAcf66aOrxgA5Ko7388c17zs69x2WnP9buUf3ls+NNuB5Ow+8ya0KM9fyOc59O1k2nOVNy32pZO+6lh7jvCTre6c/wle0/0g72cGp6PsPsPFmxSe7qjGtl5X3Hof+E11PKmw8v9NEva62BeZH7Tmii/Bk52goTuAcOjN95nqwLw4aHmeBX9UPZnri6EYeqgz3cr0359LE/MVPcwNl4csA4AgiO1jZaYX8bipUnFsyx++srE/LQ7H0ywOf6ZpqyTwAN/Rv/mZibCFUjiOILFRDBmd0Ps2j81+bCMngZSOz+L/dpyGYv5v51x+P4m+8PIglFnOe/jSQhEKLQDAV70n7+0GiCG7e7J/BuEYjclW/8xc6PeHnbcALyAd1OvSsqJtqHAnxB3z71QsGNqPKALbExQRBcFr/Yc4yvqSLkHVyNz1hUdHaY9yj3yRO0w+9OZHD2uM/UuqN+DavUdp0O/IHRpm4fn4c6p64yLzxchY9+DGL3ou1Bz1zoNCa2tXd9hyTmXKbpHhQwUFpm5MQuTxyh6iMVzlKeZRJ7F8VDWcJZ0o4DD8/17I6qldrc50FnrWul2j4iZLyXN+HLvrxyS907KN+Dm56KfkliyuCbhNsfKvDt65Eta/M6b6dz6Nbfoz+82ySq3S53Ya6wLQKbnoRZvu0J2kkUNhJr9Zxd+Dtev8FYC4mR6+wTOm1FnFoKw7TPg64YB6BlpR6R6glFR4aHCHwbnGvHJp0TvE4M1hDCyK9bIx+I5o72Tfauk/FmKUnfueG8ByyaDk3JunPo9XRlLv0bOI0pCVevQJK1D0nG/qcpDRKMB+6+/myrN12iuh8y1S96gAacQreEeX/sFit5BwBezEBMPIBtuNM/5S89D93eZuXCsOZLT7JTrKba0TJMriufqmSgdxl9xW9ZPDrUPiiZGiJV6wh6U2tfODjg/1Ceq2ZXFPYtw3v5p/0pqSD33aY9KV0r9S7HPC4rlNbs13TKCpTgr0KAymVP25HYwch5RdTiadH+MBXxUGC+ZFsyh880uGnAInA4N3w25RFmfeyIZrhXz9LuuzsaDkjtClXn3p9VLzDhY6HsBYsi3Ke07wkskHfaAwFlDa0bCNumJyDrpUX2v4o0y1SvTj+2S1eobnhj4DhqX3xXDGhYzeYXwvXSfINVfjwNRlCXkTGDW8g/px5j3mlLNFbv0590YEULtipWlOWi+ouULpA7pv7R68Rw6/4R12PBfZIINAyyU1q4q/68lOWutF1r6p4j2gjxevqPs2+Lm39fOpGNT1ZVHJ/SK4tpDKtyyJ6G7thrYDb5gJA8Cf5CtrPA6YvbxzQuPJJ1YjehVAiMF2g56x41j37IDjKcGta/4u+62YjWNA7y6FciyrRyBbjMNwTqEIQpSqzffkEfb9yUw+5CeAsNcfTVXS8pfV0caJk1iDC53QRPIwh+O7yroTqUuDKGG1Kk6fIdt5GqMEk2OY
*/