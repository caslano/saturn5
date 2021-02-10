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
DpTIwqCkNNHlWlHP3h8+qsziPQqVZDe5iYtlRiYDL7vlRy4sczDFZfhICXFNhB7g1PqKh9aL902WH01X8s5c4Fjspdxm5NZlVjlpvLv46bRi2x+ZkmBTVJMtOvuYunFy3CkJL8433/m4Utudj6UNL4xnzjfYW63BXnmDCwO28w2CJnGQt+t0tgB1mJIvqMuFPFszuQhjauJA23rWaCtYBVuvTb3gZ+aRvf+6ZA34k3SXNHu6IQSMlOqYEGkA6u3jTPrHvN+j+P4Oc9e1WLrAmPCREEq5TudDhzgObBAIvSOrf9rwdZoDvroAj2iI0Y3vTN0hbaYnyZmsfFRWIl6tPLFx6IwlnfOwNzDJ0qgelpeL8uXS19UsVz3Gfnyeqf4cjrrFnTPLWQEJhRvLmYuB8LCDeQ9QGQsCJ6VHjIgzVshIWMqD+Iz4p7KfeAaKsa/qBCZPeLyVwDHH+qLXb5/2P4CC1/mkeTafKC1NyT+TQ3fsGinHMkk69EHqzGZCJntYceFk06I8w574+lUsSGCXKGILDtIRw5sjh7k+UwT4YgbKKqkT3VFqD8WsvNnjB7zTY4QEJ4SwQL8pHF/GM4NDKSMk45eZ9trgyr+yOMRq5pl4jv+MBI6FoIvomGGVNBn+kyJZYyMX3RO56G7I
*/