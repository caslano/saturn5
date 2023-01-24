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
0AM/LmyLmYNiYeuDZZ6FzhlSI6p3MgdJTN7MbG+pDnmbgzQAH33LQ1O+UZrYTmMuFo9eZuTB6hWrWPp7cgew7l1U3t4G1uvtMa1ADgsp6s6PTYM9TJ4fQTnc3TgIxWtMyejHfykNzJY7ItnuesDIMyd3slN+qnguoFuZ8dhs+8LjZpW0p63M3i1P0N7HPRs2XBV/lliPLdPs5Vk3k/vdByxIqr6oDCXFjIcoVV37EqRIMj25WdkVTeW81NYkqI24S3jGmhL65oMO1XlcrKH0wOyop8It1fMzymSuSOnFD/npXDvA1FexJ61RJI+sLc6OcPXd8q/tP+VIiR4mT4BLM6J2nmfe58mRWYV13Vhpxkn1oo/aPfPB5xPx6d49AofUeYiSi7tPH0rAJxc/Fh7708nWF0qk0ixtycu1TkqxgpLbJlzItq6fJqoirfbyc49nehdo2W4NR5l9IobSyj5NXYubIVat1Ji/+U5gseMyBrk/7xdQjyqoc54U8bZd/FdJG3S6msr9RGMin2BjhF87AO9eAEx+ge/YSPY/Sz5Ac9MrJGI2O3+TZ/5L4aOu3zwOnxQPidOH49p7NbgCo+p2uTbVG259W4rWsYfZLAFfziF7rKpPiqslQ8HFFjx1aB/PRi+fLge2dN3DMskdsa6bu+9t8/JbyU/LhSGPOq2Ya8gyh4iSZw1sQ8I7NrdSUMxGfbLfao9DaB3ZT59m
*/