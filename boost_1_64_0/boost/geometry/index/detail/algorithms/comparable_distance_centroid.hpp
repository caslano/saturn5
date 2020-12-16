// Boost.Geometry Index
//
// squared distance between point and centroid of the box or point
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_COMPARABLE_DISTANCE_CENTROID_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_COMPARABLE_DISTANCE_CENTROID_HPP

#include <boost/geometry/index/detail/algorithms/sum_for_indexable.hpp>
#include <boost/geometry/index/detail/algorithms/diff_abs.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

struct comparable_distance_centroid_tag {};

template <
    typename Point,
    typename PointIndexable,
    size_t N>
struct sum_for_indexable<Point, PointIndexable, point_tag, comparable_distance_centroid_tag, N>
{
    typedef typename geometry::default_comparable_distance_result<Point, PointIndexable>::type result_type;

    inline static result_type apply(Point const& pt, PointIndexable const& i)
    {
        return geometry::comparable_distance(pt, i);
    }
};

template <
    typename Point,
    typename BoxIndexable,
    size_t DimensionIndex>
struct sum_for_indexable_dimension<Point, BoxIndexable, box_tag, comparable_distance_centroid_tag, DimensionIndex>
{
    typedef typename geometry::default_comparable_distance_result<Point, BoxIndexable>::type result_type;

    inline static result_type apply(Point const& pt, BoxIndexable const& i)
    {
        typedef typename coordinate_type<Point>::type point_coord_t;
        typedef typename coordinate_type<BoxIndexable>::type indexable_coord_t;

        point_coord_t pt_c = geometry::get<DimensionIndex>(pt);
        indexable_coord_t ind_c_min = geometry::get<geometry::min_corner, DimensionIndex>(i);
        indexable_coord_t ind_c_max = geometry::get<geometry::max_corner, DimensionIndex>(i);
        
        indexable_coord_t ind_c_avg = ind_c_min + (ind_c_max - ind_c_min) / 2;
        // TODO: awulkiew - is (ind_c_min + ind_c_max) / 2 safe?

        result_type diff = detail::diff_abs(ind_c_avg, pt_c);

        return diff * diff;
    }
};

template <typename Point, typename Indexable>
typename geometry::default_comparable_distance_result<Point, Indexable>::type
comparable_distance_centroid(Point const& pt, Indexable const& i)
{
    return detail::sum_for_indexable<
        Point,
        Indexable,
        typename tag<Indexable>::type,
        detail::comparable_distance_centroid_tag,
        dimension<Indexable>::value
    >::apply(pt, i);
}

}}}} // namespace boost::geometry::index::detail

#endif // #define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_COMPARABLE_DISTANCE_CENTROID_HPP


/* comparable_distance_centroid.hpp
Ifax0xJj7GTPv9L8orTMnFr0R/jVY6VlKg8zcwLlAvZ6rNSC8tsx+PSOlXgmZjzTHCu96zxWOjTEue+KfM+e9uIyY1bese/CfdV3Z+Vcyw3sLf3WiZPot6zvxip8S1oOptjlYb7RDmxpkbkKVzkoftA591VW+8ZVxhupyv/pkpPquXr839jl/Xf7UFs5qr4g3THtej2Z+/y1rTzFvaQ/vUp5/lyL8qx5f6F6hmVdy4phEoCka5A5f21NV1kRrzSL3MtT3Cc57oXZ8Z51vdauWnwXdUiL014O3bdFyyFhx2WO5qj6xgCrpKMkS417czMZyhv9dU4uR4u6p0v8x+szjBseMvR/95zP/8+hYvT3B2uQMea6GuX+Pc8s4voMypRPhKt8G+fplpP524bTvxBOeFCrsLPCurKBJiTM9v1N6n4zFeZg0RNj9GZdKlO5oPowvV8tUtm3VDJP1i3o9Vc/NT25ucwEyzc1S9otsn/FSF9AE2RsOApVaLxj/V2Xy7SR06aNnTxJrXPMzygp5X1EzqwgPfubG+mX4YguF9N/C52fE5S+tehZ9aL09Xx7HOup98oyClrsTf8x+hvmKKXvLnrtX8WhnUf86/UhMh+n3PTGj1fKwgw3vsY5uBipy6SP/NPp0+2VOGOu4qzXIxIPzCQeVdYjJo2Sezwkn9ugvqdsKvz5nLFwIc3ffj+CSss9yl2E5K/pL1bPLRbi/po67L+Sc+4tsuaoxDFJZE2s3P+xPyCOmZm90nIKS0pd7nEQt9EB60MN15Z7QMRNkn+P3UncA2JdG6qfYekPOUNP/XpLerqjNjbjv/d1emxnozikSdz3dj0XRexdz0UR+xrPRamSxjqdiZKgnsH3lCrrIteNsfeLBfhNCcgDZgRLfJvMHdOPW+t3zp216B8c6pnuqweO9Tl8UOJ0N+rXxKlIx8n9jJaVKm4M4/X7jelvKG0rXH8PQn5qtbkOZ/KsVPEl/CrtN2Wcz/FaudthJTTab+o/dJwlBy15qPf6Zit3hd6O/F+B4ux4yV8Jg9bWm7iHSdwbUlDTZR1uI/5+BobBGZi9gTqGvrgWfUMTSZeUg6orV33gqyuPEp6hv130Mc19+h3a3tqePOPtZxZcjZuUD615oGcVHduTuHc/m0bZ1+ZsGiNtDfxpc5tP1PFfP942p6PqXbqOv8whmq+IEv+V1vjjvnbzNBI/s05Z6lPyBOf+oCggLoUFBXy1cO4P1n5o6Q/wZ+0PCk6hPzDza/9En8MfZcz2Kaoz5V0ZGMeiiwImIwLjWqr74b3K/QHPI4Qt8ZUwYgLyd5H0D6ZdvF5b85LSH/Jsd9jLneqhPUj4xn7nvuTrCOIdQTyDy29mnNY2tF6j8IY9w8MjA+Ypqp3faArHfeSbC+noaWw5yyaScJuiGCOzF7qu7a9U6cfoOkGaLWd85ar29+WH1vb5M3ppn5bymTfJthdT1eejH+nysZ2x5FCfcV+7fZhO9bmH2ddO8TmMDSbvhZcaleawPy50sZa6fIHUjzjlZnBQH/4fhZqNyketRV2P2oJ6C/Uu6l+ozl6kPWoWqhh1F+oh1MeoL1GNg0I93VGSPolDnL53Jf0TQ/+ErT9PUPLHdP9v5q4EPKrqCs9kh0zIZCULS1hkB4OAgIKGVTYlAiJYNQkkkAhJhiRsijIgVayo1NKKVVtUREBUVFS0KrhjiwoWN0SNO1WsVBFRUfu/88478+68+5JJaPsVvpt/7r3n3Hfuvp97UdR+b74nNyrZczpMKvnBnXgzvS08U910NDF/BoU3B/YMso+JqkP9LIMqvucRbir5KeE5dDTxGw6KPOSm8tl1NUn5nUQ8lcjVydInon1Bv6E=
*/