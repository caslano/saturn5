// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_IMPLEMENTATION_HPP


#include <cstddef>
#include <type_traits>
#include <vector>

#include <boost/range/size.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/length.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/equals/collect_vectors.hpp>
#include <boost/geometry/algorithms/detail/equals/interface.hpp>
#include <boost/geometry/algorithms/detail/relate/relate_impl.hpp>
#include <boost/geometry/algorithms/relate.hpp>

#include <boost/geometry/strategies/relate/cartesian.hpp>
#include <boost/geometry/strategies/relate/geographic.hpp>
#include <boost/geometry/strategies/relate/spherical.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace equals
{


template
<
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct point_point
{
    template <typename Point1, typename Point2, typename Strategy>
    static inline bool apply(Point1 const& point1, Point2 const& point2,
                             Strategy const& strategy)
    {
        typedef decltype(strategy.relate(point1, point2)) strategy_type;
        return strategy_type::apply(point1, point2);
    }
};


template
<
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct box_box
{
    template <typename Box1, typename Box2, typename Strategy>
    static inline bool apply(Box1 const& box1, Box2 const& box2, Strategy const& strategy)
    {
        if (!geometry::math::equals(get<min_corner, Dimension>(box1), get<min_corner, Dimension>(box2))
            || !geometry::math::equals(get<max_corner, Dimension>(box1), get<max_corner, Dimension>(box2)))
        {
            return false;
        }
        return box_box<Dimension + 1, DimensionCount>::apply(box1, box2, strategy);
    }
};

template <std::size_t DimensionCount>
struct box_box<DimensionCount, DimensionCount>
{
    template <typename Box1, typename Box2, typename Strategy>
    static inline bool apply(Box1 const& , Box2 const& , Strategy const& )
    {
        return true;
    }
};


struct segment_segment
{
    template <typename Segment1, typename Segment2, typename Strategy>
    static inline bool apply(Segment1 const& segment1, Segment2 const& segment2,
                             Strategy const& strategy)
    {
        return equals::equals_point_point(
                    indexed_point_view<Segment1 const, 0>(segment1),
                    indexed_point_view<Segment2 const, 0>(segment2),
                    strategy)
                ? equals::equals_point_point(
                    indexed_point_view<Segment1 const, 1>(segment1),
                    indexed_point_view<Segment2 const, 1>(segment2),
                    strategy)
                : ( equals::equals_point_point(
                        indexed_point_view<Segment1 const, 0>(segment1),
                        indexed_point_view<Segment2 const, 1>(segment2),
                        strategy)
                 && equals::equals_point_point(
                        indexed_point_view<Segment1 const, 1>(segment1),
                        indexed_point_view<Segment2 const, 0>(segment2),
                        strategy)
                  );
    }
};


struct area_check
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return geometry::math::equals(geometry::area(geometry1, strategy),
                                      geometry::area(geometry2, strategy));
    }
};


/*
struct length_check
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return geometry::math::equals(geometry::length(geometry1, strategy),
                                      geometry::length(geometry2, strategy));
    }
};
*/


// Small helper structure do decide to use collect_vectors, or not
template <typename Strategy, typename CsTag>
struct use_collect_vectors
{
    static constexpr bool value = false;
};

template <typename Strategy>
struct use_collect_vectors<Strategy, cartesian_tag>
{
    static constexpr bool value = true;

    template <typename T, typename Point>
    using type = collected_vector_cartesian<T>;
};

template <typename CV>
struct use_collect_vectors<strategy::side::spherical_side_formula<CV>, spherical_tag>
{
    static constexpr bool value = true;

    template <typename T, typename Point>
    using type = collected_vector_spherical<T, Point>;
};


template <typename TrivialCheck>
struct equals_by_collection
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        if (! TrivialCheck::apply(geometry1, geometry2, strategy))
        {
            return false;
        }

        using calculation_type = typename geometry::select_most_precise
            <
                typename select_coordinate_type
                    <
                        Geometry1, Geometry2
                    >::type,
                double
            >::type;

        using collected_vector_type = typename use_collect_vectors
            <
                decltype(std::declval<Strategy>().side()),
                typename Strategy::cs_tag
            >::template type
                <
                    calculation_type,
                    typename geometry::point_type<Geometry1>::type
                >;

        std::vector<collected_vector_type> c1, c2;

        geometry::collect_vectors(c1, geometry1);
        geometry::collect_vectors(c2, geometry2);

        if (boost::size(c1) != boost::size(c2))
        {
            return false;
        }

        std::sort(c1.begin(), c1.end());
        std::sort(c2.begin(), c2.end());

        // Check if these vectors are equal.
        return std::equal(c1.begin(), c1.end(), c2.begin());
    }
};

