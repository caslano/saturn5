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
6+wly2g6lnbXWY5zlqiTZr6Wyxul+rGxU6+Tbws/1GfytcJb661mv8R68eQ0L18YzAtq0hw77qk98Md0r9T59+k+qfm1RjuYHT6YXAWSu8M6r9R4KO2K/tF2q8v8reaAxIJrsYMfhBYvc6hvJT1LHEtzXfpzwE8lZtP3petVVPfmMd6vpH03oxvY2wTcLqNV9h29Ipsv+bISSvuGJnNRQyPzZ6W6xXhu2v5DXayfOcXzB2a99N+SjnAuv8KhzK9cTx+/vsTJpxE3TWh+afPy9JXFSv1UX5GHXuXTK0dtsXzWVM8Y12pTLz5cU+r7hndVRV0VURMgM6N5H095Vyr1Y86SM51rhd5zuLjziVSaRt61U2f09fdSZyv425apMxn0+hk/Sc91ZTJXvrOZ33zW5p9ZzevmmXPXu4NFfAUsMN8hn8u4yB1cv62Bd8xSwlXdNDd1Ulq/mo2f4VYu0qXf95C1JFi3qsKv+29VvS+o/5LAw9pXZLxdrpbVs8Cnf9ZXCX1lozcQbKyo2+C7hhhntM/d4ONNoLrOXV3QVOX26+Q8L+gmd68u5WteztZlWWW+GjgD9VX8oqxumVvqDmwh4oNucTFLW9Y0yEl9YLVbxxoX3Q3cplZYLyXEtjndAR3nFb4qasFulNzfemzua6rV29O8pR69oONU41Nbb0XD0QY7bU6+t6GikjMjcZG3MlAR2Eaf1TWoCosexN6KOobk+iK+9BWSQl1DafPdlY21te5AspSPGfkHK2g4/xo+X16mtmrPWmNLWmi0zmVKXVJQUlxQdNYSo4PVcqV/dCfA1QVamb8/qoYg3who2fOV/CSvPqiV/iCuztPKuJqlXC6mCr+7Si82LrP98Z+OvyFo/jUR4zsqMU+O9dvMD5Vq46qSDcWla9YWLF7qMEvhUMZbz7Kl6jb9bJ9+5FvV1cY35Hcq/QXDV8/fX1bG10qjPEvRJDROSlVFpU65TBmrBd3CL8Mp7XKrC0nt9ug3Exwu/chspeetGm+tMaNUEKbX6O3hVn7b4c5kgycvsT5v9QbqfVtoZp49JUU9fyOFSTaou0+3J1utWm8Dz5Erqb3huxRTMVum4LSbTqMsgWDy4+rbk2euqxu9zCSGU52M11S1KpiMXVXh9y7a0rCIIbKIexbpNlxUt3jR4kXSrtOum996/1aKxqC3jg1dWpLpKfjZbfpjZo/ZY/aYPWaP2eMfOY57owrNSTtfcJo+nz3+P485ysZ/s5UKTffrmHDM4D/OqlQhyv/1eSpoUbPH3z5oo6WKXbhar1z8t0CVoNaodaqY8zX8dzVaH1+1/vpV2tf4k8l5khdKPlYsY1reh3DMIT9+61Je5WO3uhrWKbdaw1mNqidNzEjjUEuxcw1WKgf+7WoR/lWk2aL8qoL02yhNBWduI+9S5UHZKZ0f+tR6/hRx7lQB7rkSXxXPXYjHA4OkOk99gD/XGH/OVPVyXwN/6vQ599VyXRmt8RaenSxrPtZAbgHO/eTkJa1PJ5v+bFJ5KGEAXzVndaSs5AwPZefgKfPS8t2IBbgnld9iUmDUv8Y4X6KOI71uq6BOCyu4M9UKxhOkBmsppz5WqtdzzzqjtLWYeU/ymZzNfC9PrUaZ+/dCdSJ5GC2Jt1G35N/V9qWkryePq8g7aJR/3jH5TKn1DHWO8O45h9zclF6XfJXRU9ukPh6d7ww+O3mcy59ctYinOjhbhu+1yrmCsgS5Vm+U5EzDQ91hKscG48wN3XCr7lNSKqOV51ALenWGaGa9Ulajheh3vLQuTIsZ5qeYVc0es8fsMfNhn6uK5ijVHA1HW6KRaCw6HI1HR6L2npweR09uT15PYU9Zj6enqSfUE+5p6Yk=
*/