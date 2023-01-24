// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2016-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_GET_RADIUS_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_GET_RADIUS_HPP


#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace strategy_detail
{

template
<
    typename RadiusTypeOrSphere,
    typename Tag = typename tag<RadiusTypeOrSphere>::type
>
struct get_radius
{
    typedef typename geometry::radius_type<RadiusTypeOrSphere>::type type;
    static type apply(RadiusTypeOrSphere const& sphere)
    {
        return geometry::get_radius<0>(sphere);
    }
};

template <typename RadiusTypeOrSphere>
struct get_radius<RadiusTypeOrSphere, void>
{
    typedef RadiusTypeOrSphere type;
    static type apply(RadiusTypeOrSphere const& radius)
    {
        return radius;
    }
};

// For backward compatibility
template <typename Point>
struct get_radius<Point, point_tag>
{
    typedef typename select_most_precise
        <
            typename coordinate_type<Point>::type,
            double
        >::type type;

    template <typename RadiusOrSphere>
    static typename get_radius<RadiusOrSphere>::type
        apply(RadiusOrSphere const& radius_or_sphere)
    {
        return get_radius<RadiusOrSphere>::apply(radius_or_sphere);
    }
};


} // namespace strategy_detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_GET_RADIUS_HPP

/* get_radius.hpp
eA/vCVECj8FZjelQDZqsMDfNnGGganPZBzOrw2ndDj6fGSUIRn+fqmKmq0VWt6W9Y/lPgtUEbEsS9id6mYxaU76sbiJZ/AlXQZnP+uDvHJiiQ76znQPD/cXlzP3DeQ5OcZO6WKxeXR2CZgMPEY0KmyKu2nMVqxip08Mg/5m/rqWkjaQJUHtxM8jb7hhiMuZaW/LxXE+eZiqKlZJIMJAMwMavbaUIO7HpeXYFHRLGR/Hzo9V7B07dHvmLdmzV4tZY3jfL0LvOyJulI6XGlhAPCuQ5U3lQsteYTfC1KtjEh/jV9J60LQcYtc9gdmjd/tYSINr010DgcpZSNHqVfWR+8GBKfweq+ZPYLo8702owTL1qjjbrWbCTn1A1VGFiUVohImuk+AYWUnm445piteyW7f6zTX1QYSJl1YfaWQuShS4rMxkbEaEi/RfKzrInDi4Nw6UUaKHA20JxKa6FAsUZoFDcvbgVt+JuL+7u7lDcXYrr4O4wMAw2+GAzs5ZsNpvNbvYPnJzknC9Xnuu+H4Y/Oj4DAVxb/GnpB5nTFRlnf0amzqaHks+bDHWWJCLoPwkJWVwX07t5rKCsr1WZdeK4125UABZqxN/aSHNmya2pg3oTr2S/OwuzskLYohy2/FQzO/l6OqiWRfI95Ep5PbCzNj9GS3In6Ca1Q79vkINRsqUyBks3tCx1avDBmpTAauFsJTin/NXbLLnGzMrr
*/