template<typename Geometry1, typename Geometry2>
struct equals_by_relate
    : detail::relate::relate_impl
        <
            detail::de9im::static_mask_equals_type,
            Geometry1,
            Geometry2
        >
{};

// Use either collect_vectors or relate
// NOTE: the result could be conceptually different for invalid
// geometries in different coordinate systems because collect_vectors
// and relate treat invalid geometries differently.
template<typename TrivialCheck>
struct equals_by_collection_or_relate
{
    template <typename Strategy>
    using use_vectors = use_collect_vectors
        <
            decltype(std::declval<Strategy>().side()),
            typename Strategy::cs_tag
        >;

    template
    <
        typename Geometry1, typename Geometry2, typename Strategy,
        std::enable_if_t<use_vectors<Strategy>::value, int> = 0
    >
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return equals_by_collection<TrivialCheck>::apply(geometry1, geometry2, strategy);
    }

    template
    <
        typename Geometry1, typename Geometry2, typename Strategy,
        std::enable_if_t<! use_vectors<Strategy>::value, int> = 0
    >
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return equals_by_relate<Geometry1, Geometry2>::apply(geometry1, geometry2, strategy);
    }
};

struct equals_always_false
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& , Geometry2 const& , Strategy const& )
    {
        return false;
    }
};


}} // namespace detail::equals
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename P1, typename P2, std::size_t DimensionCount, bool Reverse>
struct equals<P1, P2, point_tag, point_tag, pointlike_tag, pointlike_tag, DimensionCount, Reverse>
    : detail::equals::point_point<0, DimensionCount>
{};

template <typename MultiPoint1, typename MultiPoint2, std::size_t DimensionCount, bool Reverse>
struct equals<MultiPoint1, MultiPoint2, multi_point_tag, multi_point_tag, pointlike_tag, pointlike_tag, DimensionCount, Reverse>
    : detail::equals::equals_by_relate<MultiPoint1, MultiPoint2>
{};

template <typename MultiPoint, typename Point, std::size_t DimensionCount, bool Reverse>
struct equals<Point, MultiPoint, point_tag, multi_point_tag, pointlike_tag, pointlike_tag, DimensionCount, Reverse>
    : detail::equals::equals_by_relate<Point, MultiPoint>
{};

template <typename Box1, typename Box2, std::size_t DimensionCount, bool Reverse>
struct equals<Box1, Box2, box_tag, box_tag, areal_tag, areal_tag, DimensionCount, Reverse>
    : detail::equals::box_box<0, DimensionCount>
{};


template <typename Ring1, typename Ring2, bool Reverse>
struct equals<Ring1, Ring2, ring_tag, ring_tag, areal_tag, areal_tag, 2, Reverse>
    : detail::equals::equals_by_collection_or_relate<detail::equals::area_check>
{};


template <typename Polygon1, typename Polygon2, bool Reverse>
struct equals<Polygon1, Polygon2, polygon_tag, polygon_tag, areal_tag, areal_tag, 2, Reverse>
    : detail::equals::equals_by_collection_or_relate<detail::equals::area_check>
{};


template <typename Polygon, typename Ring, bool Reverse>
struct equals<Polygon, Ring, polygon_tag, ring_tag, areal_tag, areal_tag, 2, Reverse>
    : detail::equals::equals_by_collection_or_relate<detail::equals::area_check>
{};


template <typename Ring, typename Box, bool Reverse>
struct equals<Ring, Box, ring_tag, box_tag, areal_tag, areal_tag, 2, Reverse>
    : detail::equals::equals_by_collection<detail::equals::area_check>
{};


template <typename Polygon, typename Box, bool Reverse>
struct equals<Polygon, Box, polygon_tag, box_tag, areal_tag, areal_tag, 2, Reverse>
    : detail::equals::equals_by_collection<detail::equals::area_check>
{};

template <typename Segment1, typename Segment2, std::size_t DimensionCount, bool Reverse>
struct equals<Segment1, Segment2, segment_tag, segment_tag, linear_tag, linear_tag, DimensionCount, Reverse>
    : detail::equals::segment_segment
{};

