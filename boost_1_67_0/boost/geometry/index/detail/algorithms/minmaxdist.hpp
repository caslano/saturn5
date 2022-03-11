// Boost.Geometry Index
//
// minmaxdist used in R-tree k nearest neighbors query
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_MINMAXDIST_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_MINMAXDIST_HPP

#include <boost/geometry/algorithms/distance.hpp>
#include <boost/geometry/algorithms/comparable_distance.hpp>

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
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_INDEXABLE_TAG_TYPE,
        (minmaxdist_impl));
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