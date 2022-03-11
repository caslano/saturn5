// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_INVALID_COORDINATE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_INVALID_COORDINATE_HPP

#include <cstddef>

#include <boost/type_traits/is_floating_point.hpp>

#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>
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
    struct point_has_valid_coordinates
    {
        template <typename Point>
        static inline bool apply(Point const& point)
        {
            return ! point_has_invalid_coordinate::apply(point);
        }
    };

    template <typename Geometry, typename VisitPolicy>
    static inline bool apply(Geometry const& geometry, VisitPolicy& visitor)
    {
        boost::ignore_unused(visitor);

        bool const has_valid_coordinates = detail::check_iterator_range
            <
                point_has_valid_coordinates,
                true // do not consider an empty range as problematic
            >::apply(geometry::points_begin(geometry),
                     geometry::points_end(geometry));

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
    bool HasFloatingPointCoordinates = boost::is_floating_point
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