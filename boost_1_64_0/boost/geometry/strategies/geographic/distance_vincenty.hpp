// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_VINCENTY_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_VINCENTY_HPP


#include <boost/geometry/strategies/geographic/distance.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace distance
{

/*!
\brief Distance calculation formulae on latlong coordinates, after Vincenty, 1975
\ingroup distance
\tparam Spheroid The reference spheroid model
\tparam CalculationType \tparam_calculation
\author See
    - http://www.ngs.noaa.gov/PUBS_LIB/inverse.pdf
    - http://www.icsm.gov.au/gda/gdav2.3.pdf
\author Adapted from various implementations to get it close to the original document
    - http://www.movable-type.co.uk/scripts/LatLongVincenty.html
    - http://exogen.case.edu/projects/geopy/source/geopy.distance.html
    - http://futureboy.homeip.net/fsp/colorize.fsp?fileName=navigation.frink

*/
template
<
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class vincenty
    : public strategy::distance::geographic
        <
            strategy::vincenty, Spheroid, CalculationType
        >
{
    typedef strategy::distance::geographic
        <
            strategy::vincenty, Spheroid, CalculationType
        > base_type;

public:
    inline vincenty()
        : base_type()
    {}

    explicit inline vincenty(Spheroid const& spheroid)
        : base_type(spheroid)
    {}
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename Spheroid, typename CalculationType>
struct tag<vincenty<Spheroid, CalculationType> >
{
    typedef strategy_tag_distance_point_point type;
};


template <typename Spheroid, typename CalculationType, typename P1, typename P2>
struct return_type<vincenty<Spheroid, CalculationType>, P1, P2>
    : vincenty<Spheroid, CalculationType>::template calculation_type<P1, P2>
{};


template <typename Spheroid, typename CalculationType>
struct comparable_type<vincenty<Spheroid, CalculationType> >
{
    typedef vincenty<Spheroid, CalculationType> type;
};


template <typename Spheroid, typename CalculationType>
struct get_comparable<vincenty<Spheroid, CalculationType> >
{
    static inline vincenty<Spheroid, CalculationType> apply(vincenty<Spheroid, CalculationType> const& input)
    {
        return input;
    }
};

template <typename Spheroid, typename CalculationType, typename P1, typename P2>
struct result_from_distance<vincenty<Spheroid, CalculationType>, P1, P2 >
{
    template <typename T>
    static inline typename return_type<vincenty<Spheroid, CalculationType>, P1, P2>::type
        apply(vincenty<Spheroid, CalculationType> const& , T const& value)
    {
        return value;
    }
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


// We might add a vincenty-like strategy also for point-segment distance, but to calculate the projected point is not trivial



}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_VINCENTY_HPP

/* distance_vincenty.hpp
8B4F8DvVROZWarINktkKc8xInIbjAVa/HScCOAK4WaIg0Y30BJCot3j+VJXrhwpoXW3DOHkr6M7qLJ1RbvrOxvhMyd/6g6nyBzBYUwvAX8sFeImm9t1HnhC7JjabW3hflOuqjnPe0dChkcR7OXATVtGsYk+qaC+uxbh8CrnJMlLSB5kKbTqXfGrDy4ylgHmR56uWzz+K4t6rp2UouUxRm1EvyG2hRKRchFvtkfJDsswOY4xjnkIAhWdtwEAAp0w09sQ5ZB5dPgj2Sl2vySJbQpUVurhanoqVlLwZkmllbXcRek+0ujl2EGKBo3KTTuFzIwS/yF1GjVaY2ijZQghFWcnSXJmgPmv4hIuS8VFFi2cOyliCmVgJ53S2bDOfc//TdU6Cy0JvUo/YXLwmzRAMabg9qOjT29S+fKPxLw133C8TNSh+gx2Gr583UB9BNWleOCc9tAzNtjqh4XcZxmdo8MFdZnOpMYwOXjoe8+6KF6HI/uxWC8unRRr5ifmRyaysL/HK4K7lB9prXe14kodZ/CIDPRNkVM7vAlkHo+vP76BmmNdIXuVsyGdM2A==
*/