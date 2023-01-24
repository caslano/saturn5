// Boost.Geometry

// Copyright (c) 2016 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_GNOMONIC_SPHEROID_HPP
#define BOOST_GEOMETRY_FORMULAS_GNOMONIC_SPHEROID_HPP


#include <boost/geometry/core/radius.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/math.hpp>

#include <boost/geometry/formulas/andoyer_inverse.hpp>
#include <boost/geometry/formulas/flattening.hpp>
#include <boost/geometry/formulas/thomas_inverse.hpp>
#include <boost/geometry/formulas/vincenty_direct.hpp>
#include <boost/geometry/formulas/vincenty_inverse.hpp>


namespace boost { namespace geometry { namespace formula
{

/*!
\brief Gnomonic projection on spheroid (ellipsoid of revolution).
\author See
- Charles F.F Karney, Algorithms for geodesics, 2011
https://arxiv.org/pdf/1109.4448.pdf
*/
template <
    typename CT,
    template <typename, bool, bool, bool, bool ,bool> class Inverse,
    template <typename, bool, bool, bool, bool> class Direct
>
class gnomonic_spheroid
{
    typedef Inverse<CT, false, true, true, true, true> inverse_type;
    typedef typename inverse_type::result_type inverse_result;

    typedef Direct<CT, false, false, true, true> direct_quantities_type;
    typedef Direct<CT, true, false, false, false> direct_coordinates_type;
    typedef typename direct_coordinates_type::result_type direct_result;

public:
    template <typename Spheroid>
    static inline bool forward(CT const& lon0, CT const& lat0,
                               CT const& lon, CT const& lat,
                               CT & x, CT & y,
                               Spheroid const& spheroid)
    {
        inverse_result i_res = inverse_type::apply(lon0, lat0, lon, lat, spheroid);
        CT const& m = i_res.reduced_length;
        CT const& M = i_res.geodesic_scale;

        if (math::smaller_or_equals(M, CT(0)))
        {
            return false;
        }

        CT rho = m / M;
        x = sin(i_res.azimuth) * rho;
        y = cos(i_res.azimuth) * rho;
        
        return true;
    }

    template <typename Spheroid>
    static inline bool inverse(CT const& lon0, CT const& lat0,
                               CT const& x, CT const& y,
                               CT & lon, CT & lat,
                               Spheroid const& spheroid)
    {
        CT const a = get_radius<0>(spheroid);
        CT const ds_threshold = a * std::numeric_limits<CT>::epsilon(); // TODO: 0 for non-fundamental type
        
        CT const azimuth = atan2(x, y);
        CT const rho = math::sqrt(math::sqr(x) + math::sqr(y)); // use hypot?
        CT distance = a * atan(rho / a);

        bool found = false;
        for (int i = 0 ; i < 10 ; ++i)
        {
            direct_result d_res = direct_quantities_type::apply(lon0, lat0, distance, azimuth, spheroid);
            CT const& m = d_res.reduced_length;
            CT const& M = d_res.geodesic_scale;

            if (math::smaller_or_equals(M, CT(0)))
            {
                // found = false;
                return found;
            }
            
            CT const drho = m / M - rho; // rho = m / M
            CT const ds = drho * math::sqr(M); // drho/ds = 1/M^2
            distance -= ds;

            // ds_threshold may be 0
            if (math::abs(ds) <= ds_threshold)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            direct_result d_res = direct_coordinates_type::apply(lon0, lat0, distance, azimuth, spheroid);
            lon = d_res.lon2;
            lat = d_res.lat2;
        }

        return found;
    }
};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_GNOMONIC_SPHEROID_HPP

/* gnomonic_spheroid.hpp
48fvWF2q8nMmAInkBaH/olzIyZ3ryKH1i0nEkpmS8Y/vCis9PsuEWn50C8whpVn/i11C5Ia/ic8d5CEc5pDr509S2edj21aS8f2/Q/wdUvBP7dn0r+EDH7YvnUMe374GeUig94YAXxI2usT9W/9FfEJ2whzy7vVLKosE+JKx0f0erefOA5dFpXKo+aJ5B/sX3h/id5iUT5m86e4V/mTtvImIXypsdOcP7iBnIQ+/Hwgnifu2ktN7N5GTURtJwu4NVK4qPmINObp9NTkC9Rq7NZQc2hxCYjYuIwc2BBO837QXxu8omEMAv0Ts/63vwZYG84lrvVbNG5OvGlmRhg3qkS/rfEYsalYnNatVkfQdAOPjuHTmzGkyBtb0TNbpEZVXr1mtcol7dro+hjmpbdu2JGLHNrr+C/GbRdcbmA+Ul9NH4vjoVqxYQSytLMm8Ob70y1cBzJdf1KnN9tG4X0g7z/ZtsHfVFx/dkuAlpIJJBRof22Ij2AfS+wZ35Owu2PUkug/XF3/1ypWkW7dupIFlAxofx6qvGluSo4NbkN3fN6P3q3Dtjvs3Q/jartVXjdm9OJQ3h7VWDuyB3sGeXDt+cYT4kf0RvxHFRzlFcXyxOxW1QX3vh647cC3O5dfyYS+ghPUGyr0bin/2wBa6l8F5Dee0cyNasvL3b0rW8/LnZz0wGP/CoR0a4wKb+/PU8nx4jw7bhaH4Kpm8Inxb
*/