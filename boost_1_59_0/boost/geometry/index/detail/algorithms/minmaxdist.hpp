// Boost.Geometry Index
//
// minmaxdist used in R-tree k nearest neighbors query
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_MINMAXDIST_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_MINMAXDIST_HPP

#include <boost/geometry/algorithms/distance.hpp>
#include <boost/geometry/algorithms/comparable_distance.hpp>

#include <boost/geometry/core/static_assert.hpp>

#include <boost/geometry/index/detail/algorithms/diff_abs.hpp>
#include <boost/geometry/index/detail/algorithms/sum_for_indexable.hpp>
#include <boost/geometry/index/detail/algorithms/smallest_for_indexable.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

struct minmaxdist_tag {};

template <
    typename Point,
    typename BoxIndexable,
    size_t DimensionIndex>
struct smallest_for_indexable_dimension<Point, BoxIndexable, box_tag, minmaxdist_tag, DimensionIndex>
{
    typedef typename geometry::default_comparable_distance_result<Point, BoxIndexable>::type result_type;

    inline static result_type apply(Point const& pt, BoxIndexable const& i, result_type const& maxd)
    {
        typedef typename coordinate_type<Point>::type point_coord_t;
        typedef typename coordinate_type<BoxIndexable>::type indexable_coord_t;

        point_coord_t pt_c = geometry::get<DimensionIndex>(pt);
        indexable_coord_t ind_c_min = geometry::get<geometry::min_corner, DimensionIndex>(i);
        indexable_coord_t ind_c_max = geometry::get<geometry::max_corner, DimensionIndex>(i);

        indexable_coord_t ind_c_avg = ind_c_min + (ind_c_max - ind_c_min) / 2;
        // TODO: awulkiew - is (ind_c_min + ind_c_max) / 2 safe?

        // TODO: awulkiew - optimize! don't calculate 2x pt_c <= ind_c_avg
        // take particular case pt_c == ind_c_avg into account

        result_type closer_comp = 0;
        if ( pt_c <= ind_c_avg )
            closer_comp = detail::diff_abs(pt_c, ind_c_min); // unsigned values protection
        else
            closer_comp = ind_c_max - pt_c;
        
        result_type further_comp = 0;
        if ( ind_c_avg <= pt_c )
            further_comp = pt_c - ind_c_min;
        else
            further_comp = detail::diff_abs(pt_c, ind_c_max); // unsigned values protection

        return (maxd + closer_comp * closer_comp) - further_comp * further_comp;
    }
};

template <typename Point, typename Indexable, typename IndexableTag>
struct minmaxdist_impl
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Indexable type.",
        Point, Indexable, IndexableTag);
};

template <typename Point, typename Indexable>
struct minmaxdist_impl<Point, Indexable, point_tag>
{
    typedef typename geometry::default_comparable_distance_result<Point, Indexable>::type result_type;

    inline static result_type apply(Point const& pt, Indexable const& i)
    {
        return geometry::comparable_distance(pt, i);
    }
};

template <typename Point, typename Indexable>
struct minmaxdist_impl<Point, Indexable, box_tag>
{
    typedef typename geometry::default_comparable_distance_result<Point, Indexable>::type result_type;

    inline static result_type apply(Point const& pt, Indexable const& i)
    {
        result_type maxd = geometry::comparable_distance(pt, i);

        return smallest_for_indexable<
            Point,
            Indexable,
            box_tag,
            minmaxdist_tag,
            dimension<Indexable>::value
        >::apply(pt, i, maxd);
    }
};

/**
 * This is comparable distace.
 */
template <typename Point, typename Indexable>
typename geometry::default_comparable_distance_result<Point, Indexable>::type
minmaxdist(Point const& pt, Indexable const& i)
{
    return detail::minmaxdist_impl<
        Point,
        Indexable,
        typename tag<Indexable>::type
    >::apply(pt, i);
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_MINMAXDIST_HPP

/* minmaxdist.hpp
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
*/