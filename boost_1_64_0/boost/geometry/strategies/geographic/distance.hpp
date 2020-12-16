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
#include <boost/geometry/util/promote_floating_point.hpp>
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
dMaOeANTCMuzBSjzVcRYmc+N/LthDayPNbE71sJgrI1jsC5GYD2MQw+cgw3wKWyIG7ExbsUmKO0vea6AddJpf22Q8+lL6IYbsTb+C1vhJuyJm7EXbsEbuIm4LssdIscJU7k8Z32vhtT/vdgaX8cB+AY+jG/iE7gfV+IB3Itv4Vt4GN/Ft/EcHsHf8B2sQ3pHsR6+i+3wGPrjezgA38eH8ANbOfAcgP1y2C7l8Aq6YQbWxh3YCndiT9yFvXC3chyQe/cwXec4UMmRcsDK2Aid0AudsSe6YAxWQyNWxylYD6eiByrXISSdlkSw6joE6ZWyfe+ifK+zzvUKXoUi35P70Fi/kOWF7ilaumuL+L2L8r3m9r/HeUjuhWJVnfPQMb7njsexEZ5AbzyJffB9HIkf4GN4Cmfjh/gsnsYtmImv4xk8iGfxQ8zBbPwYP8NcvIbn0ZSpT7AUXsAKeBEr46e29WTBtvJlWar1DMizHTKK+D3uMyrle9NR/T2OeVLP5T4gTtWp57fluPoHBqJDGeofOKIRS2EClsYkLIPyninrvT7uAWrfM9WQeuqKTbEeNsOW2AJ7Ykv0xzY4AtviRGyP87AjpmMn3IRdcBd2xYPoie+hF+ZiN/wKu+OP2APLkrme6IIPYh30xjbog93RF/tgLxyJfhiB/hiPvTEV++Bi7IvpGIAbsR/uwv54AAfgcQzEE/gQXseBeAsHoSNlFIZVcBzWxnD0wChsj9HYD2MwGMfjBJyAMzEWn8GJuAPj8DAa8TxOwq8wAe/jxJSELXEydsYp2AMfx8E4A5NxJs7AWTgX5+BynIuv4nzMwQX4OS7Eq7gEf8Wl2LAM5xjsgMtwBC7HUFyBUbgKY/BpTMbVOBefxS34HO7GNfgmvoA/4FosR31bh274IjbG9dgJN+IA/BdG4GaMwS1y3FxbSrlny71cS70dzH+vRNPngKl+4CHsiofRG9/GvngUR+G7GIbHcR6+h7vxJO7D9/EQfohvYya+h1l4Es/iR3gO7yczF7EWfopt8TMcipcwGC9jOH6J0/EKrsevcCt+ja/it3gKr2E2fod/4A/YlnX8EbviT7gUf8Wn8Ra+jaVLUX+xDGZiBfwOnbEi29cFndENa2INrIt1MAEb4BRsjGuwHR7CDvhv7IjvYxf8FLvhNeyOv2MPfJTt3BMX4IO4F33wC/TFH7EX/oq90b0s+yf2wr7YD/vhOByAUTgIp+JgXIFDcA8OxQ9wGJ7F4ZiLI/ATHIk3cRTewjHYhHrzCHbDEByIoTgJwzAFIzAVDbgQo3AZxuJ6jMctaMRdmICvYqKcLzxLyf1lue9MPTUfs1uh6ZMg1x2SsQNOxm44Bb1xKg6T8SMjcCYm4Wycg3NwJc7FDTgPd+MCPIJPYiYuxu8wDf/EZViFTK3AuvgUtsVV+CA+jX74DA7B1RiOz2ECrsGl+Dw+jy/genwRd+J6zMUN+DW+hNdxE/6Jm7E5ZbAFPXEr9sQMDMQdGIM7MQV34eP4Gm7Cvfgyvon7cB9exv34Ex7AW3gY7y/Nfo/eeBQH4rs4FP+N4/A4puNJ/Be+j9vwNO7Cj/ArzMKbeAZv4Vm8jdn4ANs3B2vjeWyBn+AwvIDheBEN+AXG4peYhldwNX6Fz+FV5feJ3PPHBgQf1e8TV7ke6oZ1sAZa2q9y3x636bRfs6U9nIO98BMcjhcwCi/iZPwUn8DPcA1+jv/CL9CnbNHeU1fQmI5zcv7acR2b9eZ7RA9iJZF6h+M6bsj53xrbMdTN8S8f3/FIjnqMxyQ3xzse59Heu+8WuTkWOtZjJ6KRzliPGW6OJeM9/jfHe6T8j+AVLM/DXo0IfyKaSCN2E7mEQ00=
*/