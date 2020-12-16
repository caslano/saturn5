// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014, 2015, 2016, 2017, 2018, 2019.
// Modifications copyright (c) 2014-2019 Oracle and/or its affiliates.

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
#include <vector>

#include <boost/range.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/equals/point_point.hpp>

// For trivial checks
#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/length.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

#include <boost/geometry/algorithms/detail/equals/collect_vectors.hpp>
#include <boost/geometry/algorithms/detail/equals/interface.hpp>
#include <boost/geometry/algorithms/detail/relate/relate_impl.hpp>
#include <boost/geometry/algorithms/relate.hpp>

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
    static inline bool apply(Point1 const& point1, Point2 const& point2, Strategy const& )
    {
        return Strategy::apply(point1, point2);
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
        typename Strategy::point_in_point_strategy_type const&
            pt_pt_strategy = strategy.get_point_in_point_strategy();

        return equals::equals_point_point(
                    indexed_point_view<Segment1 const, 0>(segment1),
                    indexed_point_view<Segment2 const, 0>(segment2),
                    pt_pt_strategy)
                ? equals::equals_point_point(
                    indexed_point_view<Segment1 const, 1>(segment1),
                    indexed_point_view<Segment2 const, 1>(segment2),
                    pt_pt_strategy)
                : ( equals::equals_point_point(
                        indexed_point_view<Segment1 const, 0>(segment1),
                        indexed_point_view<Segment2 const, 1>(segment2),
                        pt_pt_strategy)
                 && equals::equals_point_point(
                        indexed_point_view<Segment1 const, 1>(segment1),
                        indexed_point_view<Segment2 const, 0>(segment2),
                        pt_pt_strategy)
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
        return geometry::math::equals(
            geometry::area(geometry1,
                           strategy.template get_area_strategy<Geometry1>()),
            geometry::area(geometry2,
                           strategy.template get_area_strategy<Geometry2>()));
    }
};


struct length_check
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return geometry::math::equals(
            geometry::length(geometry1,
                             strategy.template get_distance_strategy<Geometry1>()),
            geometry::length(geometry2,
                             strategy.template get_distance_strategy<Geometry2>()));
    }
};


template <typename Geometry1, typename Geometry2, typename IntersectionStrategy>
struct collected_vector
{
    typedef typename geometry::select_most_precise
        <
            typename select_coordinate_type
                <
                    Geometry1, Geometry2
                >::type,
            double
        >::type calculation_type;

    typedef geometry::collected_vector
        <
            calculation_type,
            Geometry1,
            typename IntersectionStrategy::side_strategy_type
        > type;
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

        typedef typename collected_vector
            <
                Geometry1, Geometry2, Strategy
            >::type collected_vector_type;

        std::vector<collected_vector_type> c1, c2;

        geometry::collect_vectors(c1, geometry1);
        geometry::collect_vectors(c2, geometry2);

        if (boost::size(c1) != boost::size(c2))
        {
            return false;
        }

        std::sort(c1.begin(), c1.end());
        std::sort(c2.begin(), c2.end());

        // Just check if these vectors are equal.
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

// If collect_vectors which is a SideStrategy-dispatched optimization
// is implemented in a way consistent with the Intersection/Side Strategy
// then collect_vectors is used, otherwise relate is used.
// NOTE: the result could be conceptually different for invalid
// geometries in different coordinate systems because collect_vectors
// and relate treat invalid geometries differently.
template<typename TrivialCheck>
struct equals_by_collection_or_relate
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        typedef typename boost::is_base_of
            <
                nyi::not_implemented_tag,
                typename collected_vector
                    <
                        Geometry1, Geometry2, Strategy
                    >::type
            >::type enable_relate_type;

        return apply(geometry1, geometry2, strategy, enable_relate_type());
    }

