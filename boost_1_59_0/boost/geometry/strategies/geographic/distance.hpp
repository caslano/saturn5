// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2016 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2018.
// Modifications copyright (c) 2014-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_HPP


#include <boost/geometry/core/coordinate_promotion.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/radius.hpp>

#include <boost/geometry/formulas/andoyer_inverse.hpp>
#include <boost/geometry/formulas/meridian_inverse.hpp>
#include <boost/geometry/formulas/flattening.hpp>

#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

#include <boost/geometry/geometries/point_xy.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace distance
{

/*!
\brief Distance calculation for geographic coordinates on a spheroid
\ingroup strategies
\tparam FormulaPolicy Formula used to calculate azimuths
\tparam Spheroid The spheroid model
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
\* [link geometry.reference.algorithms.distance.distance_3_with_strategy distance (with strategy)]
\* [link geometry.reference.srs.srs_spheroid srs::spheroid]
}
*/
template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class geographic
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

    typedef Spheroid model_type;

    inline geographic()
        : m_spheroid()
    {}

    explicit inline geographic(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    template <typename CT>
    static inline CT apply(CT lon1, CT lat1, CT lon2, CT lat2,
                           Spheroid const& spheroid)
    {
        typedef typename formula::meridian_inverse
                <
                CT, strategy::default_order<FormulaPolicy>::value
                > meridian_inverse;

        typename meridian_inverse::result res =
                 meridian_inverse::apply(lon1, lat1, lon2, lat2, spheroid);

        if (res.meridian)
        {
            return res.distance;
        }

        return FormulaPolicy::template inverse
                <
                    CT, true, false, false, false, false
                >::apply(lon1, lat1, lon2, lat2, spheroid).distance;
    }

    template <typename Point1, typename Point2>
    inline typename calculation_type<Point1, Point2>::type
    apply(Point1 const& point1, Point2 const& point2) const
    {
        typedef typename calculation_type<Point1, Point2>::type CT;

        CT lon1 = get_as_radian<0>(point1);
        CT lat1 = get_as_radian<1>(point1);
        CT lon2 = get_as_radian<0>(point2);
        CT lat2 = get_as_radian<1>(point2);

        return apply(lon1, lat1, lon2, lat2, m_spheroid);
    }

    inline Spheroid const& model() const
    {
        return m_spheroid;
    }

private :
    Spheroid m_spheroid;
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template
<
    typename FormulaPolicy,
    typename Spheroid,
    typename CalculationType
>
struct tag<geographic<FormulaPolicy, Spheroid, CalculationType> >
{
    typedef strategy_tag_distance_point_point type;
};


template
<
    typename FormulaPolicy,
    typename Spheroid,
    typename CalculationType,
    typename P1,
    typename P2
>
struct return_type<geographic<FormulaPolicy, Spheroid, CalculationType>, P1, P2>
    : geographic<FormulaPolicy, Spheroid, CalculationType>::template calculation_type<P1, P2>
{};


template
<
    typename FormulaPolicy,
    typename Spheroid,
    typename CalculationType
>
struct comparable_type<geographic<FormulaPolicy, Spheroid, CalculationType> >
{
    typedef geographic<FormulaPolicy, Spheroid, CalculationType> type;
};


template
<
    typename FormulaPolicy,
    typename Spheroid,
    typename CalculationType
>
struct get_comparable<geographic<FormulaPolicy, Spheroid, CalculationType> >
{
    static inline geographic<FormulaPolicy, Spheroid, CalculationType>
        apply(geographic<FormulaPolicy, Spheroid, CalculationType> const& input)
    {
        return input;
    }
};

template
<
    typename FormulaPolicy,
    typename Spheroid,
    typename CalculationType,
    typename P1,
    typename P2
>
struct result_from_distance<geographic<FormulaPolicy, Spheroid, CalculationType>, P1, P2>
{
    template <typename T>
    static inline typename return_type<geographic<FormulaPolicy, Spheroid, CalculationType>, P1, P2>::type
        apply(geographic<FormulaPolicy, Spheroid, CalculationType> const& , T const& value)
    {
        return value;
    }
};


template <typename Point1, typename Point2>
struct default_strategy<point_tag, point_tag, Point1, Point2, geographic_tag, geographic_tag>
{
    typedef strategy::distance::geographic
                <
                    strategy::andoyer,
                    srs::spheroid
                        <
                            typename select_coordinate_type<Point1, Point2>::type
                        >
                > type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_HPP

/* distance.hpp
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
*/