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

#ifndef BOOST_GEOMETRY_PROJECTIONS_OCEA_HPP
#define BOOST_GEOMETRY_PROJECTIONS_OCEA_HPP

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace ocea
    {
            template <typename T>
            struct par_ocea
            {
                T    rok;
                T    rtk;
                T    sinphi;
                T    cosphi;
                T    singam;
                T    cosgam;
            };

            template <typename T, typename Parameters>
            struct base_ocea_spheroid
            {
                par_ocea<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T pi = detail::pi<T>();

                    T t;

                    xy_y = sin(lp_lon);
                    t = cos(lp_lon);
                    xy_x = atan((tan(lp_lat) * this->m_proj_parm.cosphi + this->m_proj_parm.sinphi * xy_y) / t);
                    if (t < 0.)
                        xy_x += pi;
                    xy_x *= this->m_proj_parm.rtk;
                    xy_y = this->m_proj_parm.rok * (this->m_proj_parm.sinphi * sin(lp_lat) - this->m_proj_parm.cosphi * cos(lp_lat) * xy_y);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    T t, s;

                    xy_y /= this->m_proj_parm.rok;
                    xy_x /= this->m_proj_parm.rtk;
                    t = sqrt(1. - xy_y * xy_y);
                    lp_lat = asin(xy_y * this->m_proj_parm.sinphi + t * this->m_proj_parm.cosphi * (s = sin(xy_x)));
                    lp_lon = atan2(t * this->m_proj_parm.sinphi * s - xy_y * this->m_proj_parm.cosphi,
                        t * cos(xy_x));
                }

                static inline std::string get_name()
                {
                    return "ocea_spheroid";
                }

            };

            // Oblique Cylindrical Equal Area
            template <typename Params, typename Parameters, typename T>
            inline void setup_ocea(Params const& params, Parameters& par, par_ocea<T>& proj_parm)
            {
                static const T half_pi = detail::half_pi<T>();

                T phi_0=0.0, phi_1, phi_2, lam_1, lam_2, lonz, alpha;

                proj_parm.rok = 1. / par.k0;
                proj_parm.rtk = par.k0;
                /*If the keyword "alpha" is found in the sentence then use 1point+1azimuth*/
                if ( pj_param_r<srs::spar::alpha>(params, "alpha", srs::dpar::alpha, alpha)) {
                    /*Define Pole of oblique transformation from 1 point & 1 azimuth*/
                    //alpha = pj_get_param_r(par.params, "alpha"); // set above
                    lonz = pj_get_param_r<T, srs::spar::lonc>(params, "lonc", srs::dpar::lonc);
                    /*Equation 9-8 page 80 (http://pubs.usgs.gov/pp/1395/report.pdf)*/
                    proj_parm.singam = atan(-cos(alpha)/(-sin(phi_0) * sin(alpha))) + lonz;
                    /*Equation 9-7 page 80 (http://pubs.usgs.gov/pp/1395/report.pdf)*/
                    proj_parm.sinphi = asin(cos(phi_0) * sin(alpha));
                /*If the keyword "alpha" is NOT found in the sentence then use 2points*/
                } else {
                    /*Define Pole of oblique transformation from 2 points*/
                    phi_1 = pj_get_param_r<T, srs::spar::lat_1>(params, "lat_1", srs::dpar::lat_1);
                    phi_2 = pj_get_param_r<T, srs::spar::lat_2>(params, "lat_2", srs::dpar::lat_2);
                    lam_1 = pj_get_param_r<T, srs::spar::lon_1>(params, "lon_1", srs::dpar::lon_1);
                    lam_2 = pj_get_param_r<T, srs::spar::lon_2>(params, "lon_2", srs::dpar::lon_2);
                    /*Equation 9-1 page 80 (http://pubs.usgs.gov/pp/1395/report.pdf)*/
                    proj_parm.singam = atan2(cos(phi_1) * sin(phi_2) * cos(lam_1) -
                        sin(phi_1) * cos(phi_2) * cos(lam_2),
                        sin(phi_1) * cos(phi_2) * sin(lam_2) -
                        cos(phi_1) * sin(phi_2) * sin(lam_1) );

                    /* take care of P->lam0 wrap-around when +lam_1=-90*/
                    if (lam_1 == -half_pi)
                        proj_parm.singam = -proj_parm.singam;

                    /*Equation 9-2 page 80 (http://pubs.usgs.gov/pp/1395/report.pdf)*/
                    proj_parm.sinphi = atan(-cos(proj_parm.singam - lam_1) / tan(phi_1));
                }
                par.lam0 = proj_parm.singam + half_pi;
                proj_parm.cosphi = cos(proj_parm.sinphi);
                proj_parm.sinphi = sin(proj_parm.sinphi);
                proj_parm.cosgam = cos(proj_parm.singam);
                proj_parm.singam = sin(proj_parm.singam);
                par.es = 0.;
            }

    }} // namespace detail::ocea
    #endif // doxygen

    /*!
        \brief Oblique Cylindrical Equal Area projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Projection parameters
         - lonc: Longitude (only used if alpha (or gamma) is specified) (degrees)
         - alpha: Alpha (degrees)
         - lat_1: Latitude of first standard parallel (degrees)
         - lat_2: Latitude of second standard parallel (degrees)
         - lon_1 (degrees)
         - lon_2 (degrees)
        \par Example
        \image html ex_ocea.gif
    */
    template <typename T, typename Parameters>
    struct ocea_spheroid : public detail::ocea::base_ocea_spheroid<T, Parameters>
    {
        template <typename Params>
        inline ocea_spheroid(Params const& params, Parameters & par)
        {
            detail::ocea::setup_ocea(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_ocea, ocea_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(ocea_entry, ocea_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(ocea_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(ocea, ocea_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_OCEA_HPP


/* ocea.hpp
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
*/