private:
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy,
                             boost::false_type /*enable_relate*/)
    {
        return equals_by_collection<TrivialCheck>::apply(geometry1, geometry2, strategy);
    }

    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy,
                             boost::true_type /*enable_relate*/)
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
fdn530QWR3Dp+zslixu7GLNUhjCDqplZWWN3FPh2MoLuQvOd/kXzIWOOzumTRvA+z1glvYJ1fLjs9xC9zfQhaLuzjM/MtufTrWyhkTXdnrU7Xh9X8/jEHG5Dbb5ik5LoCXRuA+909btCBRA3RfM9AxqH/vTj9bsiDs+R57v+TuOMJ/W0poM3VVw0bnCezspyEs63S++9MYfTE33E2Y5HNMyqeb50DmNRlqVP4TzmxUnxGIf6E/AS99aZ/14yN4ObSiZ0c6GGk1F9GrvNDjlY9IPFfdoHXRy1Iq6ywUAB52CwBkVNcWGpK8JQLtr2xQgvVOXll7AcpeL05s6UcpRWxNW2J2PynbtLOS4EGfNxfcTLqeSlhPflfJSx+vgo15XLxTy0G4+8bFhNs1lpvytijvo965MaDz46h39KweFF9Pq9Ksajb3fXCA5R3EKG83FtzEGRuD1eF+FcHBfH52MOisL16MYYR1Z5jn5zjJtW2vAdady3JcX4DrJZ+2hzlYWzuf+lHg35FZhNyWLBHBR1m/HRqqA0eidAbSxnn+l++0w/v1t/4rq+nuC9utugv889m85W32jHiNsh+zjGiBOF7BuQ7TcDMc9g2Tctb7ng3WXj207wvgXZY+C9wPAaLaf5h6aPmXK+ULXJd5AGFQ+zpxGzXJf9nbBXbbySfjYYr/k2+30xnpcqfK/Wu0W4SoIV8wS+ctsy/QBhXo4cbKYy8Zu1Ii48q79lEH2v3Cf+H+AFWAM3IsIOpYrdrTPobu6U86GW/cGdSEaJwXOe7aUck2wZZieLbbGBXJjnhHIEonLsA/koynEoODc1apsx/FfA9S5Re1mm1sHDkEZn3+qe9MVcupa7v5jgRXiht5eB09vZFzEcfiRwJEpSdEVmB26j75BQfrU10eH7TPu+I/Ik28tRyMeHwd4bvFvcnQVWNk/IjiEZ6jxkTekVj/VF+exQ87na67W3r2d9PJ6sC3H61oboccwNnxD5u/crMzxTbjdly87VejUuOHLtdVyGA5v6trbMYZlvWic4OeeyItdXJ4Y4ZnU8zrwqxGrp4XC7B9Glu1HWQVGe11K9mmizSVLlqyEw5+11KQc4107Tb/v5Wb/H01fzSSfYL5C9R2Ugj4dog7vuZsY8/Ar8FKX9adwzReJRlfW1SeIYUWXYkwQm93L79WaAY7QV2KjAaKRt7J5UqtvVgbGobh+v9ufJ/rR3yvQJq7t7++T6fAsw7JsSGPtnJlOsarCWkF8N+K0xX+zd4PjeALyKfMj43siyKL43ExbF58K+hfQHmK3m6ujbGIPFeE77dpbDWix/h5DDSj5/Z3g5z4XSu9hsX38SOLc2uvYzdkOyaFGT8Vg8pPb370M6SHtdz+ruzhMLXXCJ8VcW1+ecp3J4a6DJcyPcSnrHBu+NPn8KrmtRsk1ekMsvjMn3kN+v82BD7kcv0jnmy6ErU0NcV6Zlbq2Uyy3QY58F0duKsl2cG47K1ni7rdVHo3abqO32w0jTtQua2nB9/QhhVsy6+CjkQXspFN0e08SS+Sw6uLZiV0q03TMZQ6BE+f5zBbimoCCM1GxEph18wraD48D5UlNjc6L0X69X9XAl6yHyL32KMV8QeS/bQsKjfZCfJjlVZnyvRj7TKeOsCOcRVAvLiuZ1yVWMp0HxFaE+mTmLejVzhK1Gg3H6GsGhZ455HP2MwLxdRH29lvHYviKN6zyPN/8Ak3lEG0q/sGLFyneEXc9zTK+Xz7m6l6PTzzPOOo3DSp3y2pXxtjDuGOe4Y0yz182M59rrC8zJtdcXmRPZ68uMSXvxHi6Psx3mZ+zA6UqLcBxfDdtzsC/3Dh7H3CylsfsWXFs1k6uovV4=
*/