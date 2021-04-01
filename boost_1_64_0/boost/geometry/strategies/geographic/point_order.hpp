// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_POINT_ORDER_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_POINT_ORDER_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/point_order.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace point_order
{

template
    <
        typename FormulaPolicy = strategy::andoyer,
        typename Spheroid = srs::spheroid<double>,
        typename CalculationType = void
    >
struct geographic
{
    typedef azimuth_tag version_tag;

    template <typename Geometry>
    struct result_type
    {
        typedef typename geometry::select_calculation_type_alt
            <
                CalculationType, Geometry
            >::type type;
    };

    geographic()
    {}

    explicit geographic(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    template <typename Point>
    inline bool apply(Point const& p1, Point const& p2,
                      typename result_type<Point>::type & azi,
                      typename result_type<Point>::type & razi) const
    {
        typedef typename result_type<Point>::type calc_t;

        if (equals_point_point(p1, p2))
        {
            return false;
        }

        formula::result_inverse<calc_t> res = FormulaPolicy::template inverse
            <
                calc_t, false, true, true, false, false
            >::apply(geometry::get_as_radian<0>(p1),
                     geometry::get_as_radian<1>(p1),
                     geometry::get_as_radian<0>(p2),
                     geometry::get_as_radian<1>(p2),
                     m_spheroid);

        azi = res.azimuth;
        razi = res.reverse_azimuth;

        return true;
    }

    template <typename Point>
    inline typename result_type<Point>::type
    apply(Point const& /*p0*/, Point const& /*p1*/, Point const& /*p2*/,
          typename result_type<Point>::type const& azi1,
          typename result_type<Point>::type const& azi2) const
    {
        // TODO: support poles
        return math::longitude_distance_signed<radian>(azi1, azi2);
    }

private:
    template <typename Point>
    static bool equals_point_point(Point const& p0, Point const& p1)
    {
        return strategy::within::spherical_point_point::apply(p0, p1);
    }

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

}} // namespace strategy::point_order

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_POINT_ORDER_HPP

/* point_order.hpp
pFp1/7nHI1T8fnmbxuCKQi0nueATr+SQH+4JvYEHwUgNVqYviq7wSbomGYg6oiWxW7ebATB0s8+wFasK7roKIBr5p56ji5IHXBB1H8fXHqZIi2oi86Fg+b6/2oq0A8S/BC7my1vt50dhvdvPOZ5Uc0hq+Dog25ANdqfJVzSzjkx5obHuQM4oTaOQTxvZEGrRU0w1B1wZpBiLpaUe6Z+IqTh3kmauSvTUnvFA/S7BAIYXFhd5cpXPLhWFVB1Q+DZemd1Wpz+6v1nnKyLo8fUzVx6FJQ0OfTxgp38osXNHvYICnMDNOskAeF2cQhhCuOhZX4cQ35+NoN0B+8ZbY0gs03Sy0fi8emHLCvTy5FKJxl/64Kg8NHajZpsXAkE38iNKz8ydXxaw+l0u8IbtftA67RmmDUXBHcfSe2Vba16pJm89lE/lAcq5e2PmFvoNAVfIhB0I5w8QrcFe0n09T3zaokmGs7rWfEPz8YorUJru7Bv7EcwS6jQsgdZBJU72SGEm56FhecLZbg5GE5v6+5EWqigJtaQf4/QkWE/BLYQw6YYtmuXw92xWPAllYg==
*/