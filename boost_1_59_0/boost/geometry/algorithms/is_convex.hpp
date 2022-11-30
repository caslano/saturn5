// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2021.
// Modifications copyright (c) 2017-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_IS_CONVEX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_IS_CONVEX_HPP


#include <boost/range/empty.hpp>

#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/dummy_geometries.hpp>
#include <boost/geometry/algorithms/detail/visit.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/visit.hpp>
#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/iterators/ever_circling_iterator.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/is_convex/cartesian.hpp>
#include <boost/geometry/strategies/is_convex/geographic.hpp>
#include <boost/geometry/strategies/is_convex/spherical.hpp>
#include <boost/geometry/views/detail/closed_clockwise_view.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_convex
{

struct ring_is_convex
{
    template <typename Ring, typename Strategies>
    static inline bool apply(Ring const& ring, Strategies const& strategies)
    {
        std::size_t n = boost::size(ring);
        if (n < detail::minimum_ring_size<Ring>::value)
        {
            // (Too) small rings are considered as non-concave, is convex
            return true;
        }

        // Walk in clockwise direction, consider ring as closed
        // (though closure is not important in this algorithm - any dupped
        //  point is skipped)
        using view_type = detail::closed_clockwise_view<Ring const>;
        view_type const view(ring);

        using it_type = geometry::ever_circling_range_iterator<view_type const>;
        it_type previous(view);
        it_type current(view);
        current++;

        auto const equals_strategy = strategies.relate(dummy_point(), dummy_point());

        std::size_t index = 1;
        while (equals::equals_point_point(*current, *previous, equals_strategy)
            && index < n)
        {
            current++;
            index++;
        }

        if (index == n)
        {
            // All points are apparently equal
            return true;
        }

        it_type next = current;
        next++;
        while (equals::equals_point_point(*current, *next, equals_strategy))
        {
            next++;
        }

        auto const side_strategy = strategies.side();

        // We have now three different points on the ring
        // Walk through all points, use a counter because of the ever-circling
        // iterator
        for (std::size_t i = 0; i < n; i++)
        {
            int const side = side_strategy.apply(*previous, *current, *next);
            if (side == 1)
            {
                // Next is on the left side of clockwise ring:
                // the piece is not convex
                return false;
            }

            previous = current;
            current = next;

            // Advance next to next different point
            // (because there are non-equal points, this loop is not infinite)
            next++;
            while (equals::equals_point_point(*current, *next, equals_strategy))
            {
                next++;
            }
        }
        return true;
    }
};


struct polygon_is_convex
{
    template <typename Polygon, typename Strategies>
    static inline bool apply(Polygon const& polygon, Strategies const& strategies)
    {
        return boost::empty(interior_rings(polygon))
            && ring_is_convex::apply(exterior_ring(polygon), strategies);
    }
};

struct multi_polygon_is_convex
{
    template <typename MultiPolygon, typename Strategies>
    static inline bool apply(MultiPolygon const& multi_polygon, Strategies const& strategies)
    {
        auto const size = boost::size(multi_polygon);
        return size == 0 // For consistency with ring_is_convex
            || (size == 1 && polygon_is_convex::apply(range::front(multi_polygon), strategies));
    }
};


}} // namespace detail::is_convex
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct is_convex
{
    template <typename Strategies>
    static inline bool apply(Geometry const&, Strategies const&)
    {
        // Convexity is not defined for PointLike and Linear geometries.
        // We could implement this because the following definitions would work:
        // - no line segment between two points on the interior or boundary ever goes outside.
        // - convex_hull of geometry is equal to the original geometry, this implies equal
        //   topological dimension.
        // For MultiPoint we'd have to check whether or not an arbitrary number of equal points
        //   is stored.
        // MultiPolygon we'd have to check for continuous chain of Linestrings which would require
        //   the use of relate(pt, seg) or distance(pt, pt) strategy.
        return false;
    }
};

