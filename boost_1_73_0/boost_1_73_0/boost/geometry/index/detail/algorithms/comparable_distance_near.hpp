// Boost.Geometry Index
//
// squared distance between point and nearest point of the box or point
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_COMPARABLE_DISTANCE_NEAR_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_COMPARABLE_DISTANCE_NEAR_HPP

#include <boost/geometry/index/detail/algorithms/sum_for_indexable.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

struct comparable_distance_near_tag {};

template <
    typename Point,
    typename PointIndexable,
    size_t N>
struct sum_for_indexable<Point, PointIndexable, point_tag, comparable_distance_near_tag, N>
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
struct sum_for_indexable_dimension<Point, BoxIndexable, box_tag, comparable_distance_near_tag, DimensionIndex>
{
    typedef typename geometry::default_comparable_distance_result<Point, BoxIndexable>::type result_type;

    inline static result_type apply(Point const& pt, BoxIndexable const& i)
    {
        typedef typename coordinate_type<Point>::type point_coord_t;
        typedef typename coordinate_type<BoxIndexable>::type indexable_coord_t;

        point_coord_t pt_c = geometry::get<DimensionIndex>(pt);
        indexable_coord_t ind_c_min = geometry::get<geometry::min_corner, DimensionIndex>(i);
        indexable_coord_t ind_c_max = geometry::get<geometry::max_corner, DimensionIndex>(i);

        result_type diff = 0;

        if ( pt_c < ind_c_min )
            diff = ind_c_min - pt_c;
        else if ( ind_c_max < pt_c )
            diff = pt_c - ind_c_max;

        return diff * diff;
    }
};

template <typename Point, typename Indexable>
typename geometry::default_comparable_distance_result<Point, Indexable>::type
comparable_distance_near(Point const& pt, Indexable const& i)
{
    return detail::sum_for_indexable<
        Point,
        Indexable,
        typename tag<Indexable>::type,
        detail::comparable_distance_near_tag,
        dimension<Indexable>::value
    >::apply(pt, i);
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_COMPARABLE_DISTANCE_NEAR_HPP

/* comparable_distance_near.hpp
Ill4qyRL55jCsigXF5dk8EkrElRyrgyYgjwzNntJDviTnEPpxWzIKXc1PoyLIW5S3JYxW2afU4rhvQkyRpDeGHM4sBGba/hQIfjz/AJVMmheI11Ayn4anK+Fa7xXmVEAWJWNT/1ntnsda6AUrImq1BAFVYX/n3zKrRDeWpJ3BqcOHcVhU9Bzm7pP1JVqlRu4JHHSF7w4+onLdEk1pGaItawUk6JNGoFSSw1NQcijPoxNA5FB3Ep2S03iHGryHUebbMP/kUDX5Wd994NsnGToJ2XDMveAllzMgZaQbotSIm5vbT8Io/stmsc5A5xXCM2i3MGvRj8Pj08wJwUsZyc8S1/Ah5V+mi8TqyLXZYmHA2edXxQYnyYFjSnGrIxcMiwjRl0BNxYzbrpq2Ytg4zGs6HYmBS80cTLt//HwP94D4tuTGWLyR/IIOZ+SG1pcBFYZTRDZJwvn4kfZGbdiw/rXALPCbwg+HcDMFzS22N0fyBv0I7zD2niZ4sQ6dVAuEq/4YUtYqNFgS3uKxTvCaEjObBOg36l6As24ALKUNhCUK3nWqeIBx/Y6s6fmK7a92RToNnkOVRFSxSuQigztYOilBe23XCp0one2O5/6WWqnLLBScX1TJg8RSArY14ecwf3N6buBlPEu/A2xfTGB
*/