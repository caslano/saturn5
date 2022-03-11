// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2013 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014, 2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_POINT_ON_SURFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_POINT_ON_SURFACE_HPP


#include <cstddef>

#include <numeric>

#include <boost/concept_check.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/ring_type.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/detail/extreme_points.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>

#include <boost/geometry/strategies/cartesian/centroid_bashein_detmer.hpp>
#include <boost/geometry/strategies/side.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace point_on_surface
{

template <typename CoordinateType, int Dimension>
struct specific_coordinate_first
{
    CoordinateType const m_value_to_be_first;

    inline specific_coordinate_first(CoordinateType value_to_be_skipped)
        : m_value_to_be_first(value_to_be_skipped)
    {}

    template <typename Point>
    inline bool operator()(Point const& lhs, Point const& rhs)
    {
        CoordinateType const lh = geometry::get<Dimension>(lhs);
        CoordinateType const rh = geometry::get<Dimension>(rhs);

        // If both lhs and rhs equal m_value_to_be_first,
        // we should handle conform if lh < rh = FALSE
        // The first condition meets that, keep it first
        if (geometry::math::equals(rh, m_value_to_be_first))
        {
            // Handle conform lh < -INF, which is always false
            return false;
        }

        if (geometry::math::equals(lh, m_value_to_be_first))
        {
            // Handle conform -INF < rh, which is always true
            return true;
        }

        return lh < rh;
    }
};

template <int Dimension, typename Collection, typename Value, typename Predicate>
inline bool max_value(Collection const& collection, Value& the_max, Predicate const& predicate)
{
    bool first = true;
    for (typename Collection::const_iterator it = collection.begin(); it != collection.end(); ++it)
    {
        if (! it->empty())
        {
            Value the_value = geometry::get<Dimension>(*std::max_element(it->begin(), it->end(), predicate));
            if (first || the_value > the_max)
            {
                the_max = the_value;
                first = false;
            }
        }
    }
    return ! first;
}


template <int Dimension, typename Value>
struct select_below
{
    Value m_value;
    inline select_below(Value const& v)
        : m_value(v)
    {}

    template <typename Intruder>
    inline bool operator()(Intruder const& intruder) const
    {
        if (intruder.empty())
        {
            return true;
        }
        Value max = geometry::get<Dimension>(*std::max_element(intruder.begin(), intruder.end(), detail::extreme_points::compare<Dimension>()));
        return geometry::math::equals(max, m_value) || max < m_value;
    }
};

template <int Dimension, typename Value>
struct adapt_base
{
    Value m_value;
    inline adapt_base(Value const& v)
        : m_value(v)
    {}

    template <typename Intruder>
    inline void operator()(Intruder& intruder) const
    {
        if (intruder.size() >= 3)
        {
            detail::extreme_points::move_along_vector<Dimension>(intruder, m_value);
        }
    }
};

template <int Dimension, typename Value>
struct min_of_intruder
{
    template <typename Intruder>
    inline bool operator()(Intruder const& lhs, Intruder const& rhs) const
    {
        Value lhs_min = geometry::get<Dimension>(*std::min_element(lhs.begin(), lhs.end(), detail::extreme_points::compare<Dimension>()));
        Value rhs_min = geometry::get<Dimension>(*std::min_element(rhs.begin(), rhs.end(), detail::extreme_points::compare<Dimension>()));
        return lhs_min < rhs_min;
    }
};


template <typename Point, typename P>
inline void calculate_average(Point& point, std::vector<P> const& points)
{
    typedef typename geometry::coordinate_type<Point>::type coordinate_type;
    typedef typename std::vector<P>::const_iterator iterator_type;

    coordinate_type x = 0;
    coordinate_type y = 0;

    iterator_type end = points.end();
    for ( iterator_type it = points.begin() ; it != end ; ++it)
    {
        x += geometry::get<0>(*it);
        y += geometry::get<1>(*it);
    }

    signed_size_type const count = points.size();
    geometry::set<0>(point, x / count);
    geometry::set<1>(point, y / count);
}


template <int Dimension, typename Extremes, typename Intruders, typename CoordinateType>
inline void replace_extremes_for_self_tangencies(Extremes& extremes, Intruders& intruders, CoordinateType const& max_intruder)
{
    // This function handles self-tangencies.
    // Self-tangencies use, as usual, the major part of code...

    //        ___ e
    //       /|\ \                                                            .
    //      / | \ \                                                           .
    //     /  |  \ \                                                          .
    //    /   |   \ \                                                         .
    //   / /\ |    \ \                                                        .
    //     i2    i1

    // The picture above shows the extreme (outside, "e") and two intruders ("i1","i2")
    // Assume that "i1" is self-tangent with the extreme, in one point at the top
    // Now the "penultimate" value is searched, this is is the top of i2
    // Then everything including and below (this is "i2" here) is removed
    // Then the base of "i1" and of "e" is adapted to this penultimate value
    // It then looks like:

    //      b ___ e
    //       /|\ \                                                            .
    //      / | \ \                                                           .
    //     /  |  \ \                                                          .
    //    /   |   \ \                                                         .
    //   a    c i1

    // Then intruders (here "i1" but there may be more) are sorted from left to right
    // Finally points "a","b" and "c" (in this order) are selected as a new triangle.
    // This triangle will have a centroid which is inside (assumed that intruders left segment
    // is not equal to extremes left segment, but that polygon would be invalid)

    // Find highest non-self tangent intrusion, if any
    CoordinateType penultimate_value;
    specific_coordinate_first<CoordinateType, Dimension> pu_compare(max_intruder);
    if (max_value<Dimension>(intruders, penultimate_value, pu_compare))
    {
        // Throw away all intrusions <= this value, and of the kept one set this as base.
        select_below<Dimension, CoordinateType> predicate(penultimate_value);
        intruders.erase
            (
                std::remove_if(boost::begin(intruders), boost::end(intruders), predicate),
                boost::end(intruders)
            );
        adapt_base<Dimension, CoordinateType> fe_predicate(penultimate_value);
        // Sort from left to right (or bottom to top if Dimension=0)
        std::for_each(boost::begin(intruders), boost::end(intruders), fe_predicate);

        // Also adapt base of extremes
        detail::extreme_points::move_along_vector<Dimension>(extremes, penultimate_value);
    }
    // Then sort in 1-Dim. Take first to calc centroid.
    std::sort(boost::begin(intruders), boost::end(intruders), min_of_intruder<1 - Dimension, CoordinateType>());

    Extremes triangle;
    triangle.reserve(3);

    // Make a triangle of first two points of extremes (the ramp, from left to right), and last point of first intruder (which goes from right to left)
    std::copy(extremes.begin(), extremes.begin() + 2, std::back_inserter(triangle));
    triangle.push_back(intruders.front().back());

    // (alternatively we could use the last two points of extremes, and first point of last intruder...):
    //// ALTERNATIVE: std::copy(extremes.rbegin(), extremes.rbegin() + 2, std::back_inserter(triangle));
    //// ALTERNATIVE: triangle.push_back(intruders.back().front());

    // Now replace extremes with this smaller subset, a triangle, such that centroid calculation will result in a point inside
    extremes = triangle;
}

template <int Dimension, typename Geometry, typename Point, typename SideStrategy>
inline bool calculate_point_on_surface(Geometry const& geometry, Point& point,
                                       SideStrategy const& strategy)
{
    typedef typename geometry::point_type<Geometry>::type point_type;
    typedef typename geometry::coordinate_type<Geometry>::type coordinate_type;
    std::vector<point_type> extremes;

    typedef std::vector<std::vector<point_type> > intruders_type;
    intruders_type intruders;
    geometry::extreme_points<Dimension>(geometry, extremes, intruders, strategy);

    if (extremes.size() < 3)
    {
        return false;
    }

    // If there are intruders, find the max.
    if (! intruders.empty())
    {
        coordinate_type max_intruder;
        detail::extreme_points::compare<Dimension> compare;
        if (max_value<Dimension>(intruders, max_intruder, compare))
        {
            coordinate_type max_extreme = geometry::get<Dimension>(*std::max_element(extremes.begin(), extremes.end(), detail::extreme_points::compare<Dimension>()));
            if (max_extreme > max_intruder)
            {
                detail::extreme_points::move_along_vector<Dimension>(extremes, max_intruder);
            }
            else
            {
                replace_extremes_for_self_tangencies<Dimension>(extremes, intruders, max_intruder);
            }
        }
    }

    // Now calculate the average/centroid of the (possibly adapted) extremes
    calculate_average(point, extremes);

    return true;
}

}} // namespace detail::point_on_surface
#endif // DOXYGEN_NO_DETAIL


