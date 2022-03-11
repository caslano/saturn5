// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2013 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXTREME_POINTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXTREME_POINTS_HPP


#include <cstddef>

#include <boost/range.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/iterators/ever_circling_iterator.hpp>

#include <boost/geometry/algorithms/detail/assign_box_corners.hpp>

#include <boost/geometry/strategies/side.hpp>

#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace extreme_points
{

template <std::size_t Dimension>
struct compare
{
    template <typename Point>
    inline bool operator()(Point const& lhs, Point const& rhs)
    {
        return geometry::get<Dimension>(lhs) < geometry::get<Dimension>(rhs);
    }
};


template <std::size_t Dimension, typename PointType, typename CoordinateType>
inline void move_along_vector(PointType& point, PointType const& extreme, CoordinateType const& base_value)
{
    // Moves a point along the vector (point, extreme) in the direction of the extreme  point
    // This adapts the possibly uneven legs of the triangle (or trapezium-like shape)
    //      _____extreme            _____
    //     /     \                 /     \                                    .
    //    /base   \         =>    /       \ point                             .
    //             \ point                                                    .
    //
    // For so-called intruders, it can be used to adapt both legs to the level of "base"
    // For the base, it can be used to adapt both legs to the level of the max-value of the intruders
    // If there are 2 or more extreme values, use the one close to 'point' to have a correct vector

    CoordinateType const value = geometry::get<Dimension>(point);
    //if (geometry::math::equals(value, base_value))
    if (value >= base_value)
    {
        return;
    }

    PointType vector = point;
    subtract_point(vector, extreme);

    CoordinateType const diff = geometry::get<Dimension>(vector);

    // diff should never be zero
    // because of the way our triangle/trapezium is build.
    // We just return if it would be the case.
    if (geometry::math::equals(diff, 0))
    {
        return;
    }

    CoordinateType const base_diff = base_value - geometry::get<Dimension>(extreme);

    multiply_value(vector, base_diff);
    divide_value(vector, diff);

    // The real move:
    point = extreme;
    add_point(point, vector);
}


template <std::size_t Dimension, typename Range, typename CoordinateType>
inline void move_along_vector(Range& range, CoordinateType const& base_value)
{
    if (range.size() >= 3)
    {
        move_along_vector<Dimension>(range.front(), *(range.begin() + 1), base_value);
        move_along_vector<Dimension>(range.back(), *(range.rbegin() + 1), base_value);
    }
}


template<typename Ring, std::size_t Dimension>
struct extreme_points_on_ring
{

    typedef typename geometry::coordinate_type<Ring>::type coordinate_type;
    typedef typename boost::range_iterator<Ring const>::type range_iterator;
    typedef typename geometry::point_type<Ring>::type point_type;

    template <typename CirclingIterator, typename Points>
    static inline bool extend(CirclingIterator& it,
            std::size_t n,
            coordinate_type max_coordinate_value,
            Points& points, int direction)
    {
        std::size_t safe_index = 0;
        do
        {
            it += direction;

            points.push_back(*it);

            if (safe_index++ >= n)
            {
                // E.g.: ring is completely horizontal or vertical (= invalid, but we don't want to have an infinite loop)
                return false;
            }
        } while (geometry::math::equals(geometry::get<Dimension>(*it), max_coordinate_value));

        return true;
    }

    // Overload without adding to poinst
    template <typename CirclingIterator>
    static inline bool extend(CirclingIterator& it,
            std::size_t n,
            coordinate_type max_coordinate_value,
            int direction)
    {
        std::size_t safe_index = 0;
        do
        {
            it += direction;

            if (safe_index++ >= n)
            {
                // E.g.: ring is completely horizontal or vertical (= invalid, but we don't want to have an infinite loop)
                return false;
            }
        } while (geometry::math::equals(geometry::get<Dimension>(*it), max_coordinate_value));

        return true;
    }

    template <typename CirclingIterator>
    static inline bool extent_both_sides(Ring const& ring,
            point_type extreme,
            CirclingIterator& left,
            CirclingIterator& right)
    {
        std::size_t const n = boost::size(ring);
        coordinate_type const max_coordinate_value = geometry::get<Dimension>(extreme);

        if (! extend(left, n, max_coordinate_value, -1))
        {
            return false;
        }
        if (! extend(right, n, max_coordinate_value, +1))
        {
            return false;
        }

        return true;
    }

    template <typename Collection, typename CirclingIterator>
    static inline bool collect(Ring const& ring,
            point_type extreme,
            Collection& points,
            CirclingIterator& left,
            CirclingIterator& right)
    {
        std::size_t const n = boost::size(ring);
        coordinate_type const max_coordinate_value = geometry::get<Dimension>(extreme);

        // Collects first left, which is reversed (if more than one point) then adds the top itself, then right
        if (! extend(left, n, max_coordinate_value, points, -1))
        {
            return false;
        }
        std::reverse(points.begin(), points.end());
        points.push_back(extreme);
        if (! extend(right, n, max_coordinate_value, points, +1))
        {
            return false;
        }

        return true;
    }

    template <typename Extremes, typename Intruders, typename CirclingIterator, typename SideStrategy>
    static inline void get_intruders(Ring const& ring, CirclingIterator left, CirclingIterator right,
            Extremes const& extremes,
            Intruders& intruders,
            SideStrategy const& strategy)
    {
        if (boost::size(extremes) < 3)
        {
            return;
        }
        coordinate_type const min_value = geometry::get<Dimension>(*std::min_element(boost::begin(extremes), boost::end(extremes), compare<Dimension>()));

        // Also select left/right (if Dimension=1)
        coordinate_type const other_min = geometry::get<1 - Dimension>(*std::min_element(boost::begin(extremes), boost::end(extremes), compare<1 - Dimension>()));
        coordinate_type const other_max = geometry::get<1 - Dimension>(*std::max_element(boost::begin(extremes), boost::end(extremes), compare<1 - Dimension>()));

        std::size_t defensive_check_index = 0; // in case we skip over left/right check, collect modifies right too
        std::size_t const n = boost::size(ring);
        while (left != right && defensive_check_index < n)
        {
            coordinate_type const coordinate = geometry::get<Dimension>(*right);
            coordinate_type const other_coordinate = geometry::get<1 - Dimension>(*right);
            if (coordinate > min_value && other_coordinate > other_min && other_coordinate < other_max)
            {
                int const factor = geometry::point_order<Ring>::value == geometry::clockwise ? 1 : -1;
                int const first_side = strategy.apply(*right, extremes.front(), *(extremes.begin() + 1)) * factor;
                int const last_side = strategy.apply(*right, *(extremes.rbegin() + 1), extremes.back()) * factor;

                // If not lying left from any of the extemes side
                if (first_side != 1 && last_side != 1)
                {
                    //std::cout << "first " << first_side << " last " << last_side << std::endl;

                    // we start at this intrusion until it is handled, and don't affect our initial left iterator
                    CirclingIterator left_intrusion_it = right;
                    typename boost::range_value<Intruders>::type intruder;
                    collect(ring, *right, intruder, left_intrusion_it, right);

                    // Also moves these to base-level, makes sorting possible which can be done in case of self-tangencies
                    // (we might postpone this action, it is often not necessary. However it is not time-consuming)
                    move_along_vector<Dimension>(intruder, min_value);
                    intruders.push_back(intruder);
                    --right;
                }
            }
            ++right;
            defensive_check_index++;
        }
    }

    template <typename Extremes, typename Intruders, typename SideStrategy>
    static inline void get_intruders(Ring const& ring,
            Extremes const& extremes,
            Intruders& intruders,
            SideStrategy const& strategy)
    {
        std::size_t const n = boost::size(ring);
        if (n >= 3)
        {
            geometry::ever_circling_range_iterator<Ring const> left(ring);
            geometry::ever_circling_range_iterator<Ring const> right(ring);
            ++right;

            get_intruders(ring, left, right, extremes, intruders, strategy);
        }
    }

    template <typename Iterator, typename SideStrategy>
    static inline bool right_turn(Ring const& ring, Iterator it, SideStrategy const& strategy)
    {
        typename std::iterator_traits<Iterator>::difference_type const index
            = std::distance(boost::begin(ring), it);
        geometry::ever_circling_range_iterator<Ring const> left(ring);
        geometry::ever_circling_range_iterator<Ring const> right(ring);
        left += index;
        right += index;

        if (! extent_both_sides(ring, *it, left, right))
        {
            return false;
        }

        int const factor = geometry::point_order<Ring>::value == geometry::clockwise ? 1 : -1;
        int const first_side = strategy.apply(*(right - 1), *right, *left) * factor;
        int const last_side = strategy.apply(*left, *(left + 1), *right) * factor;

//std::cout << "Candidate at " << geometry::wkt(*it) << " first=" << first_side << " last=" << last_side << std::endl;

        // Turn should not be left (actually, it should be right because extent removes horizontal/collinear cases)
        return first_side != 1 && last_side != 1;
    }


    // Gets the extreme segments (top point plus neighbouring points), plus intruders, if any, on the same ring
    template <typename Extremes, typename Intruders, typename SideStrategy>
    static inline bool apply(Ring const& ring,
                             Extremes& extremes,
                             Intruders& intruders,
                             SideStrategy const& strategy)
    {
        std::size_t const n = boost::size(ring);
        if (n < 3)
        {
            return false;
        }

        // Get all maxima, usually one. In case of self-tangencies, or self-crossings,
        // the max might be is not valid. A valid max should make a right turn
        range_iterator max_it = boost::begin(ring);
        compare<Dimension> smaller;
        for (range_iterator it = max_it + 1; it != boost::end(ring); ++it)
        {
            if (smaller(*max_it, *it) && right_turn(ring, it, strategy))
            {
                max_it = it;
            }
        }

        if (max_it == boost::end(ring))
        {
            return false;
        }

        typename std::iterator_traits<range_iterator>::difference_type const
            index = std::distance(boost::begin(ring), max_it);
//std::cout << "Extreme point lies at " << index << " having " << geometry::wkt(*max_it) << std::endl;

        geometry::ever_circling_range_iterator<Ring const> left(ring);
        geometry::ever_circling_range_iterator<Ring const> right(ring);
        left += index;
        right += index;

        // Collect all points (often 3) in a temporary vector
        std::vector<point_type> points;
        points.reserve(3);
        if (! collect(ring, *max_it, points, left, right))
        {
            return false;
        }

//std::cout << "Built vector of " << points.size() << std::endl;

        coordinate_type const front_value = geometry::get<Dimension>(points.front());
        coordinate_type const back_value = geometry::get<Dimension>(points.back());
        coordinate_type const base_value = (std::max)(front_value, back_value);
        if (front_value < back_value)
        {
            move_along_vector<Dimension>(points.front(), *(points.begin() + 1), base_value);
        }
        else
        {
            move_along_vector<Dimension>(points.back(), *(points.rbegin() + 1), base_value);
        }

        std::copy(points.begin(), points.end(), std::back_inserter(extremes));

        get_intruders(ring, left, right, extremes, intruders, strategy);

        return true;
    }
};





}} // namespace detail::extreme_points
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry,
    std::size_t Dimension,
    typename GeometryTag = typename tag<Geometry>::type
