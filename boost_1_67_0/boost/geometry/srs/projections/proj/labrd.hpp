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

#ifndef BOOST_GEOMETRY_PROJECTIONS_LABRD_HPP
#define BOOST_GEOMETRY_PROJECTIONS_LABRD_HPP

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
    namespace detail { namespace labrd
    {
            static const double epsilon = 1.e-10;

            template <typename T>
            struct par_labrd
            {
                T    Az, kRg, p0s, A, C, Ca, Cb, Cc, Cd;
            };

            template <typename T, typename Parameters>
            struct base_labrd_ellipsoid
            {
                par_labrd<T> m_proj_parm;

                // FORWARD(e_forward)
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();

                    T V1, V2, ps, sinps, cosps, sinps2, cosps2;
                    T I1, I2, I3, I4, I5, I6, x2, y2, t;

                    V1 = this->m_proj_parm.A * log( tan(fourth_pi + .5 * lp_lat) );
                    t = par.e * sin(lp_lat);
                    V2 = .5 * par.e * this->m_proj_parm.A * log ((1. + t)/(1. - t));
                    ps = 2. * (atan(exp(V1 - V2 + this->m_proj_parm.C)) - fourth_pi);
                    I1 = ps - this->m_proj_parm.p0s;
                    cosps = cos(ps);    cosps2 = cosps * cosps;
                    sinps = sin(ps);    sinps2 = sinps * sinps;
                    I4 = this->m_proj_parm.A * cosps;
                    I2 = .5 * this->m_proj_parm.A * I4 * sinps;
                    I3 = I2 * this->m_proj_parm.A * this->m_proj_parm.A * (5. * cosps2 - sinps2) / 12.;
                    I6 = I4 * this->m_proj_parm.A * this->m_proj_parm.A;
                    I5 = I6 * (cosps2 - sinps2) / 6.;
                    I6 *= this->m_proj_parm.A * this->m_proj_parm.A *
                        (5. * cosps2 * cosps2 + sinps2 * (sinps2 - 18. * cosps2)) / 120.;
                    t = lp_lon * lp_lon;
                    xy_x = this->m_proj_parm.kRg * lp_lon * (I4 + t * (I5 + t * I6));
                    xy_y = this->m_proj_parm.kRg * (I1 + t * (I2 + t * I3));
                    x2 = xy_x * xy_x;
                    y2 = xy_y * xy_y;
                    V1 = 3. * xy_x * y2 - xy_x * x2;
                    V2 = xy_y * y2 - 3. * x2 * xy_y;
                    xy_x += this->m_proj_parm.Ca * V1 + this->m_proj_parm.Cb * V2;
                    xy_y += this->m_proj_parm.Ca * V2 - this->m_proj_parm.Cb * V1;
                }

                // INVERSE(e_inverse)  ellipsoid & spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();

                    /* t = 0.0 optimization is to avoid a false positive cppcheck warning */
                    /* (cppcheck git beaf29c15867984aa3c2a15cf15bd7576ccde2b3). Might no */
                    /* longer be necessary with later versions. */
                    T x2, y2, V1, V2, V3, V4, t = 0.0, t2, ps, pe, tpe, s;
                    T I7, I8, I9, I10, I11, d, Re;
                    int i;

                    x2 = xy_x * xy_x;
                    y2 = xy_y * xy_y;
                    V1 = 3. * xy_x * y2 - xy_x * x2;
                    V2 = xy_y * y2 - 3. * x2 * xy_y;
                    V3 = xy_x * (5. * y2 * y2 + x2 * (-10. * y2 + x2 ));
                    V4 = xy_y * (5. * x2 * x2 + y2 * (-10. * x2 + y2 ));
                    xy_x += - this->m_proj_parm.Ca * V1 - this->m_proj_parm.Cb * V2 + this->m_proj_parm.Cc * V3 + this->m_proj_parm.Cd * V4;
                    xy_y +=   this->m_proj_parm.Cb * V1 - this->m_proj_parm.Ca * V2 - this->m_proj_parm.Cd * V3 + this->m_proj_parm.Cc * V4;
                    ps = this->m_proj_parm.p0s + xy_y / this->m_proj_parm.kRg;
                    pe = ps + par.phi0 - this->m_proj_parm.p0s;

                    for ( i = 20; i; --i) {
                        V1 = this->m_proj_parm.A * log(tan(fourth_pi + .5 * pe));
                        tpe = par.e * sin(pe);
                        V2 = .5 * par.e * this->m_proj_parm.A * log((1. + tpe)/(1. - tpe));
                        t = ps - 2. * (atan(exp(V1 - V2 + this->m_proj_parm.C)) - fourth_pi);
                        pe += t;
                        if (fabs(t) < epsilon)
                            break;
                    }

                    t = par.e * sin(pe);
                    t = 1. - t * t;
                    Re = par.one_es / ( t * sqrt(t) );
                    t = tan(ps);
                    t2 = t * t;
                    s = this->m_proj_parm.kRg * this->m_proj_parm.kRg;
                    d = Re * par.k0 * this->m_proj_parm.kRg;
                    I7 = t / (2. * d);
                    I8 = t * (5. + 3. * t2) / (24. * d * s);
                    d = cos(ps) * this->m_proj_parm.kRg * this->m_proj_parm.A;
                    I9 = 1. / d;
                    d *= s;
                    I10 = (1. + 2. * t2) / (6. * d);
                    I11 = (5. + t2 * (28. + 24. * t2)) / (120. * d * s);
                    x2 = xy_x * xy_x;
                    lp_lat = pe + x2 * (-I7 + I8 * x2);
                    lp_lon = xy_x * (I9 + x2 * (-I10 + x2 * I11));
                }

                static inline std::string get_name()
                {
                    return "labrd_ellipsoid";
                }

            };

            // Laborde
            template <typename Params, typename Parameters, typename T>
            inline void setup_labrd(Params const& params, Parameters const& par, par_labrd<T>& proj_parm)
            {
                static const T fourth_pi = detail::fourth_pi<T>();

                T Az, sinp, R, N, t;

                Az = pj_get_param_r<T, srs::spar::azi>(params, "azi", srs::dpar::azi);
                sinp = sin(par.phi0);
                t = 1. - par.es * sinp * sinp;
                N = 1. / sqrt(t);
                R = par.one_es * N / t;
                proj_parm.kRg = par.k0 * sqrt( N * R );
                proj_parm.p0s = atan( sqrt(R / N) * tan(par.phi0) );
                proj_parm.A = sinp / sin(proj_parm.p0s);
                t = par.e * sinp;
                proj_parm.C = .5 * par.e * proj_parm.A * log((1. + t)/(1. - t)) +
                    - proj_parm.A * log( tan(fourth_pi + .5 * par.phi0))
                    + log( tan(fourth_pi + .5 * proj_parm.p0s));
                t = Az + Az;
                proj_parm.Ca = (1. - cos(t)) * ( proj_parm.Cb = 1. / (12. * proj_parm.kRg * proj_parm.kRg) );
                proj_parm.Cb *= sin(t);
                proj_parm.Cc = 3. * (proj_parm.Ca * proj_parm.Ca - proj_parm.Cb * proj_parm.Cb);
                proj_parm.Cd = 6. * proj_parm.Ca * proj_parm.Cb;
            }

    }} // namespace detail::labrd
    #endif // doxygen

    /*!
        \brief Laborde projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
         - Special for Madagascar
        \par Projection parameters
         - no_rot: No rotation (boolean)
         - azi: Azimuth (or Gamma) (degrees)
        \par Example
        \image html ex_labrd.gif
    */
    template <typename T, typename Parameters>
    struct labrd_ellipsoid : public detail::labrd::base_labrd_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline labrd_ellipsoid(Params const& params, Parameters const& par)
        {
            detail::labrd::setup_labrd(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_labrd, labrd_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(labrd_entry, labrd_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(labrd_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(labrd, labrd_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_LABRD_HPP


/* labrd.hpp
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
*/