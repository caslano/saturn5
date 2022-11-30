// Boost.Geometry Index
//
// n-dimensional box's margin value (hypersurface), 2d perimeter, 3d surface, etc...
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2020-2022.
// Modifications copyright (c) 2020-2022 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_MARGIN_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_MARGIN_HPP

#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

// WARNING! comparable_margin() will work only if the same Geometries are compared
// so it shouldn't be used in the case of Variants!

namespace boost { namespace geometry { namespace index { namespace detail {

template <typename Box>
struct default_margin_result
{
    using type = typename select_most_precise
        <
            typename coordinate_type<Box>::type,
            double
        >::type;
};

//template <typename Box,
//          std::size_t CurrentDimension,
//          std::size_t EdgeDimension = dimension<Box>::value>
//struct margin_for_each_edge
//{
//    BOOST_STATIC_ASSERT(0 < CurrentDimension);
//    BOOST_STATIC_ASSERT(0 < EdgeDimension);
//
//    static inline typename default_margin_result<Box>::type apply(Box const& b)
//    {
//        return margin_for_each_edge<Box, CurrentDimension, EdgeDimension - 1>::apply(b) *
//            ( geometry::get<max_corner, EdgeDimension - 1>(b) - geometry::get<min_corner, EdgeDimension - 1>(b) );
//    }
//};
//
//template <typename Box, std::size_t CurrentDimension>
//struct margin_for_each_edge<Box, CurrentDimension, CurrentDimension>
//{
//    BOOST_STATIC_ASSERT(0 < CurrentDimension);
//
//    static inline typename default_margin_result<Box>::type apply(Box const& b)
//    {
//        return margin_for_each_edge<Box, CurrentDimension, CurrentDimension - 1>::apply(b);
//    }
//};
//
//template <typename Box, std::size_t CurrentDimension>
//struct margin_for_each_edge<Box, CurrentDimension, 1>
//{
//    BOOST_STATIC_ASSERT(0 < CurrentDimension);
//
//    static inline typename default_margin_result<Box>::type apply(Box const& b)
//    {
//        return geometry::get<max_corner, 0>(b) - geometry::get<min_corner, 0>(b);
//    }
//};
//
//template <typename Box>
//struct margin_for_each_edge<Box, 1, 1>
//{
//    static inline typename default_margin_result<Box>::type apply(Box const& /*b*/)
//    {
//        return 1;
//    }
//};
//
//template <typename Box,
//          std::size_t CurrentDimension = dimension<Box>::value>
//struct margin_for_each_dimension
//{
//    BOOST_STATIC_ASSERT(0 < CurrentDimension);
//
//    static inline typename default_margin_result<Box>::type apply(Box const& b)
//    {
//        return margin_for_each_dimension<Box, CurrentDimension - 1>::apply(b) +
//            margin_for_each_edge<Box, CurrentDimension>::apply(b);
//    }
//};
//
//template <typename Box>
//struct margin_for_each_dimension<Box, 1>
//{
//    static inline typename default_margin_result<Box>::type apply(Box const& b)
//    {
//        return margin_for_each_edge<Box, 1>::apply(b);
//    }
//};

// TODO - test if this definition of margin is ok for Dimension > 2
// Now it's sum of edges lengths
// maybe margin_for_each_dimension should be used to get more or less hypersurface?

template <typename Box,
          std::size_t CurrentDimension = dimension<Box>::value>
struct simple_margin_for_each_dimension
{
    BOOST_STATIC_ASSERT(0 < CurrentDimension);

    static inline typename default_margin_result<Box>::type apply(Box const& b)
    {
        return simple_margin_for_each_dimension<Box, CurrentDimension - 1>::apply(b) +
            geometry::get<max_corner, CurrentDimension - 1>(b) - geometry::get<min_corner, CurrentDimension - 1>(b);
    }
};

template <typename Box>
struct simple_margin_for_each_dimension<Box, 1>
{
    static inline typename default_margin_result<Box>::type apply(Box const& b)
    {
        return geometry::get<max_corner, 0>(b) - geometry::get<min_corner, 0>(b);
    }
};

namespace dispatch {

template <typename Geometry, typename Tag>
struct comparable_margin
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry type.",
        Geometry, Tag);
};

template <typename Geometry>
struct comparable_margin<Geometry, point_tag>
{
    typedef typename default_margin_result<Geometry>::type result_type;

    static inline result_type apply(Geometry const& ) { return 0; }
};

template <typename Box>
struct comparable_margin<Box, box_tag>
{
    typedef typename default_margin_result<Box>::type result_type;

    static inline result_type apply(Box const& g)
    {
        //return detail::margin_for_each_dimension<Box>::apply(g);
        return detail::simple_margin_for_each_dimension<Box>::apply(g);
    }
};

} // namespace dispatch

template <typename Geometry>
typename default_margin_result<Geometry>::type comparable_margin(Geometry const& g)
{
    return dispatch::comparable_margin<
        Geometry,
        typename tag<Geometry>::type
    >::apply(g);
}

//template <typename Box>
//typename default_margin_result<Box>::type margin(Box const& b)
//{
//    return 2 * detail::margin_for_each_dimension<Box>::apply(b);
//}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_MARGIN_HPP

/* margin.hpp
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
*/