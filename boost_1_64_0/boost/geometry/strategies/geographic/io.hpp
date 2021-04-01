// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_GEOGRAPHIC_IO_HPP
#define BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_GEOGRAPHIC_IO_HPP


#include <boost/geometry/strategies/io.hpp>

#include <boost/geometry/strategies/geographic/point_order.hpp>
#include <boost/geometry/strategies/geographic/point_in_poly_winding.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace io
{

template
    <
        typename FormulaPolicy = strategy::andoyer,
        typename Spheroid = srs::spheroid<double>,
        typename CalculationType = void
    >
struct geographic
{
    typedef strategy::point_order::geographic
        <
            FormulaPolicy,
            Spheroid,
            CalculationType
        > point_order_strategy_type;
    
    point_order_strategy_type get_point_order_strategy() const
    {
        return point_order_strategy_type(m_spheroid);
    }

    template <typename Geometry1, typename Geometry2>
    struct point_in_geometry_strategy
    {
        typedef strategy::within::geographic_winding
            <
                typename point_type<Geometry1>::type,
                typename point_type<Geometry2>::type,
                FormulaPolicy,
                Spheroid,
                CalculationType
            > type;
    };

    template <typename Geometry1, typename Geometry2>
    typename point_in_geometry_strategy<Geometry1, Geometry2>::type
        get_point_in_geometry_strategy() const
    {
        typedef typename point_in_geometry_strategy
            <
                Geometry1, Geometry2
            >::type strategy_type;
        return strategy_type(m_spheroid);
    }

    geographic()
    {}

    geographic(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

private:
    Spheroid m_spheroid;
};

namespace services
{

template <>
struct default_strategy<geographic_tag>
{
    typedef geographic<> type;
};

} // namespace services

}} // namespace strategy::io

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_GEOGRAPHIC_IO_HPP

/* io.hpp
wi9mtX62HM+TCtxi4o4Ur0R3NshbJyoPXPjri3C0k3AZ12mampcQvAoGIDPJyiIQw2mFtlT+MMbxIHz14uQOMGTot2jn0xGwzKnSfu5agyTfKLL4iYo3pIhlfZw7Q16UTmbks+RQ5hD8WSSwKmsDFT5DM4PotYHrm6n17o7U/0oUbGTRoFEyABCbOSot5inOZj5tI67M9Eag0f8mUsK2EPnNzvjAlCWGEdLymQQcLDnROKd8cZXk4rq1aeU6Pz7lPZ8LFeKarmXCzkQGO46qceFQUndsDQprJF5YibD5cHdh8yQzqjWXT8VlgIGQqYV4qybfP7sm+VZ/HD4BFaO7YfkqFJ/ASVQMZvQrkJiAoG/Wpl9jsxAwVjrzEzoMP6km1xe6Yz+PbduQUeS4vlVpv+deByBdhoG5x3abBy1/FAQs7huoHg5l7DkbSl0dQOiuO+bCjRpHY9zOc2lyg7r55Awn2Gt7Hu2UjT1DHNC7sRKBeZciPC0GriINCqwq8iWdTOMT9nqHOdmLkwgpQ5+AhJOh3a9akcAlWZNUPLQQbnLwGsrZ091VE2aTxw==
*/