template <typename LineString1, typename LineString2, bool Reverse>
struct equals<LineString1, LineString2, linestring_tag, linestring_tag, linear_tag, linear_tag, 2, Reverse>
    : detail::equals::equals_by_relate<LineString1, LineString2>
{};

template <typename LineString, typename MultiLineString, bool Reverse>
struct equals<LineString, MultiLineString, linestring_tag, multi_linestring_tag, linear_tag, linear_tag, 2, Reverse>
    : detail::equals::equals_by_relate<LineString, MultiLineString>
{};

template <typename MultiLineString1, typename MultiLineString2, bool Reverse>
struct equals<MultiLineString1, MultiLineString2, multi_linestring_tag, multi_linestring_tag, linear_tag, linear_tag, 2, Reverse>
    : detail::equals::equals_by_relate<MultiLineString1, MultiLineString2>
{};

template <typename LineString, typename Segment, bool Reverse>
struct equals<LineString, Segment, linestring_tag, segment_tag, linear_tag, linear_tag, 2, Reverse>
    : detail::equals::equals_by_relate<LineString, Segment>
{};

template <typename MultiLineString, typename Segment, bool Reverse>
struct equals<MultiLineString, Segment, multi_linestring_tag, segment_tag, linear_tag, linear_tag, 2, Reverse>
    : detail::equals::equals_by_relate<MultiLineString, Segment>
{};


template <typename MultiPolygon1, typename MultiPolygon2, bool Reverse>
struct equals
    <
        MultiPolygon1, MultiPolygon2,
        multi_polygon_tag, multi_polygon_tag,
        areal_tag, areal_tag, 
        2,
        Reverse
    >
    : detail::equals::equals_by_collection_or_relate<detail::equals::area_check>
{};


template <typename Polygon, typename MultiPolygon, bool Reverse>
struct equals
    <
        Polygon, MultiPolygon,
        polygon_tag, multi_polygon_tag,
        areal_tag, areal_tag, 
        2,
        Reverse
    >
    : detail::equals::equals_by_collection_or_relate<detail::equals::area_check>
{};

template <typename MultiPolygon, typename Ring, bool Reverse>
struct equals
    <
        MultiPolygon, Ring,
        multi_polygon_tag, ring_tag,
        areal_tag, areal_tag, 
        2,
        Reverse
    >
    : detail::equals::equals_by_collection_or_relate<detail::equals::area_check>
{};


// NOTE: degenerated linear geometries, e.g. segment or linestring containing
//   2 equal points, are considered to be invalid. Though theoretically
//   degenerated segments and linestrings could be treated as points and
//   multi-linestrings as multi-points.
//   This reasoning could also be applied to boxes.

template <typename Geometry1, typename Geometry2, typename Tag1, typename Tag2, std::size_t DimensionCount>
struct equals<Geometry1, Geometry2, Tag1, Tag2, pointlike_tag, linear_tag, DimensionCount, false>
    : detail::equals::equals_always_false
{};

template <typename Geometry1, typename Geometry2, typename Tag1, typename Tag2, std::size_t DimensionCount>
struct equals<Geometry1, Geometry2, Tag1, Tag2, linear_tag, pointlike_tag, DimensionCount, false>
    : detail::equals::equals_always_false
{};

template <typename Geometry1, typename Geometry2, typename Tag1, typename Tag2, std::size_t DimensionCount>
struct equals<Geometry1, Geometry2, Tag1, Tag2, pointlike_tag, areal_tag, DimensionCount, false>
    : detail::equals::equals_always_false
{};

template <typename Geometry1, typename Geometry2, typename Tag1, typename Tag2, std::size_t DimensionCount>
struct equals<Geometry1, Geometry2, Tag1, Tag2, areal_tag, pointlike_tag, DimensionCount, false>
    : detail::equals::equals_always_false
{};

template <typename Geometry1, typename Geometry2, typename Tag1, typename Tag2, std::size_t DimensionCount>
struct equals<Geometry1, Geometry2, Tag1, Tag2, linear_tag, areal_tag, DimensionCount, false>
    : detail::equals::equals_always_false
{};

template <typename Geometry1, typename Geometry2, typename Tag1, typename Tag2, std::size_t DimensionCount>
struct equals<Geometry1, Geometry2, Tag1, Tag2, areal_tag, linear_tag, DimensionCount, false>
    : detail::equals::equals_always_false
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_IMPLEMENTATION_HPP


/* implementation.hpp
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
*/