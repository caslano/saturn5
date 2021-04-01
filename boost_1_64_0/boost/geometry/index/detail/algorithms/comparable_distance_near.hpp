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
XGwX2s5iMUQSdeY+UCFDCWfV5ly4GlcBOEpriVe2l8hLUcHdmXkjI2Kg+8Oby/e2WrEeWaN8UZcP8ZgZJNUM+2FTZpbcSTWzYtlQpzPrrAKTHxLb9hrC2ZYLoPlHbxVAqC6Xf3rttuTHJP9x4lF8tmVCBro17yQ4LOtIAAyu6Oi5zg9tUcxgmKjJlN1j6YqM2qDxuGQP83MCT+rUa3OeYvoFMQuJW3vSkoUh7QtYvizXZ6NbQK7/hUA+iC7Mi3sOaLt1hTAYlcUAzNvfpMq7xOzf2tI+OpXNN8BU3Bz1l6GiC6AGkf6loOPIJUFaIkn2dNiFa/a/WIluJP3/QvNTUP40xz32kauMyAQJoUNrifkps7CDsBzWybHAB8jKUCALOOhEvhKfuVGXoLI+N64CPk8bFSpHD1uDTQA4Ks/BPBOErUPPhChZu+Tzf7AUUR4ZFgvt6AbTj/YMwYQrMtkq+nbwiKQ+Anxh283TsIPXeZWZS4gSizV3UbZtjUo5RYqnTuBiV+k0gow6IvSgLjrQAf3tQEUAy+08IdXsfOVRA91CmspzScK3XiLBgw==
*/