// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_APPEND_HPP
#define BOOST_GEOMETRY_ALGORITHMS_APPEND_HPP


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/num_interior_rings.hpp>
#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>
#include <boost/geometry/geometries/adapted/boost_variant.hpp> // for backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace append
{

struct append_no_action
{
    template <typename Geometry, typename Point>
    static inline void apply(Geometry& , Point const& ,
                             signed_size_type = -1, signed_size_type = 0)
    {
    }
};

struct to_range_point
{
    template <typename Geometry, typename Point>
    static inline void apply(Geometry& geometry, Point const& point,
                             signed_size_type = -1, signed_size_type = 0)
    {
        typename geometry::point_type<Geometry>::type copy;
        geometry::detail::conversion::convert_point_to_point(point, copy);
        traits::push_back<Geometry>::apply(geometry, copy);
    }
};


struct to_range_range
{
    template <typename Geometry, typename Range>
    static inline void apply(Geometry& geometry, Range const& range,
                             signed_size_type = -1, signed_size_type = 0)
    {
        using point_type = typename boost::range_value<Range>::type;

        auto const end = boost::end(range);
        for (auto it = boost::begin(range); it != end; ++it)
        {
            to_range_point::apply<Geometry, point_type>(geometry, *it);
        }
    }
};


struct to_polygon_point
{
    template <typename Polygon, typename Point>
    static inline void apply(Polygon& polygon, Point const& point,
                             signed_size_type ring_index, signed_size_type = 0)
    {
        using ring_type = typename ring_type<Polygon>::type;
        using exterior_ring_type = typename ring_return_type<Polygon>::type;
        using interior_ring_range_type = typename interior_return_type<Polygon>::type;

        if (ring_index == -1)
        {
            exterior_ring_type ext_ring = exterior_ring(polygon);
            to_range_point::apply<ring_type, Point>(ext_ring, point);
        }
        else if (ring_index < signed_size_type(num_interior_rings(polygon)))
        {
            interior_ring_range_type int_rings = interior_rings(polygon);
            to_range_point::apply<ring_type, Point>(range::at(int_rings, ring_index), point);
        }
    }
};


struct to_polygon_range
{
    template <typename Polygon, typename Range>
    static inline void apply(Polygon& polygon, Range const& range,
                             signed_size_type ring_index, signed_size_type = 0)
    {
        using ring_type = typename ring_type<Polygon>::type;
        using exterior_ring_type = typename ring_return_type<Polygon>::type;
        using interior_ring_range_type = typename interior_return_type<Polygon>::type;

        if (ring_index == -1)
        {
            exterior_ring_type ext_ring = exterior_ring(polygon);
            to_range_range::apply<ring_type, Range>(ext_ring, range);
        }
        else if (ring_index < signed_size_type(num_interior_rings(polygon)))
        {
            interior_ring_range_type int_rings = interior_rings(polygon);
            to_range_range::apply<ring_type, Range>(range::at(int_rings, ring_index), range);
        }
    }
};


template <typename Policy>
struct to_multigeometry
{
    template <typename MultiGeometry, typename RangeOrPoint>
    static inline void apply(MultiGeometry& multigeometry,
                             RangeOrPoint const& range_or_point,
                             signed_size_type ring_index, signed_size_type multi_index)
    {
        Policy::template apply
            <
                typename boost::range_value<MultiGeometry>::type,
                RangeOrPoint
            >(range::at(multigeometry, multi_index), range_or_point, ring_index);
    }
};


}} // namespace detail::append
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry,
    typename RangeOrPoint,
    typename Tag = typename geometry::tag<Geometry>::type,
    typename OtherTag = typename geometry::tag<RangeOrPoint>::type
>
struct append
    : detail::append::append_no_action
{};

template <typename Geometry, typename Point>
struct append<Geometry, Point, linestring_tag, point_tag>
    : detail::append::to_range_point
{};

template <typename Geometry, typename Point>
struct append<Geometry, Point, ring_tag, point_tag>
    : detail::append::to_range_point
{};

template <typename Polygon, typename Point>
struct append<Polygon, Point, polygon_tag, point_tag>
        : detail::append::to_polygon_point
{};

template <typename Geometry, typename Range, typename RangeTag>
struct append<Geometry, Range, linestring_tag, RangeTag>
    : detail::append::to_range_range
{};

template <typename Geometry, typename Range, typename RangeTag>
struct append<Geometry, Range, ring_tag, RangeTag>
    : detail::append::to_range_range
{};

template <typename Polygon, typename Range, typename RangeTag>
struct append<Polygon, Range, polygon_tag, RangeTag>
        : detail::append::to_polygon_range
{};


template <typename Geometry, typename Point>
struct append<Geometry, Point, multi_point_tag, point_tag>
    : detail::append::to_range_point
{};

template <typename Geometry, typename Range, typename RangeTag>
struct append<Geometry, Range, multi_point_tag, RangeTag>
    : detail::append::to_range_range
{};

template <typename MultiGeometry, typename Point>
struct append<MultiGeometry, Point, multi_linestring_tag, point_tag>
    : detail::append::to_multigeometry<detail::append::to_range_point>
{};

template <typename MultiGeometry, typename Range, typename RangeTag>
struct append<MultiGeometry, Range, multi_linestring_tag, RangeTag>
    : detail::append::to_multigeometry<detail::append::to_range_range>
{};

template <typename MultiGeometry, typename Point>
struct append<MultiGeometry, Point, multi_polygon_tag, point_tag>
    : detail::append::to_multigeometry<detail::append::to_polygon_point>
{};

template <typename MultiGeometry, typename Range, typename RangeTag>
struct append<MultiGeometry, Range, multi_polygon_tag, RangeTag>
    : detail::append::to_multigeometry<detail::append::to_polygon_range>
{};


template <typename Geometry, typename RangeOrPoint, typename OtherTag>
struct append<Geometry, RangeOrPoint, dynamic_geometry_tag, OtherTag>
{
    static inline void apply(Geometry& geometry,
                             RangeOrPoint const& range_or_point,
                             signed_size_type ring_index, signed_size_type multi_index)
    {
        traits::visit<Geometry>::apply([&](auto & g)
        {
            append
                <
                    std::remove_reference_t<decltype(g)>, RangeOrPoint
                >::apply(g, range_or_point, ring_index, multi_index);
        }, geometry);
    }
};

// TODO: It's unclear how append should work for GeometryCollection because
//   it can hold multiple different geometries.

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief Appends one or more points to a linestring, ring, polygon, multi-geometry
\ingroup append
\tparam Geometry \tparam_geometry
\tparam RangeOrPoint Either a range or a point, fullfilling Boost.Range concept or Boost.Geometry Point Concept
\param geometry \param_geometry
\param range_or_point The point or range to add
\param ring_index The index of the ring in case of a polygon:
    exterior ring (-1, the default) or  interior ring index
\param multi_index The index of the geometry to which the points are appended

\qbk{[include reference/algorithms/append.qbk]}
}
 */
template <typename Geometry, typename RangeOrPoint>
inline void append(Geometry& geometry, RangeOrPoint const& range_or_point,
                   signed_size_type ring_index = -1, signed_size_type multi_index = 0)
{
    concepts::check<Geometry>();

    dispatch::append
        <
            Geometry, RangeOrPoint
        >::apply(geometry, range_or_point, ring_index, multi_index);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_APPEND_HPP

/* append.hpp
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
*/