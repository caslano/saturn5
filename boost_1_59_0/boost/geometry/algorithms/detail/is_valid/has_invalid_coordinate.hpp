// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_INVALID_COORDINATE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_INVALID_COORDINATE_HPP

#include <cstddef>
#include <type_traits>

#include <boost/geometry/algorithms/validity_failure_type.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>

#include <boost/geometry/util/has_non_finite_coordinate.hpp>

namespace boost { namespace geometry
{
    
#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{

struct always_valid
{
    template <typename Geometry, typename VisitPolicy>
    static inline bool apply(Geometry const&, VisitPolicy& visitor)
    {
        return ! visitor.template apply<no_failure>();
    }
};

struct point_has_invalid_coordinate
{
    template <typename Point, typename VisitPolicy>
    static inline bool apply(Point const& point, VisitPolicy& visitor)
    {
        boost::ignore_unused(visitor);

        return
            geometry::has_non_finite_coordinate(point)
            ?
            (! visitor.template apply<failure_invalid_coordinate>())
            :
            (! visitor.template apply<no_failure>());
    }

    template <typename Point>
    static inline bool apply(Point const& point)
    {
        return geometry::has_non_finite_coordinate(point);
    }
};

struct indexed_has_invalid_coordinate
{
    template <typename Geometry, typename VisitPolicy>
    static inline bool apply(Geometry const& geometry, VisitPolicy& visitor)
    {
        geometry::detail::indexed_point_view<Geometry const, 0> p0(geometry);
        geometry::detail::indexed_point_view<Geometry const, 1> p1(geometry);

        return point_has_invalid_coordinate::apply(p0, visitor)
            || point_has_invalid_coordinate::apply(p1, visitor);
    }
};


struct range_has_invalid_coordinate
{
    template <typename Geometry, typename VisitPolicy>
    static inline bool apply(Geometry const& geometry, VisitPolicy& visitor)
    {
        boost::ignore_unused(visitor);

        auto const points_end = geometry::points_end(geometry);
        bool const has_valid_coordinates = std::none_of
            (
                geometry::points_begin(geometry), points_end,
                []( auto const& point ){ 
                    return point_has_invalid_coordinate::apply(point); 
                }
            );

        return has_valid_coordinates
            ?
            (! visitor.template apply<no_failure>())
            :
            (! visitor.template apply<failure_invalid_coordinate>());
    }
};


template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type,
    bool HasFloatingPointCoordinates = std::is_floating_point
        <
            typename coordinate_type<Geometry>::type
        >::value
>
struct has_invalid_coordinate
    : range_has_invalid_coordinate
{};

template <typename Geometry, typename Tag>
struct has_invalid_coordinate<Geometry, Tag, false>
    : always_valid
{};

template <typename Point>
struct has_invalid_coordinate<Point, point_tag, true>
    : point_has_invalid_coordinate
{};

template <typename Segment>
struct has_invalid_coordinate<Segment, segment_tag, true>
    : indexed_has_invalid_coordinate
{};

template <typename Box>
struct has_invalid_coordinate<Box, box_tag, true>
    : indexed_has_invalid_coordinate
{};


}} // namespace detail::is_valid
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_INVALID_COORDINATE_HPP

/* has_invalid_coordinate.hpp
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
*/