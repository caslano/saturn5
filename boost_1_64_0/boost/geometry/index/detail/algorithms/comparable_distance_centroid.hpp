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
LlAyLlxQ6Mcy5jdoM/oZN+NWtO2h0vAqfZIOhMn9egYNJrOsAwYmmFvmi62vDueZxZzBx0fQZQDEY5QkKaFHnysbLNUOKb4NmJFQj8fTB+2zH6ICSKLB+6glRd/v4pX8INN9uyy/e/jYXOxva+5a8SIwPpl80BhHFrLDFFjbWwwz7x4dWvQVzijVgtCIaNy5Rd+3qajFEeuM8O6dE2ELsoTNHUSWMJCEtNHvxDasnLx1dkHhjWwaydKzN3bFx2rvyK93/1E6oJHcIla5/gOP0RHJjEAjLXvSwObV1hZsPnEdf/UrocDHMgoR/h0oi1VGlhEWSF0Dbap/3Pt31BeP3/qAdd0JN7UKldSdZRfQYqayjpCevdnLMXQjQ7VAhI+9YpI8veK071BbsfSirk4K0HpygUzb+ZKelYDDLkQFNqTa1O9GdLR9/YUuTk2IY346nykb3he30jstXkkbpbzvRRTPiZQ05Y9bb9lcmZo7bNLk9XA/Jg5Y6P+BB88ej3DjkLAnAPAEzQ9KkQrrPHXeimuY+IGSHRyf7KcFz6tU8xmLX7WWU2Sxyx0GoQ==
*/