>
struct extreme_points
{};


template<typename Ring, std::size_t Dimension>
struct extreme_points<Ring, Dimension, ring_tag>
    : detail::extreme_points::extreme_points_on_ring<Ring, Dimension>
{};


template<typename Polygon, std::size_t Dimension>
struct extreme_points<Polygon, Dimension, polygon_tag>
{
    template <typename Extremes, typename Intruders, typename SideStrategy>
    static inline bool apply(Polygon const& polygon, Extremes& extremes, Intruders& intruders,
                             SideStrategy const& strategy)
    {
        typedef typename geometry::ring_type<Polygon>::type ring_type;
        typedef detail::extreme_points::extreme_points_on_ring
            <
                ring_type, Dimension
            > ring_implementation;

        if (! ring_implementation::apply(geometry::exterior_ring(polygon),
                                         extremes, intruders, strategy))
        {
            return false;
        }

        // For a polygon, its interior rings can contain intruders
        typename interior_return_type<Polygon const>::type
            rings = interior_rings(polygon);
        for (typename detail::interior_iterator<Polygon const>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            ring_implementation::get_intruders(*it, extremes,  intruders, strategy);
        }

        return true;
    }
};

template<typename Box>
struct extreme_points<Box, 1, box_tag>
{
    template <typename Extremes, typename Intruders, typename SideStrategy>
    static inline bool apply(Box const& box, Extremes& extremes, Intruders& ,
                             SideStrategy const& )
    {
        extremes.resize(4);
        geometry::detail::assign_box_corners_oriented<false>(box, extremes);
        // ll,ul,ur,lr, contains too exactly the right info
        return true;
    }
};

