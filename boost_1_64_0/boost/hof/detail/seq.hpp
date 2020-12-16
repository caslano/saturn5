/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    seq.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_DETAIL_SEQ_H
#define BOOST_HOF_GUARD_FUNCTION_DETAIL_SEQ_H

#include <cstdlib>

namespace boost { namespace hof { 

namespace detail {

template<std::size_t ...>
struct seq 
{
    typedef seq type;
};

template <class, class>
struct merge_seq;

template <size_t... Xs, size_t... Ys>
struct merge_seq<seq<Xs...>, seq<Ys...>>
: seq<Xs..., (sizeof...(Xs)+Ys)...>
{};

template<std::size_t N>
struct gens 
: merge_seq<
    typename gens<N/2>::type,
    typename gens<N - N/2>::type
> 
{};

template<> struct gens<0> : seq<> {}; 
template<> struct gens<1> : seq<0> {}; 


}
}} // namespace boost::hof

#endif

/* seq.hpp
ZWmxFkJM/4umOJjrElteC/kfv75d05VxiaEtIYcFazSHLlAsDOIC3XCFq73rtC+iNUwXqMIpPJCRaecynLoMIlkk/5WjoymE990rHAotmytMoZ333szbYrOVVuPU73kRKD+Br/hMxJcJ8nt4CbJh1R7isxMeYvmAlU/Vj0ymQyWwf10Faqk4sysYhG3RPV3hJFBxuNg7Hp+71OVBpXyzDOeetrUG9SGxl7OMJgAphFIPMPKh+VIx9BAP+i5NUlWmekLS7I1M65VJwSmb7riK5bNu5WHkhHnhE8g0a3CXivfe4zFttCssgHf31IhIvxwhP8kbM1j/A306JG8MFFmhAmJxuf2TD2TBfie0O/YGZ1sbi1qoGpWZv0btNRYd4W36tS+jfkZaMV5qHxLWzUGn263qe3T4vQLlHVBrvlr8AfNa4LQL7ogtpBNSHQxfVJ96Wuvefw6bbG51ivvfbD+HRobYEKmRMWK7rpGxXZcHnsTOCckD+RNAmaB54g77BLxh69k5ehae0rPwvdZ5mCoqYmqLjjAfxooqqTLo9FDQXD3oM3rQWyn3e944V+4vj8r94hc492G6MK1DkTS0aZTlVPNi1E5UedGRtSakAKl9A35gm4DTckIPR/SkknbSaiNCUXPFGi1rWyIrNk9mrZU0s7NOIGZsBpyA5k5tkdiaaMJ+QKnTHVFgzzfQPQ7AWqZwK+s5S082c5etus7ktUDFJ7foiCfFDc0h2iXy7hV9edFhH9X2W+U4+/exf0vbdyNZIc8Noex+8JQuR4usyVosUFzhFdj6TGQFjnyeGR50V+qhyiEtuFu07NR2LrWqDRS1hHeSl9vav3Kh8b8RpHLXc4fC+VcHH0xVeVclHc1R5oddDdGxI4j9VG6dCsHNhb7Qn/g2FzO3ZWIHfKD21D1UXfHCJbemqP0i2MlU4Uez6+rVTyMrHNQdGdIzzS2y7eF8mhtKGVc3cxZIrJMYI1fhpcyllYnRyIbUzVXGI7skiRF1KKLyc7MusTz5EneBUa1fh98onpM1uF+Vq2vZ7eQOR9j3/2Q4z9k2PuQy6clzcMKdzMMmt02O6tBjQ2HTnjwHDw/dhRAPn0M9us9a5uEL9C59eyOXRzsjq7Gll+Dgy5d0leKXAqqCFJ1fdYuENpXv8V4RqoR+f9UqwaHJJegQJiwcgDHSzLXLczXdD+oKCt64KSC7Rd7hoG73vQuUsN7hbfYpgcbz3AWW5xeeQMRlLlWXq53Z/hsPU1priVsgcTDtJPhJMJwNPMpBXEMT7D38WSr/4iPiS2mnTMZLA1s2c+ITSg3ti0o+FPaBRptph5lWutjudtJVAO2hFZYjwL3aCfVK3BD1An9crXcTd8vS3gG6bavptIkJTfRGjS0slcZ1k8AoaFrz2EB7HOUi6yBtX8fkW4WslAaHESvvj3OJnx7jsGBxEll/g82+7NzJAVJpJEZ1zjrI1Um5YvvgI6MKVT2EZkATOUlGhKRhdbwlmcGmbvivOdBJBi1wlEz0lrvStF15F9cH0qxDl2W9ABwKs3BdO9pcMp+lYsij7Vr7Yk9sbmhPbK62J5Z41j0xdLbtXD7sVaBPkBIJCgLjOMvQrtI4zuIysWYNFzebyhhHvXHqTThyyY0oM+AUj/0eXDjX/s5DvBAsROKyEmNgg27MUf7e+BNE4Mnnc4blPwmq/Ye3wsd/qzQqQHWEPpgUGJ3MTLLKGU9ifZaDTSo3OzdVLgmDKUs1RtQVtv/xuPYxf1/feZpV8X3sf7xyNsmPnfc//sZDmyO0/7GJ65QF89I23diD7ed1OujTgI5k1/SbXt//RfWb1m3TuAQtNrtIWfeF9JtYfnRdS4T8iKdevt8=
*/