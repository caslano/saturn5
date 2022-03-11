// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_HAVERSINE_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_HAVERSINE_HPP


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/radian_access.hpp>

#include <boost/geometry/srs/sphere.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/spherical/get_radius.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/promote_floating_point.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace distance
{


namespace comparable
{

// Comparable haversine.
// To compare distances, we can avoid:
// - multiplication with radius and 2.0
// - applying sqrt
// - applying asin (which is strictly (monotone) increasing)
template
<
    typename RadiusTypeOrSphere = double,
    typename CalculationType = void
>
class haversine
{
public :
    template <typename Point1, typename Point2>
    struct calculation_type
        : promote_floating_point
          <
              typename select_calculation_type
                  <
                      Point1,
                      Point2,
                      CalculationType
                  >::type
          >
    {};

    typedef typename strategy_detail::get_radius
        <
            RadiusTypeOrSphere
        >::type radius_type;

    inline haversine()
        : m_radius(1.0)
    {}

    template <typename RadiusOrSphere>
    explicit inline haversine(RadiusOrSphere const& radius_or_sphere)
        : m_radius(strategy_detail::get_radius
                    <
                        RadiusOrSphere
                    >::apply(radius_or_sphere))
    {}

    template <typename Point1, typename Point2>
    static inline typename calculation_type<Point1, Point2>::type
    apply(Point1 const& p1, Point2 const& p2)
    {
        return calculate<typename calculation_type<Point1, Point2>::type>(
                   get_as_radian<0>(p1), get_as_radian<1>(p1),
                   get_as_radian<0>(p2), get_as_radian<1>(p2)
               );
    }

    inline radius_type radius() const
    {
        return m_radius;
    }


private :
    template <typename R, typename T1, typename T2>
    static inline R calculate(T1 const& lon1, T1 const& lat1,
                              T2 const& lon2, T2 const& lat2)
    {
        return math::hav(lat2 - lat1)
                + cos(lat1) * cos(lat2) * math::hav(lon2 - lon1);
    }

    radius_type m_radius;
};



} // namespace comparable

/*!
\brief Distance calculation for spherical coordinates
on a perfect sphere using haversine
\ingroup strategies
\tparam RadiusTypeOrSphere \tparam_radius_or_sphere
\tparam CalculationType \tparam_calculation
\author Adapted from: http://williams.best.vwh.net/avform.htm
\see http://en.wikipedia.org/wiki/Great-circle_distance
\note (from Wiki:) The great circle distance d between two
points with coordinates {lat1,lon1} and {lat2,lon2} is given by:
    d=acos(sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(lon1-lon2))
A mathematically equivalent formula, which is less subject
    to rounding error for short distances is:
    d=2*asin(sqrt((sin((lat1-lat2) / 2))^2
    + cos(lat1)*cos(lat2)*(sin((lon1-lon2) / 2))^2))
\qbk{
[heading See also]
[link geometry.reference.algorithms.distance.distance_3_with_strategy distance (with strategy)]
}
*/
template
<
    typename RadiusTypeOrSphere = double,
    typename CalculationType = void
>
class haversine
{
    typedef comparable::haversine<RadiusTypeOrSphere, CalculationType> comparable_type;

public :
    template <typename Point1, typename Point2>
    struct calculation_type
        : services::return_type<comparable_type, Point1, Point2>
    {};

    typedef typename strategy_detail::get_radius
        <
            RadiusTypeOrSphere
        >::type radius_type;

    /*!
    \brief Default constructor, radius set to 1.0 for the unit sphere
    */
    inline haversine()
        : m_radius(1.0)
    {}

    /*!
    \brief Constructor
    \param radius_or_sphere radius of the sphere or sphere model
    */
    template <typename RadiusOrSphere>
    explicit inline haversine(RadiusOrSphere const& radius_or_sphere)
        : m_radius(strategy_detail::get_radius
                    <
                        RadiusOrSphere
                    >::apply(radius_or_sphere))
    {}

    /*!
    \brief applies the distance calculation
    \return the calculated distance (including multiplying with radius)
    \param p1 first point
    \param p2 second point
    */
    template <typename Point1, typename Point2>
    inline typename calculation_type<Point1, Point2>::type
    apply(Point1 const& p1, Point2 const& p2) const
    {
        typedef typename calculation_type<Point1, Point2>::type calculation_type;
        calculation_type const a = comparable_type::apply(p1, p2);
        calculation_type const c = calculation_type(2.0) * asin(math::sqrt(a));
        return calculation_type(m_radius) * c;
    }

    /*!
    \brief access to radius value
    \return the radius
    */
    inline radius_type radius() const
    {
        return m_radius;
    }

private :
    radius_type m_radius;
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename RadiusType, typename CalculationType>
struct tag<haversine<RadiusType, CalculationType> >
{
    typedef strategy_tag_distance_point_point type;
};


template <typename RadiusType, typename CalculationType, typename P1, typename P2>
struct return_type<haversine<RadiusType, CalculationType>, P1, P2>
    : haversine<RadiusType, CalculationType>::template calculation_type<P1, P2>
{};


template <typename RadiusType, typename CalculationType>
struct comparable_type<haversine<RadiusType, CalculationType> >
{
    typedef comparable::haversine<RadiusType, CalculationType> type;
};


template <typename RadiusType, typename CalculationType>
struct get_comparable<haversine<RadiusType, CalculationType> >
{
private :
    typedef haversine<RadiusType, CalculationType> this_type;
    typedef comparable::haversine<RadiusType, CalculationType> comparable_type;
public :
    static inline comparable_type apply(this_type const& input)
    {
        return comparable_type(input.radius());
    }
};

template <typename RadiusType, typename CalculationType, typename P1, typename P2>
struct result_from_distance<haversine<RadiusType, CalculationType>, P1, P2>
{
private :
    typedef haversine<RadiusType, CalculationType> this_type;
    typedef typename return_type<this_type, P1, P2>::type return_type;
public :
    template <typename T>
    static inline return_type apply(this_type const& , T const& value)
    {
        return return_type(value);
    }
};


// Specializations for comparable::haversine
template <typename RadiusType, typename CalculationType>
struct tag<comparable::haversine<RadiusType, CalculationType> >
{
    typedef strategy_tag_distance_point_point type;
};


template <typename RadiusType, typename CalculationType, typename P1, typename P2>
struct return_type<comparable::haversine<RadiusType, CalculationType>, P1, P2>
    : comparable::haversine<RadiusType, CalculationType>::template calculation_type<P1, P2>
{};


template <typename RadiusType, typename CalculationType>
struct comparable_type<comparable::haversine<RadiusType, CalculationType> >
{
    typedef comparable::haversine<RadiusType, CalculationType> type;
};


template <typename RadiusType, typename CalculationType>
struct get_comparable<comparable::haversine<RadiusType, CalculationType> >
{
private :
    typedef comparable::haversine<RadiusType, CalculationType> this_type;
public :
    static inline this_type apply(this_type const& input)
    {
        return input;
    }
};


template <typename RadiusType, typename CalculationType, typename P1, typename P2>
struct result_from_distance<comparable::haversine<RadiusType, CalculationType>, P1, P2>
{
private :
    typedef comparable::haversine<RadiusType, CalculationType> strategy_type;
    typedef typename return_type<strategy_type, P1, P2>::type return_type;
public :
    template <typename T>
    static inline return_type apply(strategy_type const& strategy, T const& distance)
    {
        return_type const s = sin((distance / strategy.radius()) / return_type(2));
        return s * s;
    }
};


// Register it as the default for point-types
// in a spherical equatorial coordinate system
template <typename Point1, typename Point2>
struct default_strategy
    <
        point_tag, point_tag, Point1, Point2,
        spherical_equatorial_tag, spherical_equatorial_tag
    >
{
    typedef strategy::distance::haversine<typename select_coordinate_type<Point1, Point2>::type> type;
};

// Note: spherical polar coordinate system requires "get_as_radian_equatorial"


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_HAVERSINE_HPP

/* distance_haversine.hpp
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
*/