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
Ry0GKNeCQDhQh3YeN13GOINZeAOF3RMz9fgp8G2euVeSBdE1uj5hPk/JBrMplHPlQ5KitrQRbrwvyaZcvxIP3mljbXNipk4b3af84qqeSth5VCxuY/G/YLdOmIYDIkVz5GYAXQ3pSyaYouDQIEmWriWl65kLFoN/YQlyMRn1kuMKJTPNrb+gqydah5HiKWI/E7W2aL1lI5g73+w/1u7MU2Q/cCQ4Tza1kF1R5TMNvmsFa3o8no8PCRAsGU5QKbnmmcvGLRnriho7G8xO/pmo5iOohe/zZgt9kE+GOUSkLPvnulTi38DOsrGpsXsrEx6Q5Qx5RsKFQ3esYxDr+O8QhaabFEb5a2mDZAn6buXIbdsU5kslBZTD59vfFjM6Dpf4qGODGD+NpoIoPaTl/Kll9TVix9InISO/+3v8L4oFUAFwdJwQblxE24MuyYQitebpdpd8BR/pno8wvViEseEaFHA68AK98fkW4NluGzGBwNtxQIlNXxiNczypLlQUWGWfP8zVxXITvJGiAJ/PYRbwz/k3zrMEva/QPk2exzuBjRCqmE8c/W48XuadyA==
*/