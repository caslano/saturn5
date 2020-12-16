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
wvLU4S6silWwDlbFhuiB3bA69kEvHIXeOAFr4EysiWnog/OwFj6CdTAH/fFfWA/zsD4exgb4GTbEE9gIT+E9qFwPNMGq2Aw9sCXWxECsha2wDrbBhhiETbAtNsP22A47YCfshN2wM8r9WuszAlwnOt6vTZPj4xysj+nYDBdgP8zAwbgIY/BBXIiL8VFcgk/jUnwel0m7XI6f4yr8DldjZclf2RqzsD2uxT64CSfgZpyPW3AzbsVsfArfx6fxG3welfOnf2En3IOhuBejcD/OwRfxVXwZ8/EVLMRX8RoeQA/WyUGsi69hJ3wdQ/ENTMA8NOPbuArz8RF8DzfjEe34Js8hYKTB8a2FvG+2xG7YGidgG+2+jjxjgHVlevv7Ouw7ts/bZLyWBvtpC7kf2xKbYCBap8uT6RoYTNdG7t8HoT+2tZuuSKZrazDdPVJeEwzEpsh3aZaYO9NE29xE5BFuvMbjTsXzYWq5MLNmO+bD3DabvwmjvJhFDK80xzE/Ztgc4xyZpjn6PJk1+jMe0Z04OIe6E+oJu+TN9OP3ZsRuZRx0lj8zc64+h+a2ufo8mvn8XUi4pTMd0Y+IJPS5NTHdMb9mTrotx2YR67B4ns2L6fpcmzXmse4J+5yb4fydQBjl3sxg+FXMxuI5OPPmlZyHsxIN4/g843ycbvMpA4MxnIgjrvL3UnSWo3PnfFuezqPzbbk6LyrTYxpRYwHlEfZ5O7sv0OfunLjAWf5Ofe7OTYy3m7DP4RnAMuUvsOXyLFzgmM/TPYNtjgG4EncSwfx+GCdiEfoPZ7xi+T0zM1zL8dmY6ECEEblM47mQOhP2+T7DF9pyfqYtdMz7uQX74f6Ft5f/89hChxyghvk/ry50PQeo/yJbHtDgRbZcoKZFzI9ozO870SgvaMGi288NmvAg9caVmI6H0T5P6AX+5iJcyxfaONOWMzQ00zFvaEKmLXdoJr9f5/ccPEr4TWBbon0uUffFtAMiZgLjc8IRvtgxt6iZYadxE9rnGN29mPlgMO3SIdfoYgInKgdoYidxnLhKBDZhfCKDyCFOE+5NGU70IyKJDGIbcZi4QFRtxutEOGEi1hP7idOE8iUuAUR3YhyRRqwndhNHiSKiBm9MwcREIpPYSRQQF4lKvFk1JsIIE7GeyCUKCfdAXiNCiAQii8glzhHXCb9Wd3KO3vm583Pnp/jP/yr/X1RKYtu/J//f7Jq873blHp2aRmhk/5Ej7x02NKL3yKFteZZ+ZoSZ+1Rqnr6NLIn03+V+ljyHIctakZjHfAJ4MImXHGYUby4535QPdVnFPLK6K3VJSOK5fabTPbvMdZBx7qGgM/907iHJtSWH/abSB7ghbqDO2ZbyY9rFR9gtuyv9uMp7rfpGyzWl9a1Yxzx53ljrV9Dc8qy6ydo3wITe1jpONTOK7bn2Xp76fouh2MwyvfYs/SOW+afY8lah9J2xDuugrQfzDFOCPqdGXDlbrht/Iph4jHl6XnBcD9IGXH7WepPdsgdryx6faLeMaLx9JpaXPrfynGU/3ML8Ii31im8X47h9css4qZOUl8frvYrVQWmHh71km1j7zzMsSR2PnASxaXRcj4+eLq81xm2WvhbxJjp9qGnRrH2stOlS4mOkU3Y9Zbtrw008rR4fQ98ppVtLXHyiWZ0uj/GS7OZprccm2/ySTRGpJH6y5KvysO9HJfkFirR5zIhKMVOv6bGzrW3suG3+HC6ogF1bWWJtP1LX4OLLHpeUYlaKlTpVstUpNiUlPimR2VnrG4CErRxZOcprGYbrQN8WC2Wbtyd8idbEVuqXcdG6zW+/LT6ib4uyzZNSzW76OmySHHyLiAbEPCKbafMuajkjrAs=
*/