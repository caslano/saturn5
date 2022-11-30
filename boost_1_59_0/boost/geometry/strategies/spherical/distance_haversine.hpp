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
#include <boost/geometry/core/coordinate_promotion.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/radian_access.hpp>

#include <boost/geometry/srs/sphere.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/spherical/get_radius.hpp>

#include <boost/geometry/util/math.hpp>
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