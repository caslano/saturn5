// Boost.Geometry - gis-projections (based on PROJ4)

// Copyright (c) 2008-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018, 2019.
// Modifications copyright (c) 2017-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Boost.Geometry by Barend Gehrels

// Last updated version of proj: 5.0.0

// Original copyright notice:

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef BOOST_GEOMETRY_PROJECTIONS_EQDC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_EQDC_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_mlfn.hpp>
#include <boost/geometry/srs/projections/impl/pj_msfn.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/math/special_functions/hypot.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace eqdc
    {

            static const double epsilon10 = 1.e-10;

            template <typename T>
            struct par_eqdc
            {
                T    phi1;
                T    phi2;
                T    n;
                T    rho0;
                T    c;
                detail::en<T> en;
                bool ellips;
            };

            template <typename T, typename Parameters>
            struct base_eqdc_ellipsoid
            {
                par_eqdc<T> m_proj_parm;

                // FORWARD(e_forward)  sphere & ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T rho = 0.0;

                    rho = this->m_proj_parm.c - (this->m_proj_parm.ellips ? pj_mlfn(lp_lat, sin(lp_lat),
                        cos(lp_lat), this->m_proj_parm.en) : lp_lat);
                    xy_x = rho * sin( lp_lon *= this->m_proj_parm.n );
                    xy_y = this->m_proj_parm.rho0 - rho * cos(lp_lon);
                }

                // INVERSE(e_inverse)  sphere & ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    static T const half_pi = detail::half_pi<T>();

                    T rho = 0.0;

                    if ((rho = boost::math::hypot(xy_x, xy_y = this->m_proj_parm.rho0 - xy_y)) != 0.0 ) {
                        if (this->m_proj_parm.n < 0.) {
                            rho = -rho;
                            xy_x = -xy_x;
                            xy_y = -xy_y;
                        }
                        lp_lat = this->m_proj_parm.c - rho;
                        if (this->m_proj_parm.ellips)
                            lp_lat = pj_inv_mlfn(lp_lat, par.es, this->m_proj_parm.en);
                        lp_lon = atan2(xy_x, xy_y) / this->m_proj_parm.n;
                    } else {
                        lp_lon = 0.;
                        lp_lat = this->m_proj_parm.n > 0. ? half_pi : -half_pi;
                    }
                }

                static inline std::string get_name()
                {
                    return "eqdc_ellipsoid";
                }

            };

            // Equidistant Conic
            template <typename Params, typename Parameters, typename T>
            inline void setup_eqdc(Params const& params, Parameters& par, par_eqdc<T>& proj_parm)
            {
                T cosphi, sinphi;
                int secant;

                proj_parm.phi1 = pj_get_param_r<T, srs::spar::lat_1>(params, "lat_1", srs::dpar::lat_1);
                proj_parm.phi2 = pj_get_param_r<T, srs::spar::lat_2>(params, "lat_2", srs::dpar::lat_2);

                if (fabs(proj_parm.phi1 + proj_parm.phi2) < epsilon10)
                    BOOST_THROW_EXCEPTION( projection_exception(error_conic_lat_equal) );

                proj_parm.en = pj_enfn<T>(par.es);

                proj_parm.n = sinphi = sin(proj_parm.phi1);
                cosphi = cos(proj_parm.phi1);
                secant = fabs(proj_parm.phi1 - proj_parm.phi2) >= epsilon10;
                if( (proj_parm.ellips = (par.es > 0.)) ) {
                    double ml1, m1;

                    m1 = pj_msfn(sinphi, cosphi, par.es);
                    ml1 = pj_mlfn(proj_parm.phi1, sinphi, cosphi, proj_parm.en);
                    if (secant) { /* secant cone */
                        sinphi = sin(proj_parm.phi2);
                        cosphi = cos(proj_parm.phi2);
                        proj_parm.n = (m1 - pj_msfn(sinphi, cosphi, par.es)) /
                            (pj_mlfn(proj_parm.phi2, sinphi, cosphi, proj_parm.en) - ml1);
                    }
                    proj_parm.c = ml1 + m1 / proj_parm.n;
                    proj_parm.rho0 = proj_parm.c - pj_mlfn(par.phi0, sin(par.phi0),
                        cos(par.phi0), proj_parm.en);
                } else {
                    if (secant)
                        proj_parm.n = (cosphi - cos(proj_parm.phi2)) / (proj_parm.phi2 - proj_parm.phi1);
                    proj_parm.c = proj_parm.phi1 + cos(proj_parm.phi1) / proj_parm.n;
                    proj_parm.rho0 = proj_parm.c - par.phi0;
                }
            }

    }} // namespace detail::eqdc
    #endif // doxygen

    /*!
        \brief Equidistant Conic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel (degrees)
         - lat_2: Latitude of second standard parallel (degrees)
        \par Example
        \image html ex_eqdc.gif
    */
    template <typename T, typename Parameters>
    struct eqdc_ellipsoid : public detail::eqdc::base_eqdc_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline eqdc_ellipsoid(Params const& params, Parameters const& par)
        {
            detail::eqdc::setup_eqdc(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_eqdc, eqdc_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(eqdc_entry, eqdc_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(eqdc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(eqdc, eqdc_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_EQDC_HPP


/* eqdc.hpp
4zEBEzEJkzEFUwP8mZPTMB0zMBOzMBtzMBfzMB8LsBCLsBhLsBTLsBwrAvyZ0SuxCquxBmuxDuuxARuxCZv/zuGt2Ibt2IGd2IXdf2f1XuzDfhzAQRzCYRzBURzDcZzASZzCaZzBWZzDeVzARVzCZVzBVVzDddzATdzCbdzBXdzDfTzAQzzCYzzBUzzDc7z4u2f1Eq/wGm/wFu/wHh/wEZ/wGV/wFd/wHT/wE78QICA/BEJgBEFQBENwhEBIhEJohEFYhEN4RMBSLMNyrMAB7MU+8LkHMzMz+4cd8l5sZmZmZmZmZmZmZmZmZmb23/cbUEsDBBQAAAAIAEKxvEqvib9tx5sCAACQCQATAAAAYmluNjQvbGlic3NsTURkLmRsbOxdCXhURRJ+M7kmIWECBIhyGDBoFIRoWA2nEwnrAFEjl1ERQUCDckSYYBY5EhM0cUBZRUVRFzkUFQFRMQmsJIImKAoeq3iziDLD4IqAGhWY/auv997MBAZ01z14X/Jed1V1dXV3dfXdc9k187UITdMi8e/3a1qlxh+HFsZj0bSmZ1Q31V6MfatDpSXnrQ5D88dPTSmYMvmmKaMnpowZPWnSZFfKDeNSphROShk/KSX7iiEpEyePHdc1ISEuVbDot7Jbz5i3ssbL/07POfKj8F0gvjfPl/5L8iPZNzs/nn375yfgu2GlA3AK6xj/+Vby989PYfCs/Gj2fWU8//Zj/sHjx+RTPDIJuf01beydNq1D785XS9h+rWNKE2vTOC0nRtOcVgZbfQZeicxZbNGEG6hoESZaBY7lmcnQoywikPqY/bpzzbU27ek+cI+J1cYSsCZWeziakLHahAxDnm+P1UbEa1pKqk3LPEbRjAJ+sRGQG6sltmicvqtrXJELX5bmRPGNNNOkgG3XKWNHu0Zr2tU9LPCBpie+ufgaHgf+unIy7Tt6LbZp2jX43m0LpKvpWsAJX+zB0gp++O62BfMbz+mic3latMH4to8NpktPH3PjTZrWxkKZCjwVX0EIuilTp4yBm+VxDfAU5ZRQdOMmTAbhhUk877VW+E4PortE+y99ttLj/bpjtOYtSYzSvHNRC7x3dYjQvIOfxuuze6yaN38NXv36w/v4F6DrMQiu1J9Bt+1lvHp+C2zLKiAcT8D1yVsWzRu9G94rD+KVsx6vmAQgmk9GsL9OxavoQ5BMLUTYrl/A5c0ENtsLxBUfR2revbOBaEmR7/wGrzan4dXqMEhK5gFxOBXeu1rBO/h1hD3PB2/yBCD6nQHXKiKObYJ0dF8Mkm3XwnsNyTduA8RIvxB0vn/AeyNx/m4SvDlV8MYQ1mqJAb99QHh+hncq5UbfGSAZcA1eridIvgtAfO5f8Oq/Gt70w3hd+yO8rVLgKnkYwbpQYs52IGzzH+FN+B6v/FWADWkJ2KRv4K04AsFTXyX51sF7N8Uxh2LbTln8y1Hitx6w2lLQxRODq9oBcYcHiD7b4Kr8BbAWDyKv2q+g9A7DK4kk8FNm710Juj+cDqzjUXh73QouD04Hvye2w7vySdBd+gBg1mrQTXwNrszLgRhC+TJyOYI9/DeQRB5GCPt2vH7+GCTjNsJV0BwI32Z4L/wrvB2IVdtNCPbQK4DdsQZcjiyCq5KYRlCUj/8A19Mu0B26G3TXt8dr+gYk9fu9lH+U47cXwvXk+6CzvAlsl+6Uf/PhXfs+EBMpjswLEOLLK8F+Vlt4q4hzmRfeKyZHQr5EvFq2AaKGVOD2p8BgnQ2u87ci2Fbynj0b3imj4TpCSdjxAVybDoDB51Sg3jMB230tvH5Ss4E9Efnyrohj+83g3KQdYMOHA/bEtyA5/BK8V1XDdR/F8dy1oKsvwis=
*/