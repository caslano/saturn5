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
PnY4D/S+K24b42mCvjlpFpHeIIhCp2hnYaxwnTXyqHonLIwOYidNmyOClh7KBbuvjo5Ph3ujV7/QTrzaff2TBZWWz6i23QxWaT1EKTQpoEutZOnBeqCy9373IFaByAQe6MTRfP8dHMbxcPet5WA7QyddOIYrrkLI86GVZH8nW0sHcYiyfISloAKbClbPpta00VR0yy4x7iegmu78DxAsP6R57cLETLDsYjYtUwDUNTILJHGg7WI6IpCnlDZ36KC5sq8bHaN91+ohgs4kzsay4iSodetJNPq5x0mgnvX+ZzH5yrPwa/u60e9/FogWYohmH6Fgb+/gMhPTPPxhLR6Sa5xvhLW0UVNHG0/s5Yv4zPvxIEGoY/S9D6Vk8hGFSS3tKhq3s6v1zPm8Rcz+6cYuUalqZvf5bZiix+Vnus5IOoheNgldkOzKEDwX7EFZVIk55BvnXeC7sefauLPZx98AW4Y/X40727q7JyZdc2Zr3+XwJ7rZjUNFAI4PdQkiXhsNN/v4myDepZt3dzTc1t09kfKaM/t9jrUFKf72WwMpGmS9FuZdis+byPL/TMzc8NrzNwXjUZ5y0R2KJHS+BByowqbaquxKKYCtuKKMZXmdUrPISHnEODoMGULVHVpNtD9lr7GkQYvhBKa6f95o
*/