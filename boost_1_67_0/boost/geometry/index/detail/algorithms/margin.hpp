// Boost.Geometry Index
//
// n-dimensional box's margin value (hypersurface), 2d perimeter, 3d surface, etc...
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_MARGIN_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_MARGIN_HPP

// WARNING! comparable_margin() will work only if the same Geometries are compared
// so it shouldn't be used in the case of Variants!

namespace boost { namespace geometry { namespace index { namespace detail {

template <typename Box>
struct default_margin_result
{
    typedef typename select_most_precise<
        typename coordinate_type<Box>::type,
        long double
    >::type type;
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
    BOOST_MPL_ASSERT_MSG(false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY, (Geometry, Tag));
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