/*!
\brief Assigns a Point guaranteed to lie on the surface of the Geometry
\tparam Geometry geometry type. This also defines the type of the output point
\param geometry Geometry to take point from
\param point Point to assign
\param strategy side strategy
 */
template <typename Geometry, typename Point, typename SideStrategy>
inline void point_on_surface(Geometry const& geometry, Point & point,
                             SideStrategy const& strategy)
{
    concepts::check<Point>();
    concepts::check<Geometry const>();

    // First try in Y-direction (which should always succeed for valid polygons)
    if (! detail::point_on_surface::calculate_point_on_surface<1>(geometry, point, strategy))
    {
        // For invalid polygons, we might try X-direction
        detail::point_on_surface::calculate_point_on_surface<0>(geometry, point, strategy);
    }
}

/*!
\brief Assigns a Point guaranteed to lie on the surface of the Geometry
\tparam Geometry geometry type. This also defines the type of the output point
\param geometry Geometry to take point from
\param point Point to assign
 */
template <typename Geometry, typename Point>
inline void point_on_surface(Geometry const& geometry, Point & point)
{
    typedef typename strategy::side::services::default_strategy
        <
            typename cs_tag<Geometry>::type
        >::type strategy_type;

    point_on_surface(geometry, point, strategy_type());
}


/*!
\brief Returns point guaranteed to lie on the surface of the Geometry
\tparam Geometry geometry type. This also defines the type of the output point
\param geometry Geometry to take point from
\param strategy side strategy
\return The Point guaranteed to lie on the surface of the Geometry
 */
template<typename Geometry, typename SideStrategy>
inline typename geometry::point_type<Geometry>::type
return_point_on_surface(Geometry const& geometry, SideStrategy const& strategy)
{
    typename geometry::point_type<Geometry>::type result;
    geometry::point_on_surface(geometry, result, strategy);
    return result;
}

/*!
\brief Returns point guaranteed to lie on the surface of the Geometry
\tparam Geometry geometry type. This also defines the type of the output point
\param geometry Geometry to take point from
\return The Point guaranteed to lie on the surface of the Geometry
 */
template<typename Geometry>
inline typename geometry::point_type<Geometry>::type
return_point_on_surface(Geometry const& geometry)
{
    typename geometry::point_type<Geometry>::type result;
    geometry::point_on_surface(geometry, result);
    return result;
}

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_POINT_ON_SURFACE_HPP

/* point_on_surface.hpp
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
*/