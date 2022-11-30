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
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
*/