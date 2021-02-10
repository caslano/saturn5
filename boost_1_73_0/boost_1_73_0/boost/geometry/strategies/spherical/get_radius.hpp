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
sVHiZZGA4nTjJYsJG7MPHiWCqT7Q7ZOG/dfL3pHLpUm0QPMGK9X94cVgRA81t9zd4QL+vo4nY2+R4rf2A1wS4x1gzeQqy25etBRlkwjkInSBkKMOhLQ1BVPwJSAhBREZJFcGL0iBAVlOMS5CXGfiwDi7HI7UCJnDaZl4h2tAgW7nfafXD9SkaDZSGwNqIz6HR2785/CE82Mow0aTYy6H3XH/PfLyFwwmJnnZfFw8Q0D9k95gOOKssabKCACnExHz9xk26Hsi7WC9DBBEdyyJcLYP/gYcGuQ7dK+k0zu9H3SbJcmFBRqEvw0twxHJM6sanMh8+r7kj+2JMQtDIzkDBygU3npAezwB1TmthGoGmKeYosohJbd4eGuynsUqVTLACc4kB03a9ArI8joEqt+SRstbziRIisBhYSHxlJTFBRubfA5uMURKh7FJEpZAkjuclHYTTLv/QunoDShJvJZ20DEm6pCCBcJVuk6YSgviJGnyj2iVSvAPExxnLcZn36gNM66QfUHRlqdhIPXevX0TvDigW6UGyodil7mJX402iglNHC2KIofhSSOQV0HVPe4RU0J1cRHlFBFCeUEam5CD0CjJvaxCLtIcI9Mm6wVqEoR95jnFHBzGnefHzinpmeTMY6E2ivJsjC/BHkBG
*/