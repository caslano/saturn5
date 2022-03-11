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