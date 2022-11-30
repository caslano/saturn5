// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2013 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_POINT_ON_SURFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_POINT_ON_SURFACE_HPP


#include <cstddef>
#include <numeric>

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

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