template <typename Box>
struct is_convex<Box, box_tag>
{
    template <typename Strategies>
    static inline bool apply(Box const& , Strategies const& )
    {
        // Any box is convex (TODO: consider spherical boxes)
        // TODO: in spherical and geographic the answer would be "false" most of the time.
        //   Assuming that:
        //   - it even makes sense to consider Box in spherical and geographic in this context
        //     because it's not a Polygon, e.g. it can degenerate to a Point.
        //   - line segments are defined by geodesics and box edges by parallels and meridians
        //   - we use this definition: A convex polygon is a simple polygon (not self-intersecting)
        //     in which no line segment between two points on the boundary ever goes outside the
        //     polygon.
        //   Then a geodesic segment would go into the exterior of a Box for all horizontal edges
        //   of a Box unless it was one of the poles (edge degenerated to a point) or equator and
        //   longitude difference was lesser than 360 (otherwise depending on the CS there would be
        //   no solution or there would be two possible solutions - segment going through one of
        //   the poles, at least in case of oblate spheroid, either way the answer would probably
        //   be "false").
        return true;
    }
};

template <typename Ring>
struct is_convex<Ring, ring_tag> : detail::is_convex::ring_is_convex
{};

template <typename Polygon>
struct is_convex<Polygon, polygon_tag> : detail::is_convex::polygon_is_convex
{};

template <typename MultiPolygon>
struct is_convex<MultiPolygon, multi_polygon_tag> : detail::is_convex::multi_polygon_is_convex
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

namespace resolve_strategy {

template
<
    typename Strategies,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategies>::value
>
struct is_convex
{
    template <typename Geometry>
    static bool apply(Geometry const& geometry, Strategies const& strategies)
    {
        return dispatch::is_convex<Geometry>::apply(geometry, strategies);
    }
};

template <typename Strategy>
struct is_convex<Strategy, false>
{
    template <typename Geometry>
    static bool apply(Geometry const& geometry, Strategy const& strategy)
    {
        using strategies::is_convex::services::strategy_converter;
        return dispatch::is_convex
            <
                Geometry
            >::apply(geometry, strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct is_convex<default_strategy, false>
{
    template <typename Geometry>
    static bool apply(Geometry const& geometry, default_strategy const& )
    {
        typedef typename strategies::is_convex::services::default_strategy
            <
                Geometry
            >::type strategy_type;

        return dispatch::is_convex<Geometry>::apply(geometry, strategy_type());
    }
};

} // namespace resolve_strategy

namespace resolve_dynamic {

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct is_convex
{
    template <typename Strategy>
    static bool apply(Geometry const& geometry, Strategy const& strategy)
    {
        concepts::check<Geometry>();
        return resolve_strategy::is_convex<Strategy>::apply(geometry, strategy);
    }
};

template <typename Geometry>
struct is_convex<Geometry, dynamic_geometry_tag>
{
    template <typename Strategy>
    static inline bool apply(Geometry const& geometry, Strategy const& strategy)
    {
        bool result = false;
        traits::visit<Geometry>::apply([&](auto const& g)
        {
            result = is_convex<util::remove_cref_t<decltype(g)>>::apply(g, strategy);
        }, geometry);
        return result;
    }
};

// NOTE: This is a simple implementation checking if a GC contains single convex geometry.
//   Technically a GC could store e.g. polygons touching with edges and together creating a convex
//   region. To check this we'd require relate() strategy and the algorithm would be quite complex.
template <typename Geometry>
struct is_convex<Geometry, geometry_collection_tag>
{
    template <typename Strategy>
    static inline bool apply(Geometry const& geometry, Strategy const& strategy)
    {
        bool result = false;
        bool is_first = true;
        detail::visit_breadth_first([&](auto const& g)
        {
            result = is_first
                  && is_convex<util::remove_cref_t<decltype(g)>>::apply(g, strategy);
            is_first = false;
            return result;
        }, geometry);
        return result;
    }
};

} // namespace resolve_dynamic

// TODO: documentation / qbk
template<typename Geometry>
inline bool is_convex(Geometry const& geometry)
{
    return resolve_dynamic::is_convex
            <
                Geometry
            >::apply(geometry, geometry::default_strategy());
}

// TODO: documentation / qbk
template<typename Geometry, typename Strategy>
inline bool is_convex(Geometry const& geometry, Strategy const& strategy)
{
    return resolve_dynamic::is_convex<Geometry>::apply(geometry, strategy);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_IS_CONVEX_HPP

/* is_convex.hpp
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
*/