template<typename Box>
struct extreme_points<Box, 0, box_tag>
{
    template <typename Extremes, typename Intruders, typename SideStrategy>
    static inline bool apply(Box const& box, Extremes& extremes, Intruders& ,
                             SideStrategy const& )
    {
        extremes.resize(4);
        geometry::detail::assign_box_corners_oriented<false>(box, extremes);
        // ll,ul,ur,lr, rotate one to start with UL and end with LL
        std::rotate(extremes.begin(), extremes.begin() + 1, extremes.end());
        return true;
    }
};

template<typename MultiPolygon, std::size_t Dimension>
struct extreme_points<MultiPolygon, Dimension, multi_polygon_tag>
{
    template <typename Extremes, typename Intruders, typename SideStrategy>
    static inline bool apply(MultiPolygon const& multi, Extremes& extremes,
                             Intruders& intruders, SideStrategy const& strategy)
    {
        // Get one for the very first polygon, that is (for the moment) enough.
        // It is not guaranteed the "extreme" then, but for the current purpose
        // (point_on_surface) it can just be this point.
        if (boost::size(multi) >= 1)
        {
            return extreme_points
                <
                    typename boost::range_value<MultiPolygon const>::type,
                    Dimension,
                    polygon_tag
                >::apply(*boost::begin(multi), extremes, intruders, strategy);
        }

        return false;
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief Returns extreme points (for Edge=1 in dimension 1, so the top,
       for Edge=0 in dimension 0, the right side)
\note We could specify a strategy (less/greater) to get bottom/left side too. However, until now we don't need that.
 */
template
<
    std::size_t Edge,
    typename Geometry,
    typename Extremes,
    typename Intruders,
    typename SideStrategy
>
inline bool extreme_points(Geometry const& geometry,
                           Extremes& extremes,
                           Intruders& intruders,
                           SideStrategy const& strategy)
{
    concepts::check<Geometry const>();

    // Extremes is not required to follow a geometry concept (but it should support an output iterator),
    // but its elements should fulfil the point-concept
    concepts::check<typename boost::range_value<Extremes>::type>();

    // Intruders should contain collections which value type is point-concept
    // Extremes might be anything (supporting an output iterator), but its elements should fulfil the point-concept
    concepts::check
        <
            typename boost::range_value
                <
                    typename boost::range_value<Intruders>::type
                >::type
            const
        >();

    return dispatch::extreme_points
            <
                Geometry,
                Edge
            >::apply(geometry, extremes, intruders, strategy);
}


template
<
    std::size_t Edge,
    typename Geometry,
    typename Extremes,
    typename Intruders
>
inline bool extreme_points(Geometry const& geometry,
                           Extremes& extremes,
                           Intruders& intruders)
{
    typedef typename strategy::side::services::default_strategy
            <
                typename cs_tag<Geometry>::type
            >::type strategy_type;

    return geometry::extreme_points<Edge>(geometry,extremes, intruders, strategy_type());
}

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXTREME_POINTS_HPP

/* extreme_points.hpp
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
*/