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