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
Nv5WlykiY5e9vWEMcOMw/AURwsE8DB/V8rZhrepciS7EWrKts+Jr54mkSgIxrBsBJ1qKPUWqEdA2JWFZ6UKZnNve8QlIRDnOU6fakSz970+Go4P9V+9ODuJjmlUUgerK1VTGlcm0kFnY7KsOjP0NNdtAm4ASnoqdVnnWTK8ebEakbyBhDlDZ1KgBKldgx++VMg4MEml1OZoAIp+Xt64txgriCwGDaJy4ddCza8+lfuK2wKPj8wHt0+rmrtaNNF8x7xh+WSKvps1+K/LKk1MfHpJV4sPuT8P3bJioWDCW1jfpVbaYjWZpPv/12UdlyzqbbH8MM4GSKdaQiaaaeqNRiDtkfF15dENBUFgjb90eACK9PA04J6k0O5vn1ylwJjcpe9iljE2fcicSvBom0cO+QjfX1OuGMfshLA09uj5kydv3J6es94vYtopNn2mFnWlKH+F1qJDCGV55RqmkqS3QCVeU29Tr4dEp7DGmHi5uqc4UXgfsjTR/dRm6pwCQVDQj0pnAd5RDqpBCVSWgSawoCXjScaNoF0EG6BYYUCoY59gyABZg4Kls/AJZpqPedp8LvzMtB3H3SetBrJDDAPYraC2FqZZWLWeWJfjAEVgxXuDKCvE6XE7xnTPZgybBd+/MJaSilvGNdXwDM3Gs
*/