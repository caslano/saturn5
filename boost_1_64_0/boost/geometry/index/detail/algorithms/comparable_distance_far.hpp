// Boost.Geometry Index
//
// squared distance between point and furthest point of the box or point
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_COMPARABLE_DISTANCE_FAR_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_COMPARABLE_DISTANCE_FAR_HPP

#include <boost/geometry/index/detail/algorithms/diff_abs.hpp>
#include <boost/geometry/index/detail/algorithms/sum_for_indexable.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

// minmaxdist component

struct comparable_distance_far_tag {};

template <
    typename Point,
    typename BoxIndexable,
    size_t DimensionIndex>
struct sum_for_indexable_dimension<Point, BoxIndexable, box_tag, comparable_distance_far_tag, DimensionIndex>
{
    typedef typename geometry::default_comparable_distance_result<Point, BoxIndexable>::type result_type;

    inline static result_type apply(Point const& pt, BoxIndexable const& i)
    {
        typedef typename coordinate_type<Point>::type point_coord_t;
        typedef typename coordinate_type<BoxIndexable>::type indexable_coord_t;

        point_coord_t pt_c = geometry::get<DimensionIndex>(pt);
        indexable_coord_t ind_c_min = geometry::get<geometry::min_corner, DimensionIndex>(i);
        indexable_coord_t ind_c_max = geometry::get<geometry::max_corner, DimensionIndex>(i);

        result_type further_diff = 0;

        if ( (ind_c_min + ind_c_max) / 2 <= pt_c )
            further_diff = pt_c - ind_c_min;
        else
            further_diff = detail::diff_abs(pt_c, ind_c_max); // unsigned values protection

        return further_diff * further_diff;
    }
};

template <typename Point, typename Indexable>
typename geometry::default_comparable_distance_result<Point, Indexable>::type
comparable_distance_far(Point const& pt, Indexable const& i)
{
    return detail::sum_for_indexable<
        Point,
        Indexable,
        typename tag<Indexable>::type,
        detail::comparable_distance_far_tag,
        dimension<Indexable>::value
    >::apply(pt, i);
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_COMPARABLE_DISTANCE_FAR_HPP

/* comparable_distance_far.hpp
6TkuZcSNWXhZaiK5Udn7HHpLYGqHaS/GCQy2IYv1BY7J6KvVEt1ryA/F8zGEwKNOmKwgVOO4ObNaP80MkhvRH9wG4UAymUXJaoePZSrm4jyjSHYMqRqs2J1jd8/WoWJy5kqzNfF9OfmYvq0ka4aJuKNk99XAOjxdgKI7T1RC0ZiyNQhKkzj6EJspulEk3cOs9sdRbXwoCohy2mS54Os88D2LH7JOrsbAiMEPwi7tRdJgmaUxJgvH3MisbS09kBLXFDCIBQvUHgWXlkgJUSMFpCytcMNHs4JCtfrJSmqrFgjiFyBu4a/FLZzOOqqkmlp4Sy3sAqn7ehuZ0HWZlMPAOhXek1OVtQEmDdXmQ9PSZ0gvLc+2ga08nfi0kDhRq2hS5zmalzFK1zjLpt6ZAP2nsv0VapBhziUezEA792xhemkzVkRbGit+wxCVEVzDc97qW0mivQkq8WBSw/pDEwxx/pnxEr6/M4iJ+ftcf6/GdHGdq372CTX8pPBn4RhNLv3l8hVwlWP0K283L4ZXZkSWHnDHMXhqPn3ruFYH9LcuFBnUcFpwBbSOKxec/A==
*/